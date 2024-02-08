//
// Created by ryousuke kaga on 2023/12/05.
//

#include "Tx.h"
#include "cryptography.h"

Tx Tx::parse(unsigned char* bytes) {
    Tx tx;
    tx.version = from_bytes(bytes, 4, false).convert_to<long>();
    bytes += 4;

    int bytes_read;
    auto tx_in_num = read_varint(bytes, &bytes_read);
    bytes += bytes_read;

    for(int i=0; i < tx_in_num; i++) {
        TxIn input = TxIn::parse(bytes, &bytes_read);
        tx.inputs.push_back(input);
        bytes += bytes_read;
    }

    auto tx_out_num = read_varint(bytes, &bytes_read);
    bytes += bytes_read;

    for(int i=0; i < tx_out_num; i++) {
        TxOut output = TxOut::parse(bytes, &bytes_read);
        tx.outputs.push_back(output);
        bytes += bytes_read;
    }

    tx.locktime = from_bytes(bytes, 4, false).convert_to<unsigned long>();

    return tx;
}

TxIn TxIn::parse(unsigned char *bytes, int* bytes_out) {
    TxIn input;

    input.prev_tx = from_bytes(bytes, 32, false);
    bytes += 32;
    input.prev_tx_id = from_bytes(bytes, 4, false).convert_to<unsigned long>();
    bytes += 4;

    int bytes_read;
    auto script_length = read_varint(bytes, &bytes_read).convert_to<unsigned long>();
    unsigned char script_raw[script_length];
    bytes += bytes_read;
    std::memcpy(script_raw, bytes, script_length);
    input.script_raw.reserve(script_length);
    std::copy(script_raw,script_raw+script_length, std::back_inserter(input.script_raw));
    bytes += script_length;

    input.sequence = from_bytes(bytes, 4, false).convert_to<unsigned long>();

    *bytes_out = 32 + 4 + bytes_read + script_length + 4;

    return input;
}

TxOut TxOut::parse(unsigned char *bytes, int* bytes_out) {
    TxOut output;

    output.amount = from_bytes(bytes, 8, false);

    bytes += 8;

    int bytes_read;
    auto script_length = read_varint(bytes, &bytes_read).convert_to<unsigned long>();
    unsigned char script_raw[script_length];
    bytes += bytes_read;
    std::memcpy(script_raw, bytes, script_length);
    output.script_pubkey_raw.reserve(script_length);
    std::copy(script_raw,script_raw+script_length, std::back_inserter(output.script_pubkey_raw));

    *bytes_out = 8 + bytes_read + script_length;

    return output;
}
