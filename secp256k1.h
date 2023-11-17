//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef BITCOIN_IN_CPP_SECP256K1_H
#define BITCOIN_IN_CPP_SECP256K1_H

#include <utility>

#include "FieldElement.h"
#include "Point.h"
#include "cryptography.h"

const boost::multiprecision::int1024_t G_X("55066263022277343669578718895168534326250603453777594175500187360389116729240");
const boost::multiprecision::int1024_t G_Y("32670510020758816978083085130507043184471273380659243275938904335757337482424");
#define PRIME "115792089237316195423570985008687907853269984665640564039457584007908834671663"
const boost::multiprecision::int1024_t N("115792089237316195423570985008687907852837564279074904382605163141518161494337");
#define A 0
#define B 7

struct Signature {
    boost::multiprecision::int1024_t r;
    boost::multiprecision::int1024_t s;

    void der(unsigned char* out, bool big=false);
};

class S256Field : public FieldElement {
public:
    S256Field(const boost::multiprecision::int1024_t& num): FieldElement(num, boost::multiprecision::int1024_t(PRIME)) {}
    S256Field(const FieldElement& e): FieldElement(e.num, boost::multiprecision::int1024_t(PRIME)) {}
    std::string to_string() const;
    S256Field sqrt();
};


class S256Point : public Point {
public:
    S256Point(const boost::multiprecision::int1024_t& x, const boost::multiprecision::int1024_t& y, bool inf=false): Point(S256Field(x), S256Field(y), S256Field(boost::multiprecision::int1024_t(A)), S256Field(boost::multiprecision::int1024_t(B)), inf) {}
    S256Point(const S256Field x, const S256Field, bool inf=false): Point(x, y, S256Field(boost::multiprecision::int1024_t(A)), S256Field(boost::multiprecision::int1024_t(B)), inf) {}
    S256Point operator*(const boost::multiprecision::int1024_t& sc) const;
    bool verify(const boost::multiprecision::int1024_t& z, const Signature& sig) const;
    static S256Point G();
    void sec(unsigned char* out, bool compressed=false);
    S256Point parse(unsigned char* sec_bin);
};

S256Point operator*(const boost::multiprecision::int1024_t& sc, const S256Point& p);


class PrivateKey {
public:
    PrivateKey(boost::multiprecision::int1024_t  secret);
    std::string to_string();
    Signature sign(const boost::multiprecision::int1024_t& z, boost::multiprecision::int1024_t k = -1);
    boost::multiprecision::int1024_t secret;
    S256Point point = S256Point(0, 0, true);
private:
    S256Point G = S256Point::G();
    static constexpr int bit_limit = 512;
    boost::random::independent_bits_engine<boost::mt19937, bit_limit, boost::multiprecision::int1024_t> generator;
};

#endif //BITCOIN_IN_CPP_SECP256K1_H
