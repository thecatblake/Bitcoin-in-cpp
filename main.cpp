//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FieldElement.h"
#include "secp256k1.h"

int main() {
    PrivateKey pk(5000);
    unsigned char sec[1 + 32 + 32 + 1];
    memset(sec, 0, 1 + 32 + 32 + 1);
    pk.point.sec(sec);
    auto n = from_bytes(sec, 1 + 32 + 32 + 1);
    std::string result = bytes_to_str(sec, 1 + 32 + 32);

    std::cout << result << std::endl;
}