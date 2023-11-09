//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FiniteElement.h"

int main() {
    BigInt a = 77;
    BigInt b = pow(a, 49);
    FiniteElement fe(a, b);
    std::cout << b << std::endl;
}