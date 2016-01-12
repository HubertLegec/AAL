//
// Created by hubert.legec on 2015-12-16.
//

#ifndef RING_SWEEPMETHOD_H
#define RING_SWEEPMETHOD_H

#include <vector>
#include <queue>
#include "Prism.h"
#include "Collection.hpp"
#include "EdgeEndpoint.h"

class TempBuffer{
private:
    std::vector<std::shared_ptr<EdgeEndpoint>> elements;
public:
    TempBuffer();
    std::shared_ptr<EdgeEndpoint> insert(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> find(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> prev(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> next(std::shared_ptr<EdgeEndpoint> endpoint);
    void erase(std::shared_ptr<EdgeEndpoint> endpoint);
};


class SweepMethod {
private:
    Prism firstPrism;
    Prism secondPrism;
    Collection<Prism> intersectionParts;
    Collection<Prism> clippedFirstPrism;
    Collection<Prism> clippedSecondPrism;
    bool isValid = false;

    double sweepLinePosition;
    std::priority_queue<std::shared_ptr<EdgeEndpoint>, std::vector<std::shared_ptr<EdgeEndpoint>>, EdgeEndpointComparator> Q;
    TempBuffer S;
    void initQ();
    void possibleIntersection(std::shared_ptr<EdgeEndpoint> fir, std::shared_ptr<EdgeEndpoint> sec);
    void addToIntersection(Point2D startPoint, Point2D endPoint);
public:
    SweepMethod(const Prism& firstPrism, const Prism& secondPrism);
    void doClipping();
    Collection<Prism> getIntersectionParts();
    Collection<Prism> getFirstPrismParts();
    Collection<Prism> getSecondPrismParts();
    Collection<Prism> getAllParts();
};


#endif //RING_SWEEPMETHOD_H
