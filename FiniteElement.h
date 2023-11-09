//
// Created by ryousuke kaga on 2023/11/09.
//

#ifndef BITCOIN_IN_CPP_FINITEELEMENT_H
#define BITCOIN_IN_CPP_FINITEELEMENT_H

#include <iostream>
#include "BigInt.h"

class FiniteElement {
public:
    FiniteElement(const BigInt& num, const BigInt& prime);
    FiniteElement add(const FiniteElement& other) const;
    FiniteElement sub(const FiniteElement& other) const;
    FiniteElement mul(const FiniteElement& other) const;
    FiniteElement div(const FiniteElement& other) const;
    FiniteElement pow(int exp) const;
    bool operator==(const FiniteElement & other) const;
    bool operator!=(const FiniteElement & other) const;
    std::string to_string() const;
    FiniteElement check() const;
    BigInt num;
    BigInt prime;
};

std::ostream& operator << ( std::ostream& outs, const FiniteElement & finiteElement );
FiniteElement operator+(const FiniteElement& f1, const FiniteElement& f2);
FiniteElement operator-(const FiniteElement& f1, const FiniteElement& f2);
FiniteElement operator*(const FiniteElement& f1, const FiniteElement& f2);
FiniteElement operator/(const FiniteElement& f1, const FiniteElement& f2);
FiniteElement pow(const FiniteElement& fe, int exp);

#endif //BITCOIN_IN_CPP_FINITEELEMENT_H
