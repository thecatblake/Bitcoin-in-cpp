//
// Created by ryousuke kaga on 2023/11/14.
//

#ifndef BITCOIN_IN_CPP_CRYPTOGRAPHY_H
#define BITCOIN_IN_CPP_CRYPTOGRAPHY_H

#include <openssl/ssl.h>
#include <boost/multiprecision/integer.hpp>
#include <boost/format.hpp>

#define SHA256_DIGEST_LENGTH 32 // 256 / 8
#define RIPEMD160_DIGEST_LENGTH 20 // 160 / 8

int sha256(unsigned char* message, size_t message_len, unsigned char* digest);

int hash256(unsigned char* message, size_t message_len, unsigned char* digest);

int ripemd160(unsigned char* message, size_t message_len, unsigned char* digest);

int hash160(unsigned char* message, size_t message_len, unsigned char* digest);

std::string digest2hex(unsigned char* digest, size_t len);

boost::multiprecision::int1024_t hex2int512(std::string hex);

boost::multiprecision::int1024_t from_bytes(const unsigned char* digest, size_t len, bool big=true);
void to_bytes(boost::multiprecision::int1024_t n, int n_bytes, unsigned char* out, bool big= true);
void to_bytes(unsigned long n, int n_bytes, unsigned char* out, bool big= true);

std::string bytes_to_str(unsigned char* bytes, int n_bytes);


const std::string BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
std::string encode_base58(unsigned char* bytes, int len);
void decode_base58(std::string s, unsigned char* out);

std::string encode_base58_checksum(unsigned char* bytes, int len);

boost::multiprecision::int1024_t read_varint(unsigned char* bytes, int* len_out);
int encode_varint(boost::multiprecision::int1024_t n, unsigned char* out);
int varint_size(boost::multiprecision::int1024_t n);
#endif //BITCOIN_IN_CPP_CRYPTOGRAPHY_H
