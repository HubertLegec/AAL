//
// Created by hubert.legec on 2016-01-11.
//

#include "gtest/gtest.h"

#include "../AAL/headers/SweepMethod.h"

using namespace std;

/*
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
*/

/*
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
*/

TEST(SweepMethod, simpleTest3){
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

}