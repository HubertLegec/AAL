/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "gtest/gtest.h"

#include "../AAL/headers/Executor.h"
#include "../AAL/headers/PrismGenerator.h"

TEST(Executor, executorSimpleTest){
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

    std::vector<Prism> p;
    PrismGenerator generator(false, 1000, 40);
    p = generator.generate();

    Executor executor(p);
    executor.execute();
    for(Prism p : executor.getWeilerAthertonOutput()){
        std::cout << p.toString() << std::endl;
    }
    std::cout << "wa time: " << executor.getSweepTime() << std::endl;
}