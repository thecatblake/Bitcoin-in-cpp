//
// Created by ryousuke kaga on 2024/02/08.
//

#ifndef BITCOIN_IN_CPP_TEST_TX_H
#define BITCOIN_IN_CPP_TEST_TX_H

#include <gtest/gtest.h>
#include <string>
#include "Tx.h"
#include "Script.h"


TEST(txTest, TxParsing) {
    unsigned char tx_raw[] = {
            1, 0, 0, 0, 1, 129, 63, 121, 1, 26, 203, 128, 146, 93, 254, 105, 179, 222, 243, 85, 254, 145, 75, 209, 217, 106, 63, 95, 113, 191, 131, 3, 198, 169, 137, 199, 209, 0, 0, 0, 0, 107, 72, 48, 69, 2, 33, 0, 237, 129, 255, 25, 46, 117, 163, 253, 35, 4, 0, 77, 202, 219, 116, 111, 165, 226, 76, 80, 49, 204, 252, 242, 19, 32, 176, 39, 116, 87, 201, 143, 2, 32, 122, 152, 109, 149, 92, 110, 12, 179, 93, 68, 106, 137, 211, 245, 97, 0, 244, 215, 246, 120, 1, 195, 25, 103, 116, 58, 156, 142, 16, 97, 91, 237, 1, 33, 3, 73, 252, 78, 99, 30, 54, 36, 165, 69, 222, 63, 137, 245, 216, 104, 76, 123, 129, 56, 189, 148, 189, 213, 49, 210, 226, 19, 191, 1, 107, 39, 138, 254, 255, 255, 255, 2, 161, 53, 239, 1, 0, 0, 0, 0, 25, 118, 169, 20, 188, 59, 101, 77, 202, 126, 86, 176, 77, 202, 24, 242, 86, 108, 218, 240, 46, 141, 154, 218, 136, 172, 153, 195, 152, 0, 0, 0, 0, 0, 25, 118, 169, 20, 28, 75, 199, 98, 221, 84, 35, 227, 50, 22, 103, 2, 203, 117, 244, 13, 247, 159, 234, 18, 136, 172, 25, 67, 6, 0
    };

    Tx tx = Tx::parse(tx_raw);

    ASSERT_EQ(tx.version, 1);
    ASSERT_EQ(tx.inputs.size(), 1);
    ASSERT_EQ(tx.inputs[0].prev_tx_id, 0);
    ASSERT_EQ(tx.inputs[0].sequence, 0xfffffffe);

    ASSERT_EQ(tx.outputs.size(), 2);
    ASSERT_EQ(tx.outputs[0].amount, 32454049);
    ASSERT_EQ(tx.outputs[1].amount, 10011545);

    ASSERT_EQ(tx.locktime, 410393);
}

TEST(txTest, TxSerializing) {
    unsigned char tx_raw[] = {
            1, 0, 0, 0, 1, 129, 63, 121, 1, 26, 203, 128, 146, 93, 254, 105, 179, 222, 243, 85, 254, 145, 75, 209, 217, 106, 63, 95, 113, 191, 131, 3, 198, 169, 137, 199, 209, 0, 0, 0, 0, 107, 72, 48, 69, 2, 33, 0, 237, 129, 255, 25, 46, 117, 163, 253, 35, 4, 0, 77, 202, 219, 116, 111, 165, 226, 76, 80, 49, 204, 252, 242, 19, 32, 176, 39, 116, 87, 201, 143, 2, 32, 122, 152, 109, 149, 92, 110, 12, 179, 93, 68, 106, 137, 211, 245, 97, 0, 244, 215, 246, 120, 1, 195, 25, 103, 116, 58, 156, 142, 16, 97, 91, 237, 1, 33, 3, 73, 252, 78, 99, 30, 54, 36, 165, 69, 222, 63, 137, 245, 216, 104, 76, 123, 129, 56, 189, 148, 189, 213, 49, 210, 226, 19, 191, 1, 107, 39, 138, 254, 255, 255, 255, 2, 161, 53, 239, 1, 0, 0, 0, 0, 25, 118, 169, 20, 188, 59, 101, 77, 202, 126, 86, 176, 77, 202, 24, 242, 86, 108, 218, 240, 46, 141, 154, 218, 136, 172, 153, 195, 152, 0, 0, 0, 0, 0, 25, 118, 169, 20, 28, 75, 199, 98, 221, 84, 35, 227, 50, 22, 103, 2, 203, 117, 244, 13, 247, 159, 234, 18, 136, 172, 25, 67, 6, 0
    };

    Tx tx = Tx::parse(tx_raw);

    std::vector<unsigned char> serialized = tx.serialize();

    bool eq = true;
    for(size_t i=0; i < serialized.size(); i++) {
        if(tx_raw[i] != serialized[i]) eq = false;
    }

    ASSERT_TRUE(eq);
}

