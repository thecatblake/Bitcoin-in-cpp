//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef BITCOIN_IN_CPP_TEST_SECP256K1_H
#define BITCOIN_IN_CPP_TEST_SECP256K1_H

#include <gtest/gtest.h>
#include "secp256k1.h"


TEST(secp256k1Test, constants) {
    auto G = S256Point::G();
    auto n = BigInt(N);

    ASSERT_TRUE((n * G).inf);
}

#endif //BITCOIN_IN_CPP_TEST_SECP256K1_H
