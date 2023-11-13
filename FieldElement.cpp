//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FieldElement.h"

FieldElement::FieldElement(const BigInt& num, const BigInt& prime): num(num), prime(prime) {

}

bool FieldElement::operator==(const FieldElement &other) const {
    return num == other.num && prime == other.prime;
}

std::string FieldElement::to_string() const {
    return "FiniteElement_" + prime.to_string() + "(" + num.to_string() + ")";
}

bool FieldElement::operator!=(const FieldElement &other) const {
    return !operator==(other);
}

FieldElement FieldElement::add(const FieldElement &other) const {
    return {(num + other.num) % prime, prime};
}

FieldElement FieldElement::sub(const FieldElement &other) const {
    BigInt n = (num - other.num) % prime;
    if(n < 0) n += prime;
    return {n , prime};
}

FieldElement FieldElement::mul(const FieldElement &other) const {
    return {(num * other.num) % prime, prime};
}

FieldElement FieldElement::div(const FieldElement &other) const {
    return mul(other.pow((prime - 2)));
}

FieldElement FieldElement::pow(const BigInt& exp) const {
    if(exp == 0) return {1, prime};
    if(exp < 0) return pow(((prime - 2) * -exp) % (prime-1));

    BigInt p = prime - 1;
    BigInt result = 1;
    BigInt coef = exp;
    BigInt current = num % p;

    while(coef != 0) {
        if(coef % 2 == 1)
            result = result * current % prime;
        current = current * current % prime;
        coef /= 2;
    }

    return {result, prime};
}

FieldElement FieldElement::check() const {
    return {num % prime, prime};
}

FieldElement FieldElement::operator-() const {
    return {-num, prime};
}

FieldElement FieldElement::operator*(const BigInt &sc) const {
    return {(num * sc) % prime, prime};
}

std::ostream& operator << ( std::ostream& outs, const FieldElement & finiteElement ) {
    return outs << finiteElement.to_string();
}

FieldElement operator+(const FieldElement& f1, const FieldElement& f2) {
    return f1.add(f2);
}

FieldElement operator-(const FieldElement& f1, const FieldElement& f2) {
    return f1.sub(f2);
}

FieldElement operator*(const FieldElement& f1, const FieldElement& f2) {
    return f1.mul(f2);
}

FieldElement operator/(const FieldElement& f1, const FieldElement& f2) {
    return f1.div(f2);
}

FieldElement pow(const FieldElement& fe, int exp) {
    return fe.pow(exp);
}