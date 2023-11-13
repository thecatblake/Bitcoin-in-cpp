//
// Created by ryousuke kaga on 2023/11/09.
//
#include <gtest/gtest.h>
#include "FieldElement.h"

TEST(FieldElementTest, f_57_plus_minus) {
    FieldElement fe1(44, 57);
    FieldElement fe2(33, 57);
    FieldElement fe3(9, 57);
    FieldElement fe4(29, 57);
    FieldElement fe5(52, 57);
    FieldElement fe6(30, 57);
    FieldElement fe7(38, 57);

    FieldElement t1(20, 57);
    FieldElement t2(37, 57);
    FieldElement t3(41, 57);

    EXPECT_EQ(fe1 + fe2, t1);
    EXPECT_EQ(fe3 - fe4, t2);
    EXPECT_EQ(fe5 - fe6 - fe7, t3);
}

TEST(FieldElementTest, f_97_mul) {
    FieldElement fe1(95, 97);
    FieldElement fe2(45, 97);
    FieldElement fe3(31, 97);
    FieldElement fe4(12, 97);
    FieldElement fe5(77, 97);

    FieldElement t1(23, 97);
    FieldElement t2(63, 97);

    EXPECT_EQ(fe1 * fe2 * fe3, t1);
    EXPECT_EQ(fe4.pow(7) * fe5.pow(49), t2);
}

TEST(FieldElementTest, f_31_div) {
    FieldElement fe1(3, 31);
    FieldElement fe2(24, 31);
    FieldElement fe3(17, 31);
    FieldElement fe4(4, 31);
    FieldElement fe5(11, 31);

    FieldElement t1(4, 31);
    FieldElement t2(29, 31);
    FieldElement t3(13, 31);

    EXPECT_EQ(fe1 / fe2, t1);
    EXPECT_EQ(fe3.pow(-3).check(), t2);
    EXPECT_EQ(fe4.pow(-4) * fe5, t3);
}

TEST(FieldElementTest, associativity) {
    FieldElement fe1(3, 31);
    FieldElement fe2(24, 31);
    FieldElement fe3(17, 31);

    EXPECT_EQ((fe1 + fe2) + fe3, fe1 + (fe2 + fe3));
}