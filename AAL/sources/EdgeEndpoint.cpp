//
// Created by hubert.legec on 2015-12-17.
//

#include <sstream>
#include "../headers/EdgeEndpoint.h"

using namespace std;

EdgeEndpoint::EdgeEndpoint() : Point2D() { }

EdgeEndpoint::EdgeEndpoint(const Point2D& point) : Point2D(point) {

}

EdgeEndpoint::EdgeEndpoint(const EdgeEndpoint &other) : Point2D(other) {
    this->type = other.type;
    this->pl = other.pl;
    this->inOut = other.inOut;
    this->inside = other.inside;
    this->left = other.left;
    this->secondEndpoint = other.secondEndpoint;
}

EdgeEndpoint& EdgeEndpoint::operator=(const EdgeEndpoint &other) {
    Point2D::operator=(other);
    this->type = other.type;
    this->pl = other.pl;
    this->inOut = other.inOut;
    this->inside = other.inside;
    this->left = other.left;
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
    this->pl = tl;
}

PolygonType EdgeEndpoint::getPolygonType() const {
    return pl;
}

void EdgeEndpoint::setSecondEndpoint(shared_ptr<EdgeEndpoint> secondEndpoint) {
    this->secondEndpoint = secondEndpoint;
}

shared_ptr<EdgeEndpoint> EdgeEndpoint::getSecondEndpoint() const {
    return this->secondEndpoint;
}

void EdgeEndpoint::setInsideOtherPolygonFlag(shared_ptr<EdgeEndpoint> prev) {
    if(prev == nullptr){
        inside = inOut = false;
    } else if(prev->pl == this->pl){
        inside = prev->inside;
        inOut = !prev->inOut;
    } else{
        inside = !prev->inOut;
        inOut = prev->inside;
    }
}

std::string EdgeEndpoint::toString() const {
    stringstream ss;
    ss << "EdgeEndpoint[(" << x << ", " << y << "), left:" << left << "]";
    return ss.str();
}