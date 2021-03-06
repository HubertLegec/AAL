/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "gtest/gtest.h"

#include "../AAL/headers/PrismGenerator.h"

TEST(PrismGenerator, convexGeneration){
    PrismGenerator generator(true, 10, 10);

    std::vector<Prism> result = generator.generate();

    ASSERT_EQ(10, result.size());
    for(auto p : result){
        EXPECT_TRUE(p.getBase().getVertices().getSize() <= 10);
        std::cout << p.toString() << std::endl;
    }

}

