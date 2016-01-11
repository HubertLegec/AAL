//
// Created by hubert.legec on 2016-01-11.
//

#include "gtest/gtest.h"

#include "../AAL/headers/SweepMethod.h"

TEST(SweepMethod, q_test){
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

    SweepMethod sweepMethod(Prism(1, 3, 5, pol1), Prism(2, 6, 9, pol2));
    sweepMethod.doClipping();

}