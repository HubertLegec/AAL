#include "../headers/Point2D.h"

#include <cmath>
#include <sstream>

using namespace std;

Point2D::Point2D(double x, double y, bool intersectionPoint, bool visited) : x(x), y(y),
                                                                             intersectionPoint(intersectionPoint),
                                                                             visited(visited) {

}

Point2D::Point2D(const Point2D &other) {
    this->x = other.x;
    this->y = other.y;
    this->intersectionPoint = other.intersectionPoint;
    this->visited = other.visited;
}

Point2D &Point2D::operator=(const Point2D &other) {
    this->x = other.x;
    this->y = other.y;
    this->intersectionPoint = other.intersectionPoint;
    this->visited = other.visited;
    return *this;
}

bool Point2D::operator==(const Point2D &other) const {
    return (this->x == other.x) && (this->y == other.y);
}

bool Point2D::operator!=(const Point2D &other) const {
    return !(*this == other);
}

double Point2D::getDistance(const Point2D &other) const {
    double dx = other.getX() - x;
    double dy = other.getY() - y;
    return hypot(dx, dy);
}

void Point2D::setX(double x) {
    this->x = x;
}

void Point2D::setY(double y) {
    this->y = y;
}

double Point2D::getX() const {
    return x;
}

double Point2D::getY() const {
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
    result << "Point2D[(" << x << "," << y << "), isp: " << intersectionPoint << ", v: " << visited << "]";
    return result.str();
}