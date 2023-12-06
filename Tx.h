//
// Created by ryousuke kaga on 2023/12/05.
//

#ifndef BITCOIN_IN_CPP_TX_H
#define BITCOIN_IN_CPP_TX_H

struct TxIn {
    unsigned char* prev_tx;
    long prev_id;
};

class Tx {
public:
    Tx(long version);
    static Tx parse(unsigned char* bytes);
    long version;
};

#endif //BITCOIN_IN_CPP_TX_H
