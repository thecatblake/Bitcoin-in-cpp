//
// Created by ryousuke kaga on 2023/11/14.
//

#ifndef BITCOIN_IN_CPP_CRYPTOGRAPHY_H
#define BITCOIN_IN_CPP_CRYPTOGRAPHY_H

#include <openssl/ssl.h>
#include <boost/multiprecision/integer.hpp>
#include <boost/format.hpp>

#define SHA256_DIGEST_LENGTH 32 // 256 / 8

int sha256(unsigned char* message, size_t message_len, unsigned char* digest);

int hash256(unsigned char* message, size_t message_len, unsigned char* digest);

std::string digest2hex(unsigned char* digest, size_t len);

boost::multiprecision::int1024_t hex2int512(std::string hex);

boost::multiprecision::int1024_t from_bytes(const unsigned char* digest, size_t len);

#endif //BITCOIN_IN_CPP_CRYPTOGRAPHY_H
