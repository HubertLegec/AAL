/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <sstream>
#include <iostream>
#include <cmath>
#include <limits>
#include "../headers/EdgeEndpoint.h"

using namespace std;

EdgeEndpoint::EdgeEndpoint() : Point2D() {
    this->left = false;
    this->inOut = false;
    this->inside = false;
    this->pl = SUBJECT;
}

EdgeEndpoint::EdgeEndpoint(const Point2D &point) : Point2D(point) {
    this->left = false;
    this->inOut = false;
    this->inside = false;
    this->pl = SUBJECT;
}

EdgeEndpoint::EdgeEndpoint(const Point2D &point, PolygonType polType) : Point2D(point) {
    this->pl = polType;
    this->left = false;
    this->inOut = false;
    this->inside = false;
}

EdgeEndpoint::EdgeEndpoint(const EdgeEndpoint &other) : Point2D(other) {
    this->pl = other.pl;
    this->inOut = other.inOut;
    this->inside = other.inside;
    this->left = other.left;
    this->secondEndpoint = other.secondEndpoint;
}

EdgeEndpoint &EdgeEndpoint::operator=(const EdgeEndpoint &other) {
    Point2D::operator=(other);
    this->pl = other.pl;
    this->inOut = other.inOut;
    this->inside = other.inside;
    this->left = other.left;
    this->secondEndpoint = other.secondEndpoint;
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
    if (prev == nullptr) {
        inside = inOut = false;
        secondEndpoint->inside = secondEndpoint->inOut = false;
    } else if (prev->pl == this->pl) {
        inside = prev->inside;
        secondEndpoint->inside = prev->inside;
        inOut = !prev->inOut;
        secondEndpoint->inOut = !prev->inOut;
    } else {
        inside = !prev->inOut;
        secondEndpoint->inside = !prev->inOut;
        inOut = prev->inside;
        secondEndpoint->inOut = prev->inside;
    }
}

bool EdgeEndpoint::operator==(const EdgeEndpoint &other) const {
    return Point2D::operator==(other) && this->left == other.left && this->pl == other.pl;
}

bool EdgeEndpoint::operator!=(const EdgeEndpoint &other) const {
    return !(*this == other);
}

float EdgeEndpoint::getIntersectionY(float x) const {
    if (approximatelyEqual(this->x, x)) {
        return this->y;
    } else if (approximatelyEqual(this->secondEndpoint->x, x)) {
        return this->secondEndpoint->x;
    } else {
        float dy = (this->y - this->secondEndpoint->y) / (this->x - secondEndpoint->x);
        return this->y + dy * fabs(this->x - x);
    }
}

bool EdgeEndpoint::isVertical() const {
    return approximatelyEqual(x, secondEndpoint->x) ? true : false;
}

bool EdgeEndpoint::isToTheLeftOf(const EdgeEndpoint &other) const {
    return graterThan(other.x, this->x) || (approximatelyEqual(this->x, other.x) && graterThan(other.y, this->y));
}

void EdgeEndpoint::joinToExistingEnd(std::shared_ptr<EdgeEndpoint> &other) {
    inside = other->inside;
    inOut = other->inOut;
    pl = other->pl;
    left = !other->left;
    secondEndpoint = other;
}

string EdgeEndpoint::toString() const {
    stringstream ss;
    ss << "EdgeEndpoint[(" << x << ", " << y << "), left:" << left << " inside: " << inside << " inOut: " << inOut <<
    " pt: " << pl << "]";
    return ss.str();
}