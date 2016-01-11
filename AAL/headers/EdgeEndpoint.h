//
// Created by hubert.legec on 2015-12-17.
//

#ifndef RING_EDGEENDPOINT_H
#define RING_EDGEENDPOINT_H

#include <memory>
#include "Point2D.h"

enum PolygonType{
    SUBJECT = 0,
    CLIPPING = 1
};

enum EdgeType{

};

class EdgeEndpoint : public Point2D{
private:
    std::shared_ptr<EdgeEndpoint> secondEndpoint;
    bool left;
    bool inOut;
    bool inside;
    EdgeType type;
    PolygonType tl;
public:
    EdgeEndpoint();
    EdgeEndpoint(const Point2D& point);
    EdgeEndpoint(const EdgeEndpoint& other);
    EdgeEndpoint& operator=(const EdgeEndpoint& other);
    void setSecondEndpoint(std::shared_ptr<EdgeEndpoint> secondEndpoint);
    std::shared_ptr<EdgeEndpoint> getSecondEndpoint() const;
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
    std::string toString() const;
};

struct EdgeEndpointComparator
{
    bool operator ()(std::shared_ptr<EdgeEndpoint> eep1, std::shared_ptr<EdgeEndpoint> eep2 )
    {
        //x rosnaco
        if( eep1->getX() > eep2->getX() ) return true;

        if( eep1->getX() < eep2->getX() ) return false;

        //y rosnaco
        if( eep1->getY() > eep2->getY() ) return true;

        if( eep1->getY() < eep2->getY() ) return false;

        return false;
    }
};


#endif //RING_EDGEENDPOINT_H
