//
// Created by hubert.legec on 2016-01-11.
//

#include "gtest/gtest.h"
#include "../AAL/headers/SweepMethod.h"

using namespace std;

TEST(SweepMethod, simpleTest1){
    Polygon pol1;
    pol1.add(Point2D(1, 6));
    pol1.add(Point2D(10, 7));
    pol1.add(Point2D(9, 2));
    Polygon pol2;
    pol2.add(Point2D(3, 3));
    pol2.add(Point2D(8, 5));
    pol2.add(Point2D(14, -2));

    SweepMethod sm1(Prism(1, 2, 8, pol1), Prism(2, 5, 12, pol2));
    sm1.doClipping();


    ASSERT_EQ(1, sm1.getIntersectionParts().getSize());
    ASSERT_EQ(4, sm1.getIntersectionParts()[0].getVertexList().getSize());

    for(auto v : sm1.getIntersectionParts().getItems()){
        cout << v.toString() << endl;
    }
}

TEST(SweepMethod, simlpeTest2){
    Polygon pol1;
    pol1.add(Point2D(1, 1));
    pol1.add(Point2D(1, 3));
    pol1.add(Point2D(5, 3));
    pol1.add(Point2D(5, 1));
    Polygon pol2;
    pol2.add(Point2D(2, 2));
    pol2.add(Point2D(2, 5));
    pol2.add(Point2D(6, 5));
    pol2.add(Point2D(6, 2));

    SweepMethod sweepMethod(Prism(1, 3, 5, pol1), Prism(2, 6, 9, pol2));
    sweepMethod.doClipping();

    ASSERT_EQ(1, sweepMethod.getIntersectionParts().getSize());
    ASSERT_EQ(4, sweepMethod.getIntersectionParts()[0].getVertexList().getSize());

    for(auto v : sweepMethod.getIntersectionParts().getItems()){
        cout << v.toString() << endl;
    }
}


TEST(SweepMethod, mediumTest1){
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

    SweepMethod sweepMethod(Prism(1, 3, 5, pol3), Prism(2, 6, 9, pol4));
    sweepMethod.doClipping();

    ASSERT_EQ(2, sweepMethod.getIntersectionParts().getSize());
    ASSERT_EQ(result21.size(), sweepMethod.getIntersectionParts()[0].getVertexList().getSize());
    ASSERT_EQ(result22.size(), sweepMethod.getIntersectionParts()[1].getVertexList().getSize());

}

TEST(SweepMethod, mediumTest2){
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

    SweepMethod sweepMethod(Prism(1, 3, 5, pol1), Prism(2, 6, 9, pol2));
    sweepMethod.doClipping();

    ASSERT_EQ(1, sweepMethod.getIntersectionParts().getSize());
    ASSERT_EQ(result1.size(), sweepMethod.getIntersectionParts()[0].getVertexList().getSize());
}

TEST(SweepMethod, mediumTest3){
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

    SweepMethod sweepMethod(Prism(1, 3, 5, pol1), Prism(2, 6, 9, pol2));
    sweepMethod.doClipping();

    ASSERT_EQ(1, sweepMethod.getIntersectionParts().getSize());
    ASSERT_EQ(result.size(), sweepMethod.getIntersectionParts()[0].getVertexList().getSize());
}

/*
TEST(SweepMethod, sophisticatedTest){
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

    SweepMethod sweepMethod(Prism(1, 3, 5, pol1), Prism(2, 6, 9, pol2));
    sweepMethod.doClipping();

    ASSERT_EQ(3, sweepMethod.getIntersectionParts().getSize());
}*/