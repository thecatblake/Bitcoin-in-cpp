//
// Created by ryousuke kaga on 2023/11/09.
//

#include "FiniteElement.h"
#include <vector>

int main() {

    // The outputs are all 1.
    int ps[] = {7, 11, 17, 31};

    for(auto p : ps) {
        std::vector<FiniteElement> f_set;
        for(int i=1; i <= p - 1; i++) {
            FiniteElement fe(i, p);
            f_set.push_back(fe.pow(p-1));
        }

        for(const auto& fe : f_set) {
            FiniteElement zero(0, p);
            std::cout << (fe + zero).num << " ";
        }

        std::cout << std::endl;
    }
}