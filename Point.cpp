//
// Created by ryousuke kaga on 2023/11/11.
//

#include "Point.h"

Point::Point(const FieldElement& x, const FieldElement& y, const FieldElement& a, const FieldElement& b, bool inf):
    x(x), y(y), a(a), b(b), inf(inf) {
    if(!inf && y * y != x * x * x + a * x + b)
        invalid = true;
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

    if(x == other.x && y == -other.y)
        return {{0, x.prime}, {0, y.prime}, a, b, true};

    if(x != other.x) {
        FieldElement s = (other.y - y) / (other.x - x);
        FieldElement x3 = s*s - x - other.x;
        FieldElement y3 = s * (x - x3) - y;
        return {x3, y3, a, b};
    }

    if(operator==(other) && y.num == 0)
        return  {{0, x.prime}, {0, y.prime}, a, b, true};

    if(operator==(other)) {
        FieldElement s = (x * x * 3 + a) / (y * 2);
        FieldElement x3 = s*s - x * 2;
        FieldElement y3 = s * (x - x3) - y;
        return {x3, y3, a, b};
    }
}

Point Point::operator*(const boost::multiprecision::int1024_t& sc) const {
    Point p(x, y, a, b);
    boost::multiprecision::int1024_t coef = sc;
    Point result({0, x.prime}, {0, y.prime}, a, b, true);
    while(coef != 0) {
        if(coef % 2 == 1)
            result = result + p;
        p = p + p;
        coef /= 2;
    }

    return result;
}

std::ostream& operator << ( std::ostream& outs, const Point & point ) {
    outs << "(" << point.x << ", " << point.y << ")";
}

Point operator+(const Point& a, const Point& b) {
    return a.add(b);
}

Point operator*(const boost::multiprecision::int1024_t& sc, const Point& p) {
    return p * sc;
}