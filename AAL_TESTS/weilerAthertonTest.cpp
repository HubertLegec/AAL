//
// Created by hubert.legec on 2015-12-10.
//

#include "gtest/gtest.h"

#include "../AAL/headers/WeilerAtherton.h"

TEST(WeilerAtherton, convexClippingSimpleTest) {
    Polygon pol1;
    pol1.add(Point2D(1, 1));
    pol1.add(Point2D(1, 3));
    pol1.add(Point2D(5, 3));
    pol1.add(Point2D(5, 1));
    Polygon pol2;
    pol2.add(Point2D(3, 1));
    pol2.add(Point2D(3, 4));
    pol2.add(Point2D(8, 4));
    pol2.add(Point2D(8, 1));

    std::vector<Point2D> result;
    result.push_back(Point2D(3, 3));
    result.push_back(Point2D(5, 3));
    result.push_back(Point2D(5, 1));
    result.push_back(Point2D(3, 1));


    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();

    ASSERT_EQ(1, w1.getIntersectionParts().getSize());
    ASSERT_EQ(result.size(), w1.getIntersectionParts()[0].getBase().getVertices().getSize());
    for (Prism p : w1.getIntersectionParts()) {
        int i = 0;
        for (auto v : p.getBase().getVertices()) {
            EXPECT_TRUE(v == result[i]);
            i++;
        }
    }

}

TEST(WeilerAtherton, clippingMediumTest) {
    Polygon pol1;
    pol1.add(Point2D(1, 1));
    pol1.add(Point2D(5, 3));
    pol1.add(Point2D(1, 3));
    pol1.add(Point2D(1, 8));
    pol1.add(Point2D(6, 8));
    pol1.add(Point2D(6, 1));
    Polygon pol2;
    pol2.add(Point2D(4, -1));
    pol2.add(Point2D(4, 4));
    pol2.add(Point2D(9, 4));
    pol2.add(Point2D(9, -1));

    Polygon pol3;
    pol3.add(Point2D(7, 1));
    pol3.add(Point2D(1, 11));
    pol3.add(Point2D(9, 11));
    pol3.add(Point2D(8, 9));
    pol3.add(Point2D(4, 8));
    pol3.add(Point2D(9, 7));
    Polygon pol4;
    pol4.add(Point2D(7, 12));
    pol4.add(Point2D(11, 12));
    pol4.add(Point2D(11, 5));
    pol4.add(Point2D(7, 5));

    std::vector<Point2D> result;
    result.push_back(Point2D(4, 2.5));
    result.push_back(Point2D(5, 3));
    result.push_back(Point2D(4, 3));
    result.push_back(Point2D(4, 4));
    result.push_back(Point2D(6, 4));
    result.push_back(Point2D(6, 1));
    result.push_back(Point2D(4, 1));

    std::vector<Point2D> result21;
    result21.push_back(Point2D(7, 11));
    result21.push_back(Point2D(9, 11));
    result21.push_back(Point2D(8, 9));
    result21.push_back(Point2D(7, 8.75));
    std::vector<Point2D> result22;
    result22.push_back(Point2D(7, 7.4));
    result22.push_back(Point2D(9, 7));
    result22.push_back(Point2D(8 + 1.0 / 3.0, 5));
    result22.push_back(Point2D(7, 5));


    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();
    ASSERT_EQ(1, w1.getIntersectionParts().getSize());
    ASSERT_EQ(result.size(), w1.getIntersectionParts()[0].getBase().getVertices().getSize());
    for (Prism p : w1.getIntersectionParts()) {
        int i = 0;
        for (auto v : p.getBase().getVertices()) {
            EXPECT_TRUE(v == result[i]);
            i++;
        }
    }


    WeilerAtherton w2(Prism(2, 1, 2, pol3), Prism(3, 2, 3, pol4));
    w2.doWeilerAtherton();
    ASSERT_EQ(2, w2.getIntersectionParts().getSize());
    ASSERT_EQ(result21.size(), w2.getIntersectionParts()[0].getBase().getVertices().getSize());
    ASSERT_EQ(result22.size(), w2.getIntersectionParts()[1].getBase().getVertices().getSize());
    Prism p = w2.getIntersectionParts()[0];
    int i = 0;
    for (auto v : p.getBase().getVertices()) {
        EXPECT_TRUE(v == result21[i]);
        i++;
    }
    Prism p2 = w2.getIntersectionParts()[1];
    i = 0;
    for (auto v : p2.getBase().getVertices()) {
        EXPECT_TRUE(v == result22[i]);
        i++;
    }
}

TEST(WeilerAtherton, clippingSophisticatedTest) {
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    Polygon pol1;
    pol1.add(Point2D(8, 2));
    pol1.add(Point2D(2, 2));
    pol1.add(Point2D(2, 9));
    pol1.add(Point2D(4, 12));
    pol1.add(Point2D(4, 7));
    pol1.add(Point2D(7, 12));
    Polygon pol2;
    pol2.add(Point2D(3, 8));
    pol2.add(Point2D(9, 8));
    pol2.add(Point2D(5, 11));
    pol2.add(Point2D(10, 11));
    pol2.add(Point2D(10, 1));
    pol2.add(Point2D(4, 1));
    pol2.add(Point2D(5, 4));


    //TODO
    std::vector<Point2D> result;
    result.push_back(Point2D(4, 8));
    result.push_back(Point2D(4, 7));
    result.push_back(Point2D(5, 8));
    result.push_back(Point2D(4, 4));
    result.push_back(Point2D(6, 4));
    result.push_back(Point2D(6, 1));
    result.push_back(Point2D(4, 1));
    result.push_back(Point2D(4, 1));

    std::vector<Point2D> result2;
    result2.push_back(Point2D(4, 2.5));
    result2.push_back(Point2D(5, 3));
    result2.push_back(Point2D(4, 3));
    result2.push_back(Point2D(4, 4));

    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();
    ASSERT_EQ(2, w1.getIntersectionParts().getSize());
    ASSERT_EQ(result.size(), w1.getIntersectionParts()[0].getBase().getVertices().getSize());
    ASSERT_EQ(result2.size(), w1.getIntersectionParts()[1].getBase().getVertices().getSize());
}
