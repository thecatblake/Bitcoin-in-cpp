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

std::vector<unsigned char> Tx::serialize() {
    int tx_in_varint_size = varint_size(inputs.size());
    int tx_out_varint_size = varint_size(outputs.size());

    unsigned char bytes[4 + tx_in_varint_size + tx_out_varint_size + 4];
    to_bytes(version, 4, bytes);
    encode_varint(inputs.size(), bytes+4);
    encode_varint(outputs.size(),bytes+4+tx_in_varint_size);
    to_bytes(locktime, 4, bytes+4+tx_in_varint_size+tx_out_varint_size);

    std::vector<unsigned char> result;
    result.reserve(version+tx_in_varint_size);

    auto it = result.begin();

    std::copy(bytes, bytes+4, it);
    it += 4;
    std::copy(bytes+4, bytes+4+tx_in_varint_size, it);

    for(auto& input : inputs) {
        auto input_bytes = input.serialize();
        result.insert(result.end(), input_bytes.begin(), input_bytes.end());
    }

    it = result.end();
    result.reserve(tx_out_varint_size);
    std::copy(bytes+4+tx_in_varint_size, bytes+4+tx_in_varint_size+tx_out_varint_size, it);

    for(auto& output: outputs) {
        auto output_bytes = output.serialize();
        result.insert(result.end(), output_bytes.begin(), output_bytes.end());
    }

    it = result.end();
    result.reserve(4);
    std::copy(bytes+4+tx_in_varint_size+tx_out_varint_size, bytes+4+tx_in_varint_size+tx_out_varint_size+4, it);

    return result;
}

Tx::Tx() {

}

Tx::Tx(long version, std::vector<TxIn> inputs, std::vector<TxOut> outputs, unsigned long locktime, bool testnet):
    version(version), inputs(inputs), outputs(outputs), locktime(locktime), testnet(testnet) {

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

std::vector<unsigned char> TxIn::serialize() {
    unsigned long size = 32 + 4 + 4;

    unsigned char bytes[size];
    to_bytes(prev_tx, 32, bytes, false);
    to_bytes(prev_tx_id, 4, bytes+32, false);
    to_bytes(sequence, 4, bytes+32+4, false);

    std::vector<unsigned char> result;
    result.reserve(size + script_raw.size());

    auto it = result.begin();

    std::copy(bytes, bytes+32+4, it);
    it += 32 + 4;
    std::copy(script_raw.begin(), script_raw.end(), it);
    it += script_raw.size();
    std::copy(bytes+32+4, bytes+32+4+4, it);

    return result;
}

TxIn::TxIn(boost::multiprecision::int1024_t prev_tx, unsigned long prev_tx_id): prev_tx(prev_tx), prev_tx_id(prev_tx_id) {

}

TxIn::TxIn() {

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

std::vector<unsigned char> TxOut::serialize() {
    unsigned long size = 4;

    unsigned char bytes[size];
    to_bytes(amount, 4, bytes, false);

    std::vector<unsigned char> result;
    result.reserve(size + script_pubkey_raw.size());

    auto it = result.begin();

    std::copy(bytes, bytes+4, it);
    it += 4;
    std::copy(script_pubkey_raw.begin(), script_pubkey_raw.end(), it);

    return result;
}

TxOut::TxOut() {

}

TxOut::TxOut(boost::multiprecision::int1024_t amount, std::vector<unsigned char> script_raw): amount(amount), script_pubkey_raw(script_raw) {

}
