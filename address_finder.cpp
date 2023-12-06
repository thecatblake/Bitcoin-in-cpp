//
// Created by ryousuke kaga on 2023/12/06.
//

#include <boost/multiprecision/integer.hpp>
#include <boost/multiprecision/random.hpp>
#include "secp256k1.h"

using namespace boost::multiprecision;
using namespace boost::random;

int main() {
    constexpr int bit_limit = 256;
    independent_bits_engine<mt19937, bit_limit, int1024_t> generator;

    for (int i=0; i < 10000; i++) {
        int1024_t secret = generator();
        PrivateKey pk(secret);
        auto address = pk.point.address();

        std::cout << to_string(secret) << " " << address << std::endl;
    }
}