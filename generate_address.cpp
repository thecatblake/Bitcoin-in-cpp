//
// Created by ryousuke kaga on 2023/12/04.
//

#include "cryptography.h"
#include "secp256k1.h"
#include <iostream>

int main(int argc, char** argv) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    auto* passphrase = (unsigned char*)argv[1];
    sha256(passphrase, strlen(argv[1]), hash);
    boost::multiprecision::int1024_t secret = from_bytes(hash, SHA256_DIGEST_LENGTH, false);

    std::cout << "secret: " << to_string (secret)<< std::endl;

    PrivateKey pk(secret);
    std::string address = pk.point.address(true, true);

    std::cout << "address: " << address << std::endl;
}