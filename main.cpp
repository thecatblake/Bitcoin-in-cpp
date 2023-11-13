//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FieldElement.h"

int main() {
    BigInt a = 77;
    BigInt b = pow(a, 49);
    FieldElement fe(a, b);
    std::cout << b << std::endl;
}