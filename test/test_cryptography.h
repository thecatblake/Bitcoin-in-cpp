//
// Created by ryousuke kaga on 2023/11/14.
//

#ifndef BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H
#define BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H

#include <gtest/gtest.h>
#include "cryptography.h"

TEST(CryptographyTest, from_bytes) {
    boost::multiprecision::int1024_t e = 12345;
    unsigned char md[SHA256_DIGEST_LENGTH];

    unsigned char msg[] = "Programming Bitcoin!";

    hash256(msg, strlen((char*)msg), md);

    auto z = from_bytes(md, SHA256_DIGEST_LENGTH);

    EXPECT_EQ(z.str(), "68128520874913546745294642417570923341793882471965920093685935829550641843528");
}

#endif //BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H