//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FieldElement.h"

#include <utility>


boost::multiprecision::int512_t modpow(boost::multiprecision::int512_t base, boost::multiprecision::int512_t exp, const boost::multiprecision::int512_t& modulus) {
    base %= modulus;
    boost::multiprecision::int512_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp /= 2;
    }
    return result;
}

FieldElement::FieldElement(boost::multiprecision::int512_t  num, boost::multiprecision::int512_t  prime): num(std::move(num)), prime(std::move(prime)) {

}

bool FieldElement::operator==(const FieldElement &other) const {
    return num == other.num && prime == other.prime;
}

std::string FieldElement::to_string() const {
    return "FiniteElement_" + boost::multiprecision::to_string(prime) + "(" + boost::multiprecision::to_string(num) + ")";
}

bool FieldElement::operator!=(const FieldElement &other) const {
    return !operator==(other);
}

FieldElement FieldElement::add(const FieldElement &other) const {
    return {(num + other.num) % prime, prime};
}

FieldElement FieldElement::sub(const FieldElement &other) const {
    auto n = (num - other.num)  % prime;
    if (n < 0) n += prime;
    return {n , prime};
}

FieldElement FieldElement::mul(const FieldElement &other) const {
    return {(num * other.num) % prime, prime};
}

FieldElement FieldElement::div(const FieldElement &other) const {
    return {num * modpow(other.num, prime - 2, prime) % prime, prime};
}

FieldElement FieldElement::pow(const boost::multiprecision::int512_t& exp) const {
    if(exp == 0) return {1, prime};
    if(exp < 0) return pow(((prime - 2) * -1 * exp) % (prime-1));
    return {modpow(num, exp % (prime-1), prime), prime};
}

FieldElement FieldElement::check() const {
    return {num % prime, prime};
}

FieldElement FieldElement::operator-() const {
    return {-1 * num, prime};
}

FieldElement FieldElement::operator*(const boost::multiprecision::int512_t &sc) const {
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