/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "gtest/gtest.h"

#include "../AAL/headers/WeilerAtherton.h"

using namespace std;
/*
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

    vector<Point2D> result;
    result.push_back(Point2D(3, 3));
    result.push_back(Point2D(5, 3));
    result.push_back(Point2D(5, 1));
    result.push_back(Point2D(3, 1));

    vector<Point2D> firstPart;
    firstPart.push_back(Point2D(3, 3));
    firstPart.push_back(Point2D(3, 1));
    firstPart.push_back(Point2D(1, 1));
    firstPart.push_back(Point2D(1, 3));

    vector<Point2D> secondPart;
    secondPart.push_back(Point2D(3, 3));
    secondPart.push_back(Point2D(3, 4));
    secondPart.push_back(Point2D(8, 4));
    secondPart.push_back(Point2D(8, 1));
    secondPart.push_back(Point2D(5, 1));
    secondPart.push_back(Point2D(5, 3));

    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();

    ASSERT_EQ(1, w1.getIntersectionParts().getSize());
    ASSERT_EQ(1, w1.getFirstParts().getSize());
    ASSERT_EQ(1, w1.getSecondParts().getSize());
    ASSERT_EQ(result.size(), w1.getIntersectionParts()[0].getBase().getVertices().getSize());
    ASSERT_EQ(firstPart.size(), w1.getFirstParts()[0].getBase().getVertices().getSize());
    ASSERT_EQ(secondPart.size(), w1.getSecondParts()[0].getBase().getVertices().getSize());
    for (Prism p : w1.getIntersectionParts()) {
        int i = 0;
        for (auto v : p.getVertexList()) {
            EXPECT_TRUE(v == result[i]);
            i++;
        }
    }

    for(int i = 0; i < firstPart.size(); i++){
        EXPECT_TRUE(firstPart[i] == w1.getFirstParts()[0].getVertexList()[i]);
    }

    for(int i = 0; i < secondPart.size(); i++){
        EXPECT_TRUE(secondPart[i] == w1.getSecondParts()[0].getVertexList()[i]);
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

    vector<Point2D> result1;
    result1.push_back(Point2D(4, 2.5));
    result1.push_back(Point2D(5, 3));
    result1.push_back(Point2D(4, 3));
    result1.push_back(Point2D(4, 4));
    result1.push_back(Point2D(6, 4));
    result1.push_back(Point2D(6, 1));
    result1.push_back(Point2D(4, 1));

    vector<Point2D> firstPart11;
    firstPart11.push_back(Point2D(4, 2.5));
    firstPart11.push_back(Point2D(4, 1));
    firstPart11.push_back(Point2D(1, 1));
    vector<Point2D> firstPart12;
    firstPart12.push_back(Point2D(6, 4));
    firstPart12.push_back(Point2D(4, 4));
    firstPart12.push_back(Point2D(4, 3));
    firstPart12.push_back(Point2D(1, 3));
    firstPart12.push_back(Point2D(1, 8));
    firstPart12.push_back(Point2D(6, 8));

    vector<Point2D> secondPart;
    secondPart.push_back(Point2D(6, 4));
    secondPart.push_back(Point2D(9, 4));
    secondPart.push_back(Point2D(9, -1));
    secondPart.push_back(Point2D(4, -1));
    secondPart.push_back(Point2D(4, 1));
    secondPart.push_back(Point2D(6, 1));


    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();
    ASSERT_EQ(1, w1.getIntersectionParts().getSize());
    ASSERT_EQ(2, w1.getFirstParts().getSize());
    ASSERT_EQ(1, w1.getSecondParts().getSize());
    ASSERT_EQ(result1.size(), w1.getIntersectionParts()[0].getVertexList().getSize());
    ASSERT_EQ(firstPart11.size(), w1.getFirstParts()[0].getVertexList().getSize());
    ASSERT_EQ(firstPart12.size(), w1.getFirstParts()[1].getVertexList().getSize());
    ASSERT_EQ(secondPart.size(), w1.getSecondParts()[0].getVertexList().getSize());
    for (Prism p : w1.getIntersectionParts()) {
        int i = 0;
        for (auto v : p.getBase().getVertices()) {
            EXPECT_TRUE(v == result1[i]);
            i++;
        }
    }

    for(int i = 0; i < firstPart11.size(); i++){
        EXPECT_TRUE(firstPart11[i] == w1.getFirstParts()[0].getVertexList()[i]);
    }

    for(int i = 0; i < firstPart12.size(); i++){
        EXPECT_TRUE(firstPart12[i] == w1.getFirstParts()[1].getVertexList()[i]);
    }

    for(int i = 0; i < secondPart.size(); i++){
        EXPECT_TRUE(secondPart[i] == w1.getSecondParts()[0].getVertexList()[i]);
    }

}

TEST(WeilerAtherton, clippingMediumTest2){
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

    vector<Point2D> result21;
    result21.push_back(Point2D(7, 11));
    result21.push_back(Point2D(9, 11));
    result21.push_back(Point2D(8, 9));
    result21.push_back(Point2D(7, 8.75));
    vector<Point2D> result22;
    result22.push_back(Point2D(7, 7.4));
    result22.push_back(Point2D(9, 7));
    result22.push_back(Point2D(8 + 1.0 / 3.0, 5));
    result22.push_back(Point2D(7, 5));

    vector<Point2D> firstPart;
    firstPart.push_back(Point2D(7, 11));
    firstPart.push_back(Point2D(7, 8.75));
    firstPart.push_back(Point2D(4, 8));
    firstPart.push_back(Point2D(7, 7.4));
    firstPart.push_back(Point2D(7, 5));
    firstPart.push_back(Point2D(8 + 1.0 / 3.0, 5));
    firstPart.push_back(Point2D(7, 1));
    firstPart.push_back(Point2D(1, 11));

    vector<Point2D> secondPart;
    secondPart.push_back(Point2D(7, 11));
    secondPart.push_back(Point2D(7, 12));
    secondPart.push_back(Point2D(11, 12));
    secondPart.push_back(Point2D(11, 5));
    secondPart.push_back(Point2D(8 + 1.0 / 3.0, 5));
    secondPart.push_back(Point2D(9, 7));
    secondPart.push_back(Point2D(7, 7.4));
    secondPart.push_back(Point2D(7, 8.75));
    secondPart.push_back(Point2D(8, 9));
    secondPart.push_back(Point2D(9, 11));



    WeilerAtherton w2(Prism(2, 1, 2, pol3), Prism(3, 2, 3, pol4));
    w2.doWeilerAtherton();
    ASSERT_EQ(2, w2.getIntersectionParts().getSize());
    ASSERT_EQ(1, w2.getFirstParts().getSize());
    ASSERT_EQ(1, w2.getSecondParts().getSize());
    ASSERT_EQ(result21.size(), w2.getIntersectionParts()[0].getVertexList().getSize());
    ASSERT_EQ(result22.size(), w2.getIntersectionParts()[1].getVertexList().getSize());
    ASSERT_EQ(firstPart.size(), w2.getFirstParts()[0].getVertexList().getSize());
    ASSERT_EQ(secondPart.size(), w2.getSecondParts()[0].getVertexList().getSize());
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

    for(int i = 0; i < firstPart.size(); i++){
        EXPECT_TRUE(firstPart[i] == w2.getFirstParts()[0].getVertexList()[i]);
    }

    for(int i = 0; i < secondPart.size(); i++){
        EXPECT_TRUE(secondPart[i] == w2.getSecondParts()[0].getVertexList()[i]);
    }
}


TEST(WeilerAtherton, clippingSophisticatedTest) {
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


    vector<Point2D> result;
    result.push_back(Point2D(4, 8));
    result.push_back(Point2D(4, 7));
    result.push_back(Point2D(4.6, 8));
    result.push_back(Point2D(7.4, 8));
    result.push_back(Point2D(8, 2));
    result.push_back(Point2D(4 + 1.0/3.0, 2));
    result.push_back(Point2D(5, 4));
    result.push_back(Point2D(3, 8));

    vector<Point2D> result2;
    result2.push_back(Point2D(5.96552, 10.2759));
    result2.push_back(Point2D(6.4, 11));
    result2.push_back(Point2D(7.1, 11));
    result2.push_back(Point2D(7.27027, 9.2973));

    vector<Point2D> firstPart1;

    WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    w1.doWeilerAtherton();
    ASSERT_EQ(2, w1.getIntersectionParts().getSize());
    ASSERT_EQ(3, w1.getFirstParts().getSize());
    ASSERT_EQ(2, w1.getSecondParts().getSize());
    ASSERT_EQ(result.size(), w1.getIntersectionParts()[0].getBase().getVertices().getSize());
    ASSERT_EQ(result2.size(), w1.getIntersectionParts()[1].getBase().getVertices().getSize());
    ASSERT_EQ(7, w1.getFirstParts()[0].getVertexList().getSize());
    ASSERT_EQ(4, w1.getFirstParts()[1].getVertexList().getSize());
    ASSERT_EQ(3, w1.getFirstParts()[2].getVertexList().getSize());
    ASSERT_EQ(9, w1.getSecondParts()[0].getVertexList().getSize());
    ASSERT_EQ(3, w1.getSecondParts()[1].getVertexList().getSize());

    Prism p = w1.getIntersectionParts()[0];
    int i = 0;
    for (auto v : p.getBase().getVertices()) {
        EXPECT_TRUE(v == result[i]);
        i++;
    }
    Prism p2 = w1.getIntersectionParts()[1];
    i = 0;
    for (auto v : p2.getBase().getVertices()) {
        EXPECT_TRUE(v == result2[i] || i == 0 || i == 3);
        i++;
    }
}
*/
TEST(WeilerAtherton, xTest){
    Polygon pol1;
    pol1.add(Point2D(2, 2));
    pol1.add(Point2D(2, 8));
    pol1.add(Point2D(8, 8));
    pol1.add(Point2D(8, 2));
    Polygon pol2;
    pol2.add(Point2D(5, 5));
    pol2.add(Point2D(-2, -2));
    pol2.add(Point2D(0, 0));

    WeilerAtherton wa(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
    wa.doWeilerAtherton();

    EXPECT_EQ(1, wa.getIntersectionParts().getSize());
    EXPECT_EQ(3, wa.getIntersectionParts()[0].getVertexList().getSize());
}
