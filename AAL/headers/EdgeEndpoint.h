//
// Created by hubert.legec on 2015-12-17.
//

#ifndef RING_EDGEENDPOINT_H
#define RING_EDGEENDPOINT_H

#include "Point2D.h"

enum PolygonType{
    SUBJECT = 0,
    CLIPPING = 1
};

enum EdgeType{

};

class EdgeEndpoint : public Point2D{
private:
    EdgeEndpoint* secondEndpoint;
    bool left;
    bool inOut;
    bool inside;
    EdgeType type;
    PolygonType tl;
public:
    EdgeEndpoint();
    EdgeEndpoint(Point2D point);
    EdgeEndpoint(const EdgeEndpoint& other);
    EdgeEndpoint& operator=(const EdgeEndpoint& other);
    void setSecondEndpoint(EdgeEndpoint* secondEndpoint);
    EdgeEndpoint* getSecondEndpoint() const;
    void setLeft(bool left);
    bool isLeft() const;
    void setInOut(bool inOut);
    bool isInOut() const;
    void setInside(bool inside);
    bool isInside() const;
    void setEdgeType(EdgeType type);
    EdgeType getEdgeType() const;
    void setPolygonType(PolygonType tl);
    PolygonType getPolygonType() const;
};


#endif //RING_EDGEENDPOINT_H
