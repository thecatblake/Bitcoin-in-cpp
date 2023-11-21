//
// Created by ryousuke kaga on 2023/11/13.
//

#include "secp256k1.h"

std::string S256Field::to_string() const {
    std::unique_ptr<char[]> buf(new char[65]);
    std::snprintf(buf.get(), 65, "%64s", boost::multiprecision::to_string(num).c_str());

    return buf.get();
}

S256Field S256Field::sqrt() {
    return pow((prime+1)/4);
}


S256Point S256Point::G() {
    return {boost::multiprecision::int1024_t(G_X), boost::multiprecision::int1024_t(G_Y)};
}

S256Point S256Point::operator*(const boost::multiprecision::int1024_t &sc) const {
    auto result =  Point::operator*(sc % N);
    return {result.x.num,result.y.num,  result.inf};
}

bool S256Point::verify(const boost::multiprecision::int1024_t &z, const Signature &sig) const {
    boost::multiprecision::int1024_t s_inv = modpow(sig.s, N - 2, N);
    boost::multiprecision::int1024_t u = z * s_inv % N;
    boost::multiprecision::int1024_t v = sig.r * s_inv % N;
    auto total = u * G() + v * *this;
    return total.x.num == sig.r;
}

void S256Point::sec(unsigned char* out, bool compressed) {
    if(compressed) {
        unsigned char buf[SEC_COMPRESSED_LENGTH];
        buf[0] = y.num % 2 == 0 ? 2 : 3;
        to_bytes(x.num, 32, buf + 1);
        memcpy(out, buf, SEC_COMPRESSED_LENGTH);
        return;
    }

    unsigned char buf[SEC_LENGTH];
    buf[0] = 4;
    to_bytes(x.num, 32, buf + 1);
    to_bytes(y.num, 32, buf + 1 + 32);
    memcpy(out, buf, SEC_LENGTH);
}

S256Point S256Point::parse(unsigned char *sec_bin) {
    if(sec_bin[0] == 4) {
        auto x = from_bytes(sec_bin+1, 32);
        auto y = from_bytes(sec_bin+1+32, 32);
        return {x, y};
    }

    bool is_even = sec_bin[0] == 2;
    auto lx = S256Field(from_bytes(sec_bin+1, 32));
    S256Field alpha = lx*lx*lx + S256Field(B);
    auto beta = alpha.sqrt();

    if((is_even && beta.num % 2 == 1) || (!is_even && beta.num % 2 == 0))
        beta = S256Field(beta.prime - beta.num);

    return {x, beta};
}

int S256Point::hash160(unsigned char *digest, bool compressed) {
    unsigned char out[compressed ? SEC_COMPRESSED_LENGTH : SEC_LENGTH];
    sec(out, compressed);
    return ::hash160(out, compressed ? SEC_COMPRESSED_LENGTH : SEC_LENGTH, digest);
}

std::string S256Point::address(bool compressed, bool testnet) {
    unsigned char out[1+RIPEMD160_DIGEST_LENGTH];
    hash160(out+1, compressed);
    out[0] = testnet ? 0x6f : 0x00;
    return encode_base58_checksum(out, 1+RIPEMD160_DIGEST_LENGTH);
}

S256Point operator*(const boost::multiprecision::int1024_t& sc, const S256Point& p) {
    return p * sc;
}

PrivateKey::PrivateKey(boost::multiprecision::int1024_t secret): secret(std::move(secret)) {
    point = this->secret * G;
}

std::string PrivateKey::to_string() {
    std::unique_ptr<char[]> buf(new char[65]);
    std::snprintf(buf.get(), 65, "%64s", boost::multiprecision::to_string(secret).c_str());

    return buf.get();
}

Signature PrivateKey::sign(const boost::multiprecision::int1024_t& z, boost::multiprecision::int1024_t k) {
    if(k == -1) {
        k = generator() % N;
    }

    auto r = (k * G).x.num;
    auto k_inv = modpow(k, N-2, N);
    auto s = (z + r*secret) * k_inv % N;
    if (s > N/2)
        s = N - s;

    return {r, s};
}

PrivateKey::PrivateKey(const std::string& secret): secret(boost::multiprecision::int1024_t(secret)) {

}

int Signature::der(unsigned char *out, bool big) const {
    unsigned char rbin[32];
    to_bytes(r, 32, rbin);
    int i=0;
    while(i < 32 && rbin[i] == 0) i++;
    bool rflag = rbin[i] & 0x80;

    unsigned char sbin[32];
    to_bytes(s, 32, sbin);
    int j = 0;
    while(j < 32 && sbin[j] == 0) j++;
    bool sflag = sbin[j] & 0x80;

    out[0] = 0x30;
    out[1] = 32 + 32 + 1 + 1 + 1 + 1 + 1;
    out[2] = 0x02;
    out[3] = 32 - i + rflag;
    out[4] = 0x00;
    memcpy(out+4+rflag, rbin+i, 32-i);
    out[4 + rflag + 32 - i ] = 0x02;
    out[4 + rflag + 32 - i + 1] = 32 - j + sflag;
    out[4 + rflag + 32 - i + 2] = 0x00;
    memcpy(out + 4+rflag+32-i+2+sflag, sbin+j, 32-j);
    return 4+rflag+32-i+2+sflag+32-j;
}
