//
// Created by ryousuke kaga on 2023/11/13.
//

#include "secp256k1.h"

std::string S256Field::to_string() const {
    std::unique_ptr<char[]> buf(new char[65]);
    std::snprintf(buf.get(), 65, "%064llx", num.to_long_long());

    return buf.get();
}

S256Point S256Point::G() {
    return {BigInt(G_X), BigInt(G_Y)};
}

S256Point S256Point::operator*(const BigInt &sc) const {
    auto result =  Point::operator*(sc % N);
    return {result.x.num,result.y.num,  result.inf};
}

S256Point operator*(const BigInt& sc, const S256Point& p) {
    return p * sc;
}
