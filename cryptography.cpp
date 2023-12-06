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

int ripemd160(unsigned char* message, size_t message_len, unsigned char* digest) {
    EVP_MD_CTX* ctx;

    if((ctx = EVP_MD_CTX_new()) == nullptr)
        return -1;

    if(!EVP_DigestInit(ctx, EVP_ripemd160()))
        return -1;

    if(!EVP_DigestUpdate(ctx, message, message_len))
        return -1;

    if(!EVP_DigestFinal(ctx, digest, nullptr))
        return -1;

    EVP_MD_CTX_free(ctx);

    return 0;
}

int hash160(unsigned char* message, size_t message_len, unsigned char* digest) {
    unsigned char out[SHA256_DIGEST_LENGTH];
    sha256(message, message_len, out);
    return ripemd160(out, SHA256_DIGEST_LENGTH, digest);
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

boost::multiprecision::int1024_t from_bytes(const unsigned char* digest, size_t len, bool big) {
    boost::multiprecision::int1024_t x = 0;
    for(size_t i = 0; i < len; i++) {
        size_t k = digest[big ? len - i - 1 : i];
        boost::multiprecision::int1024_t t = 256;
        t = boost::multiprecision::pow(t, i);
        t *= k;
        x += t;
    }

    return x;
}

void to_bytes(boost::multiprecision::int1024_t n, int n_bytes, unsigned char* out, bool big) {
    for(int i=0; i < n_bytes; i++) {
        unsigned char rem = (unsigned char)(n % 256);
        out[big ? n_bytes - i - 1 : i] = rem;
        n /= 256;
    }
}

std::string bytes_to_str(unsigned char* bytes, int n_bytes) {
    std::string result;
    for (int i=0; i < n_bytes; i++) {
        char c[3];
        std::snprintf(c, 3, "%02x", bytes[i]);
        result += c;
    }

    return result;
}

std::string encode_base58(unsigned char* bytes, int len) {
    int count = 0;
    for(int i=0; i < len; i++) {
        if(bytes[i]==0)
            count++;
        else
            break;
    }
    auto num = from_bytes(bytes, len);
    std::string result;
    while(num > 0) {
        auto mod = (int)(num % 58);
        num = num / 58;
        result.insert(0, 1, BASE58_ALPHABET[mod]);
    }
    std::string prefix;
    for(int i=0; i < count; i++) prefix += "1";
    return prefix + result;
}

std::string encode_base58_checksum(unsigned char* bytes, int len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash256(bytes, len, hash);
    unsigned char inp[len + 4];
    memcpy(inp, bytes, len);
    memcpy(inp+len, hash, 4);
    return encode_base58(inp, len + 4);
}

boost::multiprecision::int1024_t read_varint(unsigned char* bytes, int* len_out) {
    if (bytes[0] == 0xfd) {
        *len_out = 3;
        return from_bytes(bytes, 2, false);
    } else if (bytes[0] == 0xfe) {
        *len_out = 5;
        return from_bytes(bytes, 4, false);
    } else if (bytes[0] == 0xff) {
        *len_out = 9;
        return from_bytes(bytes, 8, false);
    }

    *len_out = 1;
    return from_bytes(bytes, 1, false);
}

int encode_varint(boost::multiprecision::int1024_t n, unsigned char* out) {
    int len = 1;
    auto x = n.convert_to<long long int>();
    boost::multiprecision::int1024_t t2("18446744073709551616");
    if(n < 0xfd) {
        out[0] = x;
    } else if (n < 0x10000) {
        len = 1 + 2;
        out[0] = 0xfd;
        to_bytes(n, 2, out+1, false);
    } else if (n < 0x100000000) {
        len = 1 + 4;
        out[0] = 0xfe;
        to_bytes(n, 4, out+1, false);
    } else if (n < t2) {
        len = 1 + 8;
        out[0] = 0xff;
        to_bytes(n, 8, out+1, false);
    }

    return len;
}