//
// Created by ryousuke kaga on 2023/12/05.
//

#ifndef BITCOIN_IN_CPP_SCRIPT_H
#define BITCOIN_IN_CPP_SCRIPT_H

#include <vector>

class Script {
public:
    Script();
};

std::vector<unsigned char> p2pkh_script(const unsigned char h160[20]);


#endif //BITCOIN_IN_CPP_SCRIPT_H
