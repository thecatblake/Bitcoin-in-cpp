//
// Created by ryousuke kaga on 2023/11/09.
//
#include <gtest/gtest.h>
#include "FiniteElement.h"

TEST(FiniteElementTest, f_57_plus_minus) {
    FiniteElement fe1(44, 57);
    FiniteElement fe2(33, 57);
    FiniteElement fe3(9, 57);
    FiniteElement fe4(29, 57);
    FiniteElement fe5(52, 57);
    FiniteElement fe6(30, 57);
    FiniteElement fe7(38, 57);

    FiniteElement t1(20, 57);
    FiniteElement t2(37, 57);
    FiniteElement t3(41, 57);

    EXPECT_EQ(fe1 + fe2, t1);
    EXPECT_EQ(fe3 - fe4, t2);
    EXPECT_EQ(fe5 - fe6 - fe7, t3);
}

TEST(FiniteElementTest, f_97_mul) {
    FiniteElement fe1(95, 97);
    FiniteElement fe2(45, 97);
    FiniteElement fe3(31, 97);
    FiniteElement fe4(12, 97);
    FiniteElement fe5(77, 97);

    FiniteElement t1(23, 97);
    FiniteElement t2(63, 97);

    EXPECT_EQ(fe1 * fe2 * fe3, t1);
    EXPECT_EQ(fe4.pow(7) * fe5.pow(49), t2);
}

TEST(FiniteElementTest, f_31_div) {
    FiniteElement fe1(3, 31);
    FiniteElement fe2(24, 31);
    FiniteElement fe3(17, 31);
    FiniteElement fe4(4, 31);
    FiniteElement fe5(11, 31);

    FiniteElement t1(4, 31);
    FiniteElement t2(29, 31);
    FiniteElement t3(13, 31);

    EXPECT_EQ(fe1 / fe2, t1);
    EXPECT_EQ(fe3.pow(-3).check(), t2);
    EXPECT_EQ(fe4.pow(-4) * fe5, t3);
}