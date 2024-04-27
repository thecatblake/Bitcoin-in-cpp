//
// Created by ryousuke kaga on 2023/12/05.
//

#include "Script.h"

std::vector<unsigned char> p2pkh_script(const unsigned char *h160) {
    std::vector<unsigned char> out;
    out.resize(24);
    out[0] = 0x76;
    out[1] = 0xa9;
    for(int i=0; i < 20; i++) {
        out[2+i] = h160[i];
    }
    out[22] = 0x88;
    out[23] = 0xac;
    return out;
}
