/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef RING_EDGEENDPOINT_H
#define RING_EDGEENDPOINT_H

#include <memory>
#include <limits>
#include <cmath>
#include "Point2D.h"

using namespace std;

enum PolygonType {
    SUBJECT = 0,
    CLIPPING = 1
};

enum EdgeType {
    DEFAULT = 0
};

class EdgeEndpoint : public Point2D {
private:
    std::shared_ptr<EdgeEndpoint> secondEndpoint;
    bool left;
    bool inOut;
    bool inside;
    EdgeType type;
    PolygonType pl;
public:
    EdgeEndpoint();

    EdgeEndpoint(const Point2D &point);

    EdgeEndpoint(const EdgeEndpoint &other);

    EdgeEndpoint &operator=(const EdgeEndpoint &other);

    bool operator==(const EdgeEndpoint& other) const;

    bool operator!=(const EdgeEndpoint& other) const;

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

    void setPolygonType(PolygonType pl);

    PolygonType getPolygonType() const;

    void setInsideOtherPolygonFlag(std::shared_ptr<EdgeEndpoint> prev);

    float getIntersectionY(float x) const;

    bool isVertical() const;

    std::string toString() const;
};

struct EdgeEndpointComparator {
    bool operator()(const std::shared_ptr<EdgeEndpoint>& eep1, const std::shared_ptr<EdgeEndpoint>& eep2) {
        //x rosnaco
        if (graterThan(eep1->getX(), eep2->getX())) return true;

        if (graterThan(eep2->getX(), eep1->getX())) return false;

        //y rosnaco
        if (graterThan(eep1->getY(), eep2->getY())) return true;

        if (graterThan(eep2->getY(), eep1->getY())) return false;

        if(!eep1->isLeft() && eep2->isLeft()) return false;

        if(eep1->isLeft() && !eep2->isLeft()) return true;

        if(eep1->isLeft() && eep2->isLeft() && eep1->isVertical() && !eep2->isVertical()){
            return true;
        }

        if(eep1->isLeft() && eep2->isLeft() && !eep1->isVertical() && eep2->isVertical()){
            return false;
        }

        if(!eep1->isLeft() && !eep2->isLeft() && eep1->isVertical() && !eep2->isVertical()){
            return false;
        }

        if(!eep1->isLeft() && !eep2->isLeft() && !eep1->isVertical() && eep2->isVertical()){
            return true;
        }

        if(eep1->isLeft() && eep2->isLeft() && eep1->isVertical() && eep2->isVertical()){
            if(eep1->getSecondEndpoint()->getY() > eep2->getSecondEndpoint()->getY()){
                return true;
            }
            if(eep1->getSecondEndpoint()->getY() < eep2->getSecondEndpoint()->getY()){
                return false;
            }
        }

        if(!eep1->isLeft() && !eep2->isLeft() && eep1->isVertical() && eep2->isVertical()){
            if(eep1->getSecondEndpoint()->getY() > eep2->getSecondEndpoint()->getY()){
                return false;
            }
            if(eep1->getSecondEndpoint()->getY() < eep2->getSecondEndpoint()->getY()){
                return true;
            }
        }

        //według rosnącego y drugiego końca krawędzi
        if(eep1->getSecondEndpoint()->getY() >= eep2->getSecondEndpoint()->getY()) return true;

        return false;
    }

    static bool graterThan(float a, float b){
        float eps = max(1.0f, max(fabs(a), fabs(b)));
        return (a - b) > numeric_limits<float>::epsilon()*eps;
    }
};


#endif //RING_EDGEENDPOINT_H
