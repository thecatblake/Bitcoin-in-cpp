//
// Created by ryousuke kaga on 2023/11/11.
//

#include "Point.h"

Point::Point(const BigInt& x, const BigInt& y, const BigInt& a, const BigInt& b, bool inf):
    x(x), y(y), a(a), b(b), inf(inf) {
    if(y * y != x * x * x + a * x + b)
        throw std::runtime_error("(" + x.to_string() + ", " + y.to_string() + ") is not on the curve");
}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y && a == other.a && b == other.b;
}

bool Point::operator!=(const Point &other) const {
    return !operator==(other);
}

Point Point::add(const Point &other) const {
    if (inf)
        return other;
    if (other.inf)
        return *this;

    if(x == other.x)
        return {0, 0, a, b, true};

    BigInt s;

    if(x == other.x && y == other.y) {
        if(y == 0)
            return {0, 0, a, b, true};
        s = (x * x * 3 + a) / (y * 2);
    } else {
        s = (other.y - y) / (other.x - x);
    }

    BigInt x3 = s*s - x - other.x;
    BigInt y3 = s * (x - x3) - y;

    return {x3, y3, a, b};
}

Point operator+(const Point& a, const Point& b) {
    return a.add(b);
}
