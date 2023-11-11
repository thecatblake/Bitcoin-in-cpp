//
// Created by ryousuke kaga on 2023/11/11.
//

#ifndef BITCOIN_IN_CPP_TEST_POINT_H
#define BITCOIN_IN_CPP_TEST_POINT_H

#include <gtest/gtest.h>
#include "Point.h"

TEST(PointTest, addition_with_inf) {
    Point p1(0, 0, 3, 7, true);
    Point p2(1, 2, 3, 7);

    Point t(1, 2, 3, 7);

    EXPECT_EQ(p1 + p2, t);
    EXPECT_EQ(p2 + p1, t);
}

TEST(PointTest, adding_inverse_return_inf) {
    Point p1(1, 2, 3, 7);
    Point p2(1, -2, 3, 7);

    Point t(0, 0, 3, 7, true);

    EXPECT_EQ(p1 + p2, t);
}

TEST(PointTest, adding_points_with_different_x) {
    Point p1(2, 5, 5, 7);
    Point p2(-1, -1, 5, 7);

    Point t(3, -7, 5, 7);

    EXPECT_EQ(p1 + p2, t);
}

TEST(PointTest, adding_points_with_the_same_point) {
    Point p(-1, -1, 5, 7);

    Point t(18, -77, 5, 7);

    EXPECT_EQ(p + p, t);
}

TEST(PointTest, adding_points_with_the_same_point_and_y_zero) {
    Point p(-1, 0, 2, 3);

    Point t(0, 0, 2, 3, true);

    EXPECT_EQ(p + p, t);
}

#endif //BITCOIN_IN_CPP_TEST_POINT_H
