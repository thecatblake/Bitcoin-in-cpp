//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FieldElement.h"
#include <vector>

int main() {

    // The outputs are all 1.
    int ps[] = {7, 11, 17, 31};

    for(auto p : ps) {
        std::vector<FieldElement> f_set;
        for(int i=1; i <= p - 1; i++) {
            FieldElement fe(i, p);
            f_set.push_back(fe.pow(p-1));
        }

        for(const auto& fe : f_set) {
            FieldElement zero(0, p);
            std::cout << (fe + zero).num << " ";
        }

        std::cout << std::endl;
    }
}