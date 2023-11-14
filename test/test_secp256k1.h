//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef BITCOIN_IN_CPP_TEST_SECP256K1_H
#define BITCOIN_IN_CPP_TEST_SECP256K1_H

#include <gtest/gtest.h>
#include "secp256k1.h"


TEST(secp256k1Test, constants) {
    auto G = S256Point::G();
    auto n = boost::multiprecision::int1024_t(N);

    ASSERT_TRUE((n * G).inf);
}

TEST(secp256k1Test, verifying_signature) {
    S256Point point(
            boost::multiprecision::int1024_t("61718672711110078285455301750480400966627255360668707636501858927943098880108"),
            boost::multiprecision::int1024_t("44267342672039291314052509441658516950140155852350072275186874907549665111604"));
    boost::multiprecision::int1024_t z("106803335299316304368406718150407005727570940625608758663533317704082257612640");
    boost::multiprecision::int1024_t r("78047132305074547209667415378684003360790728528333174453334458954808711947157");
    boost::multiprecision::int1024_t s("2945795152904547855448158643091235482997756069461486099501216307557115896772");
    Signature sig {r, s};
    ASSERT_TRUE(point.verify(z, sig));
}

TEST(secp256k1Test, signing_signature) {
    unsigned char md[SHA256_DIGEST_LENGTH];

    unsigned char msg[] = "Programming Bitcoin!";

    hash256(msg, strlen((char*)msg), md);

    boost::multiprecision::int1024_t e = 12345;
    auto z = from_bytes(md, SHA256_DIGEST_LENGTH);

    PrivateKey pk(e);
    auto sig = pk.sign(z, 1234567890);

    EXPECT_EQ(sig.r.str(), "19635924277356798752105674083697999930996555344818160161847497917044432760610");
    EXPECT_EQ(sig.s.str(), "13449928304528854552621297743528922715969746175462178470032064141974217735194");
}

TEST(secp256k1Test, signing_veryfing) {
    boost::random::independent_bits_engine<boost::mt19937, 512, boost::multiprecision::int1024_t> generator;
    PrivateKey pk(generator() % N);
    auto z = generator();
    auto sig = pk.sign(z);
    ASSERT_TRUE(pk.point.verify(z, sig));
}

#endif //BITCOIN_IN_CPP_TEST_SECP256K1_H