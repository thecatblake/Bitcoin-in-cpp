//
// Created by ryousuke kaga on 2023/11/13.
//

#include "secp256k1.h"

std::string S256Field::to_string() const {
    std::unique_ptr<char[]> buf(new char[65]);
    std::snprintf(buf.get(), 65, "%64s", boost::multiprecision::to_string(num).c_str());

    return buf.get();
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

void S256Point::sec(unsigned char* out) {
    unsigned char buf[1 + 32 + 32 + 1];
    buf[0] = 4;
    to_bytes(x.num, 32, buf + 1);
    to_bytes(y.num, 32, buf + 1 + 32);
    buf[1 + 32 + 32] = '\0';
    memcpy(out, buf, 1 + 32 + 32 + 1);
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
