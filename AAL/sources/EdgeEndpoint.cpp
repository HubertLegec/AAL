//
// Created by hubert.legec on 2015-12-17.
//

#include "../headers/EdgeEndpoint.h"

EdgeEndpoint::EdgeEndpoint() : Point2D() { }

EdgeEndpoint::EdgeEndpoint(Point2D point) : Point2D(point){

}

EdgeEndpoint::EdgeEndpoint(const EdgeEndpoint &other) : Point2D(other){
    this->type = other.type;
    this->tl = other.tl;
    this->inOut = other.inOut;
    this->inside = other.inside;
    this->left = left;
    this->secondEndpoint = other.secondEndpoint;
}

void EdgeEndpoint::setEdgeType(EdgeType type) {
    this->type = type;
}

EdgeType EdgeEndpoint::getEdgeType() const {
    return type;
}

void EdgeEndpoint::setInOut(bool inOut) {
    this->inOut = inOut;
}

bool EdgeEndpoint::isInOut() const {
    return inOut;
}

void EdgeEndpoint::setInside(bool inside) {
    this->inside = inside;
}

bool EdgeEndpoint::isInside() const {
    return inside;
}

void EdgeEndpoint::setLeft(bool left) {
    this->left = left;
}

bool EdgeEndpoint::isLeft() const {
    return left;
}

void EdgeEndpoint::setPolygonType(PolygonType tl) {
    this->tl = tl;
}

PolygonType EdgeEndpoint::getPolygonType() const {
    return tl;
}

void EdgeEndpoint::setSecondEndpoint(EdgeEndpoint *secondEndpoint) {
    this->secondEndpoint = secondEndpoint;
}

EdgeEndpoint* EdgeEndpoint::getSecondEndpoint() const {
    return this->secondEndpoint
}