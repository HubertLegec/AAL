/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef RING_SWEEPMETHOD_H
#define RING_SWEEPMETHOD_H

#include <vector>
#include <queue>
#include <deque>
#include "Prism.h"
#include "Collection.hpp"
#include "EdgeEndpoint.h"
#include "TempBuffer.h"
#include "Line2D.h"

class SweepMethod {
private:
    Prism firstPrism;
    Prism secondPrism;
    Collection<Prism> intersectionParts;
    Collection<Prism> clippedFirstPrism;
    Collection<Prism> clippedSecondPrism;

    double sweepLinePosition;
    std::priority_queue<std::shared_ptr<EdgeEndpoint>, std::vector<std::shared_ptr<EdgeEndpoint>>, EdgeEndpointComparator> Q;
    TempBuffer S;
    std::map<Point2D, std::shared_ptr<std::deque<Point2D>>> resultPartsBegin;
    std::map<Point2D, std::shared_ptr<std::deque<Point2D>>> resultPartsEnd;
    void initQ();
    void possibleIntersection(std::shared_ptr<EdgeEndpoint> first, std::shared_ptr<EdgeEndpoint> second);
    void addToIntersection(Point2D startPoint, Point2D endPoint);
    bool isValidIntersection(const Line2D& l1, const Line2D& l2, const Point2D& p, bool result);
public:
    SweepMethod(const Prism& firstPrism, const Prism& secondPrism);
    void doClipping();
    Collection<Prism> getIntersectionParts();
    Collection<Prism> getFirstPrismParts();
    Collection<Prism> getSecondPrismParts();
    Collection<Prism> getAllParts();
};


#endif //RING_SWEEPMETHOD_H
