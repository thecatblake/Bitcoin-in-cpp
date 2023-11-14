//
// Created by ryousuke kaga on 2023/11/14.
//

#include "cryptography.h"

int sha256(unsigned char* message, size_t message_len, unsigned char* digest) {
    EVP_MD_CTX* ctx;

    if((ctx = EVP_MD_CTX_new()) == nullptr)
        return -1;

    if(!EVP_DigestInit(ctx, EVP_sha256()))
        return -1;

    if(!EVP_DigestUpdate(ctx, message, message_len))
        return -1;

    if(!EVP_DigestFinal(ctx, digest, nullptr))
        return -1;

    EVP_MD_CTX_free(ctx);

    return 0;
}

int hash256(unsigned char* message, size_t message_len, unsigned char* digest) {
    sha256(message, message_len, digest);
    return sha256(digest, SHA256_DIGEST_LENGTH, digest);
}

std::string digest2hex(std::string digest) {
    std::string result;

    for(char i : digest) {
        char h[2];
        snprintf(h, 2, "%x", i);
        result += h;
    }

    return result;
}

const std::string hexstring = "0123456789abcdef";

boost::multiprecision::int1024_t hex2int512(std::string hex) {
    std::reverse(hex.begin(), hex.end());
    boost::multiprecision::int1024_t x = 0;
    for(size_t i = 0; i < hex.length(); i++) {
        size_t k = hexstring.find(hex[i]);
        boost::multiprecision::int1024_t t = 16;
        t = boost::multiprecision::pow(t, i);
        t *= k;
        x += t;
    }

    return x;
}

boost::multiprecision::int1024_t from_bytes(const unsigned char* digest, size_t len) {
    boost::multiprecision::int1024_t x = 0;
    for(size_t i = 0; i < len; i++) {
        size_t k = digest[len - i - 1];
        boost::multiprecision::int1024_t t = 256;
        t = boost::multiprecision::pow(t, i);
        t *= k;
        x += t;
    }

    return x;
}