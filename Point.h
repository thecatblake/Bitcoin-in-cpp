//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef BITCOIN_IN_CPP_POINT_H
#define BITCOIN_IN_CPP_POINT_H

#include "FieldElement.h"

class Point {
public:
    Point(const FieldElement& x, const FieldElement& y, const FieldElement& a, const FieldElement& b, bool inf=false);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    Point operator*(const boost::multiprecision::int512_t& sc) const;

    Point add(const Point& other) const;
    FieldElement a;
    FieldElement b;
    FieldElement x;
    FieldElement y;
    bool inf = false;
    bool invalid = false;
};

std::ostream& operator << ( std::ostream& outs, const Point & finiteElement );
Point operator+(const Point& a, const Point& b);
Point operator*(const boost::multiprecision::int512_t& sc, const Point& p);

#endif //BITCOIN_IN_CPP_POINT_H
