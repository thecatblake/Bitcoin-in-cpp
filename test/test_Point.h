//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef BITCOIN_IN_CPP_TEST_POINT_H
#define BITCOIN_IN_CPP_TEST_POINT_H

#include <gtest/gtest.h>
#include "Point.h"

TEST(PointTest, addition_with_inf) {
    Point p1({0, 103}, {0, 103}, {3, 103}, {7, 103}, true);
    Point p2({1, 103}, {2, 103}, {3, 103}, {7, 103});

    Point t({1, 103}, {2, 103}, {3, 103}, {7, 103});

    ASSERT_TRUE(p1 + p2 == t);
    ASSERT_TRUE(p2 + p1 == t);
}

TEST(PointTest, adding_inverse_return_inf) {
    Point p1({-1, 103}, {-1, 103}, {5, 103}, {7, 103});
    Point p2({-1, 103}, {1, 103}, {5, 103}, {7, 103});

    Point t({0, 103}, {0, 103}, {5, 103}, {7, 103}, true);

    ASSERT_FALSE(p1.invalid);
    ASSERT_FALSE(p1.invalid);
    ASSERT_TRUE(p1 + p2 == t);
}

TEST(PointTest, adding_points_with_different_x) {
    Point p1({2, 103}, {5, 103}, {5, 103}, {7, 103});
    Point p2({-1, 103}, {-1, 103}, {5, 103}, {7, 103});

    Point t({3, 103}, {103-7, 103}, {5, 103}, {7, 103});

    ASSERT_FALSE(p1.invalid);
    ASSERT_FALSE(p2.invalid);

    ASSERT_TRUE(p1 + p2 == t);
}

TEST(PointTest, adding_points_with_the_same_point) {
    Point p({-1, 103}, {-1, 103}, {5, 103}, {7, 103});

    Point t({18, 103}, {77, 103}, {5, 103}, {7, 103});

    ASSERT_FALSE(p.invalid);

    ASSERT_TRUE(p + p == t);
}

TEST(PointTest, adding_points_with_the_same_point_and_y_zero) {
    Point p({-1, 103}, {0, 103}, {2, 103}, {3, 103});

    Point t({0, 103}, {0, 103}, {2, 103}, {3, 103}, true);

    EXPECT_EQ(p + p, t);
}

TEST(PointTest, additive_associativity) {
    FieldElement a(0, 223);
    FieldElement b(7, 223);
    Point p1({192, 223}, {105, 223}, a, b);
    Point p2({143, 223}, {98, 223}, a, b);
    Point p3({47, 223}, {71, 223}, a, b);

    EXPECT_EQ((p1 + p2) + p3, p1 + (p2 + p3));

    Point p4 = p1 + p2;

    EXPECT_EQ((p1 + p2) + p4, p1 + (p2 + p4));

    EXPECT_EQ(p1 + p2 + p1 + p2, p4 + p4);

    EXPECT_EQ(p2 + p2 + p2 + p2, (p2 + p2) + (p2 + p2));
}

TEST(PointTest, mutliplying_points) {
    FieldElement a(0, 223);
    FieldElement b(7, 223);
    Point p1({192, 223}, {105, 223}, a, b);
    Point t1({49, 223}, {71, 223}, a, b);
    Point p2({143, 223}, {98, 223}, a, b);
    Point t2({64, 223}, {168, 223}, a, b);
    Point p3({47, 223}, {71, 223}, a, b);
    Point t3({36, 223}, {111, 223}, a, b);
    Point t4({194, 223}, {51, 223}, a, b);
    Point t5({116, 223}, {55, 223}, a, b);
    Point t6({0, 223}, {0, 223}, a, b, true);

    EXPECT_EQ(2 * p1, t1);
    EXPECT_EQ(2 * p2, t2);
    EXPECT_EQ(2 * p3, t3);
}

#endif //BITCOIN_IN_CPP_TEST_POINT_H
