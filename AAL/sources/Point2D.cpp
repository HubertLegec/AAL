/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "../headers/Point2D.h"

#include <cmath>
#include <limits>
#include <sstream>

using namespace std;

Point2D::Point2D(float x, float y, bool intersectionPoint) : x(x), y(y), intersectionPoint(intersectionPoint) {

}

Point2D::Point2D(const Point2D &other) {
    this->x = other.x;
    this->y = other.y;
    this->intersectionPoint = other.intersectionPoint;
    this->visited = other.visited;
    this->firstPartAdded = other.firstPartAdded;
    this->secondPartAdded = other.secondPartAdded;
}

Point2D &Point2D::operator=(const Point2D &other) {
    this->x = other.x;
    this->y = other.y;
    this->intersectionPoint = other.intersectionPoint;
    this->visited = other.visited;
    this->firstPartAdded = other.firstPartAdded;
    this->secondPartAdded = other.secondPartAdded;
    return *this;
}

bool Point2D::operator==(const Point2D &other) const {
    return fabs(this->x - other.x) <= numeric_limits<float>::epsilon() * max(1.0f, max(this->x, other.x)) * 5
           && fabs(this->y - other.y) <= numeric_limits<float>::epsilon() * max(1.0f, max(this->y, other.y)) * 5;
}

bool Point2D::operator!=(const Point2D &other) const {
    return !(*this == other);
}

bool Point2D::operator<(const Point2D &other) const {
    if (graterThan(other.x, x)) return true;
    if (graterThan(x, other.x)) return false;
    if (graterThan(other.y, y)) return true;
    return false;
}

float Point2D::getDistance(const Point2D &other) const {
    float dx = other.getX() - x;
    float dy = other.getY() - y;
    return hypot(dx, dy);
}

void Point2D::setX(float x) {
    this->x = x;
}

void Point2D::setY(float y) {
    this->y = y;
}

float Point2D::getX() const {
    return x;
}

float Point2D::getY() const {
    return y;
}

bool Point2D::isIntersectionPoint() const {
    return intersectionPoint;
}

void Point2D::setIntersectionPoint(bool intersectionPoint) {
    this->intersectionPoint = intersectionPoint;
}

bool Point2D::isVisited() const {
    return visited;
}

void Point2D::setVisited(bool visited) {
    this->visited = visited;
}

bool Point2D::isFirstPartAdded() const {
    return firstPartAdded;
}

void Point2D::setFirstPartAdded(bool firstPartAdded) {
    this->firstPartAdded = firstPartAdded;
}

bool Point2D::isSecondPartAdded() const {
    return secondPartAdded;
}

void Point2D::setSecondPartAdded(bool secondPartAdded) {
    this->secondPartAdded = secondPartAdded;
}

string Point2D::toString() const {
    stringstream result;
    result << "Point2D(" << x << "," << y << "), inters: " << intersectionPoint << "]";
    return result.str();
}

bool Point2D::approximatelyEqual(float a, float b) {
    return fabs(a - b) <= max(fabs(a), fabs(b)) * numeric_limits<float>::epsilon();
}

bool Point2D::graterThan(float a, float b) {
    float eps = max(1.0f, max(fabs(a), fabs(b)));
    return (a - b) > numeric_limits<float>::epsilon() * eps;
}