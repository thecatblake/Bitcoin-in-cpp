//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef BITCOIN_IN_CPP_SECP256K1_H
#define BITCOIN_IN_CPP_SECP256K1_H

#include "FieldElement.h"
#include "Point.h"

#define G_X "55066263022277343669578718895168534326250603453777594175500187360389116729240"
#define G_Y "32670510020758816978083085130507043184471273380659243275938904335757337482424"
#define PRIME "115792089237316195423570985008687907853269984665640564039457584007908834671663"
#define N "115792089237316195423570985008687907852837564279074904382605163141518161494337"
#define A 0
#define B 7

class S256Field : public FieldElement {
public:
    S256Field(const BigInt& num): FieldElement(num, BigInt(PRIME)) {}
    std::string to_string() const;
};


class S256Point : public Point {
public:
    S256Point(const BigInt& x, const BigInt& y, bool inf=false): Point(S256Field(x), S256Field(y), S256Field(BigInt(A)), S256Field(BigInt(B)), inf) {}
    S256Point operator*(const BigInt& sc) const;
    static S256Point G();
};

S256Point operator*(const BigInt& sc, const S256Point& p);

#endif //BITCOIN_IN_CPP_SECP256K1_H
