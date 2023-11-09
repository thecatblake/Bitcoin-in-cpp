//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FiniteElement.h"

FiniteElement::FiniteElement(const BigInt& num, const BigInt& prime): num(num), prime(prime) {

}

bool FiniteElement::operator==(const FiniteElement &other) const {
    return num == other.num && prime == other.prime;
}

std::string FiniteElement::to_string() const {
    return "FiniteElement_" + prime.to_string() + "(" + num.to_string() + ")";
}

bool FiniteElement::operator!=(const FiniteElement &other) const {
    return !operator==(other);
}

FiniteElement FiniteElement::add(const FiniteElement &other) const {
    return {(num + other.num) % prime, prime};
}

FiniteElement FiniteElement::sub(const FiniteElement &other) const {
    BigInt n = (num - other.num) % prime;
    if(n < 0) n += prime;
    return {n , prime};
}

FiniteElement FiniteElement::mul(const FiniteElement &other) const {
    return {(num * other.num) % prime, prime};
}

FiniteElement FiniteElement::div(const FiniteElement &other) const {
    return mul(other.pow((prime - 2).to_int()));
}

FiniteElement FiniteElement::pow(int exp) const {
    if(exp == 0) return {1, prime};
    if(exp < 0) return pow(((prime - 2).to_int() * -exp) % (prime-1).to_int());
    return {::pow(num % (prime-1).to_int(), exp), prime};
}

FiniteElement FiniteElement::check() const {
    return {num % prime, prime};
}

std::ostream& operator << ( std::ostream& outs, const FiniteElement & finiteElement ) {
    return outs << finiteElement.to_string();
}

FiniteElement operator+(const FiniteElement& f1, const FiniteElement& f2) {
    return f1.add(f2);
}

FiniteElement operator-(const FiniteElement& f1, const FiniteElement& f2) {
    return f1.sub(f2);
}

FiniteElement operator*(const FiniteElement& f1, const FiniteElement& f2) {
    return f1.mul(f2);
}

FiniteElement operator/(const FiniteElement& f1, const FiniteElement& f2) {
    return f1.div(f2);
}

FiniteElement pow(const FiniteElement& fe, int exp) {
    return fe.pow(exp);
}