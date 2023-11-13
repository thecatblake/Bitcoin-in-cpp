//
// Created by ryousuke kaga on 2023/11/09.
//

#ifndef BITCOIN_IN_CPP_FIELDELEMENT_H
#define BITCOIN_IN_CPP_FIELDELEMENT_H

#include <iostream>
#include <boost/multiprecision/integer.hpp>

boost::multiprecision::int512_t modpow(boost::multiprecision::int512_t base, boost::multiprecision::int512_t exp, const boost::multiprecision::int512_t& modulus);

class FieldElement {
public:
    FieldElement(boost::multiprecision::int512_t  num, boost::multiprecision::int512_t  prime);
    FieldElement add(const FieldElement& other) const;
    FieldElement sub(const FieldElement& other) const;
    FieldElement mul(const FieldElement& other) const;
    FieldElement div(const FieldElement& other) const;
    FieldElement pow(const boost::multiprecision::int512_t& exp) const;
    bool operator==(const FieldElement & other) const;
    bool operator!=(const FieldElement & other) const;
    FieldElement operator-() const;
    FieldElement operator*(const boost::multiprecision::int512_t& sc) const;
    std::string to_string() const;
    FieldElement check() const;
    boost::multiprecision::int512_t num;
    boost::multiprecision::int512_t prime;
};

std::ostream& operator << ( std::ostream& outs, const FieldElement & finiteElement );
FieldElement operator+(const FieldElement& f1, const FieldElement& f2);
FieldElement operator-(const FieldElement& f1, const FieldElement& f2);
FieldElement operator*(const FieldElement& f1, const FieldElement& f2);
FieldElement operator/(const FieldElement& f1, const FieldElement& f2);
FieldElement pow(const FieldElement& fe, int exp);

#endif //BITCOIN_IN_CPP_FIELDELEMENT_H
