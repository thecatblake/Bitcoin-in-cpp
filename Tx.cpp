//
// Created by ryousuke kaga on 2023/12/05.
//

#include "Tx.h"
#include "cryptography.h"

Tx Tx::parse(unsigned char* bytes) {
    long version = from_bytes(bytes, 4, false).convert_to<long>();
    bytes += 4;
    int bytes_read;
    auto tx_in_num = read_varint(bytes, &bytes_read);
    bytes += bytes_read;
    return {version};
}

Tx::Tx(long version): version(version) {
}
