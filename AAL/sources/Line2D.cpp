/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <sstream>
#include <cmath>
#include <iostream>
#include <limits>
#include "../headers/Line2D.h"

using namespace std;

Line2D::Line2D() {

}

Line2D::Line2D(float x1, float y1, float x2, float y2) {
    this->start = Point2D(x1, y1);
    this->end = Point2D(x2, y2);
}

Line2D::Line2D(const Point2D &start, const Point2D &end) {
    this->start = start;
    this->end = end;
}

Line2D::Line2D(const Line2D &other) {
    this->start = other.getStart();
    this->end = other.getEnd();
}

Vector2D Line2D::getVector2D() const {
    return Vector2D(end.getX() - start.getX(), end.getY() - start.getY());
}

Line2D &Line2D::operator=(const Line2D &other) {
    this->start = other.start;
    this->end = other.end;
    return *this;
}

void Line2D::setStart(const Point2D &start) {
    this->start = start;
}

void Line2D::setEnd(const Point2D &end) {
    this->end = end;
}

Point2D Line2D::getStart() const {
    return start;
}

Point2D Line2D::getEnd() const {
    return end;
}

bool Line2D::isOnSegment(const Point2D &start, const Point2D &end, const Point2D &pointToCheck) {
    float x1 = start.getX();
    float y1 = start.getY();
    float x2 = end.getX();
    float y2 = end.getY();
    if (pointToCheck.getX() <= max(x1, x2) && pointToCheck.getX() >= min(x1, x2)
        && pointToCheck.getY() <= max(y1, y2) && pointToCheck.getY() >= min(y1, y2)) {
        return true;
    }
    else {
        return false;
    }
}

bool Line2D::isOnLine(const Point2D &pointToCheck) const {
    float lenght = start.getDistance(end);
    if (fabs(start.getDistance(pointToCheck) + pointToCheck.getDistance(end) - lenght) <= numeric_limits<float>::epsilon()*lenght) {
        return true;
    }
    else {
        return false;
    }
}

bool Line2D::isOnSegment(const Point2D &pointToCheck) const {
    return isOnSegment(start, end, pointToCheck);
}

bool Line2D::intersectableLines(const Line2D &other) const {
    float dx1 = end.getX() - start.getX();
    float dy1 = end.getY() - start.getY();

    float dx2 = other.end.getX() - other.start.getY();
    float dy2 = other.end.getY() - other.start.getY();

    return (dy1 * dx2 != dx1 * dy2);
}

bool Line2D::intersectableSegment(const Line2D &other) const {
    Orientation o1 = getOrientation(other.start);
    Orientation o2 = getOrientation(other.end);
    Orientation o3 = other.getOrientation(start);
    Orientation o4 = other.getOrientation(end);

    //General case
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    //Special cases
    if (o1 == 0 && isOnSegment(other.start)) {
        return true;
    }

    if (o2 == 0 && isOnSegment(other.end)) {
        return true;
    }

    if (o3 == 0 && other.isOnSegment(start)) {
        return true;
    }

    if (o4 == 0 && other.isOnSegment(end)) {
        return true;
    }

    return false;
}

float Line2D::getSlope() const {
    float dx = end.getX() - start.getX();
    float dy = end.getY() - end.getY();

    return dy / dx;
}

Orientation Line2D::getOrientation(const Point2D &point) const {
    float sx = start.getX();
    float sy = start.getY();
    float ex = end.getX();
    float ey = end.getY();
    float px = point.getX();
    float py = point.getY();

    float result = (ey - sy) * (px - ex) - (ex - sx) * (py - ey);

    if (result == 0) {
        return Orientation::COLINEAR;
    }
    else if (result > 0) {
        return Orientation::CLOCK_WISE;
    }
    else {
        return Orientation::COUNTERCLOCK_WISE;
    }
}

pair<bool, Point2D> Line2D::getIntersectionPoint(const Line2D &other) const {
    float x1 = start.getX();
    float y1 = start.getY();
    float x2 = end.getX();
    float y2 = end.getY();
    float x3 = other.start.getX();
    float y3 = other.start.getY();
    float x4 = other.end.getX();
    float y4 = other.end.getY();

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0) {
        return pair<bool, Point2D>(false, Point2D());
    }

    if(start == other.start || start == other.end){
        return pair<bool, Point2D>(true, start);
    }
    if(end == other.start || end == other.end){
        return pair<bool, Point2D>(true, end);
    }

    float xi = ((x3 - x4) * (x1 * y2 - y1 * x2) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
    float yi = ((y3 - y4) * (x1 * y2 - y1 * x2) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;

    float xEpsilon = numeric_limits<float>::epsilon()*max(1.0f, xi);
    float yEpsilon = numeric_limits<float>::epsilon()*max(1.0f, yi);

    if (xi + xEpsilon < min(x1, x2) || xi > max(x1, x2) + xEpsilon) {
        return pair<bool, Point2D>(false, Point2D());
    } else if (xi + xEpsilon < min(x3, x4) || xi > max(x3, x4) + xEpsilon) {
        return pair<bool, Point2D>(false, Point2D());
    } else if(yi + yEpsilon < min(y1, y2)
              || yi > max(y1, y2) + yEpsilon){
        return pair<bool, Point2D>(false, Point2D());
    } else if(yi + yEpsilon < min(y3, y4) || yi > max(y3, y4) + yEpsilon){
        return pair<bool, Point2D>(false, Point2D());
    } else {
        return pair<bool, Point2D>(true, Point2D(xi, yi));
    }
}

std::string Line2D::toString() const {
    stringstream ss;
    ss << "Line2D[" << start.toString() << ", " << end.toString() << "]";
    return ss.str();
}