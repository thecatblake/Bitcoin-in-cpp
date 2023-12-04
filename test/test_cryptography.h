//
// Created by ryousuke kaga on 2023/11/14.
//

#ifndef BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H
#define BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H

#include <gtest/gtest.h>
#include "cryptography.h"

TEST(CryptographyTest, hash256) {
    boost::multiprecision::int1024_t e = 12345;
    unsigned char md[SHA256_DIGEST_LENGTH];

    unsigned char msg[] = "Programming Bitcoin!";

    hash256(msg, strlen((char*)msg), md);

    auto result = bytes_to_str(md, SHA256_DIGEST_LENGTH);

    EXPECT_EQ(result, "969f6056aa26f7d2795fd013fe88868d09c9f6aed96965016e1936ae47060d48");
}

TEST(CryptographyTest, ripemd160) {
    unsigned char md[RIPEMD160_DIGEST_LENGTH];

    unsigned char msg[] = "Programming Bitcoin!";

    ripemd160(msg, strlen((char*)msg), md);

    std::string result = bytes_to_str(md, RIPEMD160_DIGEST_LENGTH);

    EXPECT_EQ(result, "5fa51423729739a7932011983d8da55ce343c5ed");
}

TEST(CryptographyTest, hash160) {
    unsigned char md[RIPEMD160_DIGEST_LENGTH];

    unsigned char msg[] = "Programming Bitcoin!";

    hash160(msg, strlen((char*)msg), md);

    std::string result = bytes_to_str(md, RIPEMD160_DIGEST_LENGTH);

    EXPECT_EQ(result, "1bfe0674ace4eb211cf290fd1f7f3ad57f56e490");
}

TEST(CryptographyTest, base58_encoding) {
    // 256 bit
    boost::multiprecision::int1024_t x("56099933801250147507530887846013995861658484709398205753844016085871945288253");
    // 32 byte
    unsigned char bytes[32];
    to_bytes(x, 32, bytes);
    std::string result = encode_base58(bytes, 32);

    EXPECT_EQ(result, "9MA8fRQrT4u8Zj8ZRd6MAiiyaxb2Y1CMpvVkHQu5hVM6");

    boost::multiprecision::int1024_t x2("423978563313610541820751014531939415111138679983830741516375588441135684140");
    to_bytes(x2, 32, bytes);
    result = encode_base58(bytes, 32);

    EXPECT_EQ(result, "4fE3H2E6XMp4SsxtwinF7w9a34ooUrwWe4WsW1458Pd");

    boost::multiprecision::int1024_t x3("90067678915080561991476742139334357116447229582337733602832701972810841451190");
    to_bytes(x3, 32, bytes);
    result = encode_base58(bytes, 32);

    EXPECT_EQ(result, "EQJsjkd6JaGwxrjEhfeqPenqHwrBmPQZjJGNSCHBkcF7");
}

#endif //BITCOIN_IN_CPP_TEST_CRYPTOGRAPHY_H