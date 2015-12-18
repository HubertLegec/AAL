//
// Created by hubert.legec on 2015-12-16.
//

#ifndef RING_SWEEPMETHOD_H
#define RING_SWEEPMETHOD_H

#include <vector>
#include <queue>
#include "Prism.h"
#include "Collection.hpp"

class SweepMethod {
private:
    Prism firstPrism;
    Prism secondPrism;
    Collection<Prism> intersectionParts;
    Collection<Prism> clippedFirstPrism;
    Collection<Prism> clippedSecondPrism;
    bool isValid = false;

    double sweepLinePosition;
    std::priority_queue<> S;
public:
    SweepMethod(const Prism& firstPrism, const Prism& secondPrism);
    void doClipping();
    std::vector<Prism> getIntersectionParts();
    std::vector<Prism> getFirstPrismParts();
    std::vector<Prism> getSecondPrismParts();
    std::vector<Prism> getAllParts();
};


#endif //RING_SWEEPMETHOD_H
