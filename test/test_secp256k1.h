//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef BITCOIN_IN_CPP_TEST_SECP256K1_H
#define BITCOIN_IN_CPP_TEST_SECP256K1_H

#include <gtest/gtest.h>
#include <string>
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

TEST(secp256k1Test, SEC_format) {
    PrivateKey pk(5000);
    unsigned char sec[SEC_LENGTH];
    pk.point.sec(sec, false);
    std::string result = bytes_to_str(sec, SEC_LENGTH);

    ASSERT_EQ(result, "04ffe558e388852f0120e46af2d1b370f85854a8eb0841811ece0e3e03d282d57c315dc72890a4f10a1481c031b03b351b0dc79901ca18a00cf009dbdb157a1d10");

    PrivateKey pk2("33466154331649568");
    pk2.point.sec(sec, false);
    result = bytes_to_str(sec, SEC_LENGTH);

    ASSERT_EQ(result, "04027f3da1918455e03c46f659266a1bb5204e959db7364d2f473bdf8f0a13cc9dff87647fd023c13b4a4994f17691895806e1b40b57f4fd22581a4f46851f3b06");

    PrivateKey pk3("3917405024756549");
    pk3.point.sec(sec, false);
    result = bytes_to_str(sec, SEC_LENGTH);

    ASSERT_EQ(result, "04d90cd625ee87dd38656dd95cf79f65f60f7273b67d3096e68bd81e4f5342691f842efa762fd59961d0e99803c61edba8b3e3f7dc3a341836f97733aebf987121");
}

TEST(secp256k1Test, compressed_SEC_format) {
    PrivateKey pk(5001);
    unsigned char sec[SEC_COMPRESSED_LENGTH];
    pk.point.sec(sec, true);
    std::string result = bytes_to_str(sec, SEC_COMPRESSED_LENGTH);

    ASSERT_EQ(result, "0357a4f368868a8a6d572991e484e664810ff14c05c0fa023275251151fe0e53d1");

    PrivateKey pk2("33549155665686099");
    pk2.point.sec(sec, true);
    result = bytes_to_str(sec, SEC_COMPRESSED_LENGTH);

    ASSERT_EQ(result, "02933ec2d2b111b92737ec12f1c5d20f3233a0ad21cd8b36d0bca7a0cfa5cb8701");

    PrivateKey pk3("3917405025026849");
    pk3.point.sec(sec, true);
    result = bytes_to_str(sec, SEC_COMPRESSED_LENGTH);

    ASSERT_EQ(result, "0296be5b1292f6c856b3c5654e886fc13511462059089cdf9c479623bfcbe77690");
}

TEST(secp256k1Test, der_format) {
    boost::multiprecision::int1024_t r("24934477526773085068622965895147445253088155263472363298185420205900230535110");
    boost::multiprecision::int1024_t s("63617477430228947890476775612691984600680877069283092420476557621266469411564");

    Signature sig {r, s};

    unsigned char out[DER_BUF_LENGTH];
    int len = sig.der(out);
    std::string result = bytes_to_str(out, len);

    ASSERT_EQ(result, "3045022037206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c60221008ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec");
}

TEST(secp256k1Test, address_of_public_key) {
    PrivateKey pk(5002);
    std::string result = pk.point.address(false, true);

    EXPECT_EQ(result, "mmTPbXQFxboEtNRkwfh6K51jvdtHLxGeMA");

    PrivateKey pk2("33632321603200000");
    std::string result2 = pk2.point.address(true, true);

    EXPECT_EQ(result2, "mopVkxp8UhXqRYbCYJsbeE1h1fiF64jcoH");

    PrivateKey pk3("320257972354799");
    std::string result3 = pk3.point.address(true, false);

    EXPECT_EQ(result3, "1F1Pn2y6pDb68E5nYJJeba4TLg2U7B6KF1");
}

#endif //BITCOIN_IN_CPP_TEST_SECP256K1_H