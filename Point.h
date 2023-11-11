//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef BITCOIN_IN_CPP_POINT_H
#define BITCOIN_IN_CPP_POINT_H

#include "BigInt.h"

class Point {
public:
    Point(const BigInt& x, const BigInt& y, const BigInt& a, const BigInt& b, bool inf=false);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Point add(const Point& other) const;
    BigInt a;
    BigInt b;
    BigInt x;
    BigInt y;
    bool inf;
};

Point operator+(const Point& a, const Point& b);

#endif //BITCOIN_IN_CPP_POINT_H
