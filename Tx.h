//
// Created by ryousuke kaga on 2023/12/05.
//

#ifndef BITCOIN_IN_CPP_TX_H
#define BITCOIN_IN_CPP_TX_H

#include <vector>
#include <cstring>
#include <boost/multiprecision/integer.hpp>

struct TxIn {
    boost::multiprecision::int1024_t prev_tx;
    unsigned long prev_tx_id;
    std::vector<unsigned char> script_raw;
    unsigned long sequence;

    TxIn();
    TxIn(boost::multiprecision::int1024_t prev_tx, unsigned long prev_tx_id);
    static TxIn parse(unsigned char* bytes, int* bytes_read);
    std::vector<unsigned char> serialize();
};

struct TxOut {
    boost::multiprecision::int1024_t amount;
    std::vector<unsigned char> script_pubkey_raw;

    TxOut();
    TxOut(boost::multiprecision::int1024_t amount, std::vector<unsigned char> script_raw);
    static TxOut parse(unsigned char* bytes, int* bytes_read);
    std::vector<unsigned char> serialize();
};

class Tx {
public:
    static Tx parse(unsigned char* bytes);
    std::vector<unsigned char> serialize();

    Tx();
    Tx(long version, std::vector<TxIn> inputs, std::vector<TxOut> outputs, unsigned long locktime, bool testnet);
    long version;
    std::vector<TxIn> inputs;
    std::vector<TxOut> outputs;
    unsigned long locktime;
    bool testnet;
};

#endif //BITCOIN_IN_CPP_TX_H