TEST(txTest, TxCreation) {
    unsigned char prev_tx_raw[] = {
            117, 161, 196, 188, 103, 31, 85, 246, 38, 221, 161, 7, 76, 119, 37, 153, 30, 111, 104, 184, 252, 239, 207, 202, 123, 100, 64, 92, 163, 180, 95, 28
    };


    TxIn prev_tx(from_bytes(prev_tx_raw, 32), 13);
    unsigned char change_h160[20];
    decode_base58("mzx5YhAH9kNHtcN481u6WkjeHjYtVeKVh2", change_h160);
    std::vector<unsigned char> change_script = p2pkh_script(change_h160);
    TxOut change_output(9000000, change_script);
    unsigned char target_h160[20];
    decode_base58("miKegze5FQNCnGw6PKyqUbYUeBa4x2hFeM", target_h160);
    std::vector<unsigned char> target_script = p2pkh_script(target_h160);
    TxOut target_output(1000000, target_script);

    std::vector<TxIn> inputs = {prev_tx};
    std::vector<TxOut> outputs = {change_output,target_output};
    Tx tx(1, inputs, outputs, 0, true);

    std::vector<unsigned char> serialized = tx.serialize();
    std::vector<unsigned char> tx_true = {
            1, 0, 0, 0, 2, 47, 42, 254, 87, 189, 224, 130, 44, 121, 54, 4, 186, 174, 131, 79, 44, 210, 97, 85, 191, 28, 13, 55, 72, 2, 18, 193, 7, 231, 92, 208, 17, 1, 0, 0, 0, 106, 71, 48, 68, 2, 32, 76, 197, 254, 17, 178, 176, 37, 248, 252, 159, 96, 115, 181, 227, 148, 40, 131, 187, 186, 38, 107, 113, 117, 16, 104, 186, 222, 184, 241, 31, 3, 100, 2, 32, 112, 23, 131, 99, 245, 222, 164, 20, 149, 129, 164, 185, 185, 219, 173, 145, 236, 31, 217, 144, 227, 250, 20, 249, 222, 60, 203, 66, 31, 165, 178, 105, 1, 33, 3, 147, 85, 129, 229, 44, 53, 76, 210, 244, 132, 254, 142, 216, 58, 247, 163, 9, 112, 5, 178, 249, 198, 11, 255, 113, 211, 91, 215, 149, 245, 75, 103, 255, 255, 255, 255, 21, 61, 176, 32, 45, 226, 126, 121, 68, 199, 253, 101, 30, 193, 208, 250, 177, 241, 170, 237, 75, 13, 166, 13, 154, 27, 6, 189, 119, 31, 246, 81, 1, 0, 0, 0, 107, 72, 48, 69, 2, 33, 0, 183, 169, 56, 212, 103, 154, 167, 39, 31, 13, 50, 216, 59, 97, 168, 94, 176, 24, 12, 241, 38, 29, 68, 254, 170, 210, 61, 253, 151, 153, 218, 251, 2, 32, 95, 242, 243, 102, 221, 217, 85, 95, 113, 70, 134, 26, 130, 152, 183, 99, 107, 232, 178, 146, 9, 10, 34, 76, 93, 200, 66, 104, 72, 13, 139, 225, 1, 33, 3, 147, 85, 129, 229, 44, 53, 76, 210, 244, 132, 254, 142, 216, 58, 247, 163, 9, 112, 5, 178, 249, 198, 11, 255, 113, 211, 91, 215, 149, 245, 75, 103, 255, 255, 255, 255, 1, 208, 117, 65, 0, 0, 0, 0, 0, 25, 118, 169, 20, 173, 52, 111, 142, 181, 125, 238, 154, 55, 152, 23, 22, 228, 152, 18, 10, 232, 14, 68, 247, 136, 172, 0, 0, 0, 0
    };
    bool flag = true;
    for(int i=0; i < serialized.size(); i++) {
        if(serialized[i] != tx_true[i]) {
            flag = false;
            break;
        }
    }
    ASSERT_TRUE(flag);
}

TEST(txTest, SigningTransaction) {

}

#endif //BITCOIN_IN_CPP_TEST_TX_H
