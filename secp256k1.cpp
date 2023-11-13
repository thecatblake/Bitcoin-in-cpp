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
    return {boost::multiprecision::int512_t(G_X), boost::multiprecision::int512_t(G_Y)};
}

S256Point S256Point::operator*(const boost::multiprecision::int512_t &sc) const {
    auto result =  Point::operator*(sc % N);
    return {result.x.num,result.y.num,  result.inf};
}

bool S256Point::verify(const boost::multiprecision::int512_t &z, const Signature &sig) const {
    boost::multiprecision::int512_t s_inv = modpow(sig.s, N - 2, N);
    boost::multiprecision::int512_t u = z * s_inv % N;
    boost::multiprecision::int512_t v = sig.r * s_inv % N;
    auto total = u * G() + v * *this;
    return total.x.num == sig.r;
}

S256Point operator*(const boost::multiprecision::int512_t& sc, const S256Point& p) {
    return p * sc;
}
