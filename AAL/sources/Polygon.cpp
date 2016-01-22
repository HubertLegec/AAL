/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "../headers/Polygon.h"
#include "../headers/Line2D.h"
#include <sstream>

using namespace std;

void Polygon::updateMinMax(const Point2D &vertex) {
    if (vertex.getX() < xMin) {
        xMin = vertex.getX();
    }
    else if (vertex.getX() > xMax) {
        xMax = vertex.getX();
    }

    if (vertex.getY() < yMin) {
        yMin = vertex.getY();
    }
    else if (vertex.getY() > yMax) {
        yMax = vertex.getY();
    }
}

void Polygon::updateMinMax(const vector<Point2D> &vertices) {
    for (Point2D vertex : vertices) {
        updateMinMax(vertex);
    }
}

Polygon::Polygon() {
    xMin = numeric_limits<float>::max();
    yMin = numeric_limits<float>::max();
    xMax = numeric_limits<float>::min();
    yMax = numeric_limits<float>::min();
}

Polygon::Polygon(const Polygon &other) {
    xMin = other.xMin;
    yMin = other.yMin;
    xMax = other.xMax;
    yMax = other.yMax;
    add(other.getVertices());
}

Polygon::Polygon(const Collection<Point2D> &vertices) {
    xMin = numeric_limits<float>::max();
    yMin = numeric_limits<float>::max();
    xMax = numeric_limits<float>::min();
    yMax = numeric_limits<float>::min();
    add(vertices);
}

Polygon &Polygon::operator=(const Polygon &other) {
    xMin = other.xMin;
    yMin = other.yMin;
    xMax = other.xMax;
    yMax = other.yMax;
    add(other.getVertices());
    return *this;
}

bool Polygon::operator==(const Polygon &other) const {
    return vertexList == other.vertexList;
}

void Polygon::add(const Point2D &point) {
    vertexList.add(point);
    updateMinMax(point);
}

void Polygon::add(const vector<Point2D> &vertices) {
    vertexList.add(vertices);
    updateMinMax(vertices);
}

void Polygon::add(const Collection<Point2D> &vertices) {
    vertexList.add(vertices);
    updateMinMax(vertices.getItems());
}

float Polygon::getMinX() const {
    return xMin;
}

float Polygon::getMinY() const {
    return yMin;
}

float Polygon::getMaxX() const {
    return xMax;
}

float Polygon::getMaxY() const {
    return yMax;
}

Point2D &Polygon::operator[](int index) {
    return vertexList[index];
}

Point2D Polygon::operator[](int index) const {
    return vertexList[index];
}

bool Polygon::exist(const Point2D &vertex) const {
    return vertexList.exist(vertex);
}

int Polygon::getIndex(const Point2D &vertex) const {
    return vertexList.getIndex(vertex);
}

Collection<Point2D> Polygon::getVertices() const {
    return vertexList;
}

bool Polygon::isInside(const Point2D &point) const {
    if (!isValidPolygon()) {
        return false;
    } else if (point.getX() > xMax || point.getX() < xMin) {
        return false;
    } else if (point.getY() > yMax || point.getY() < yMin) {
        return false;
    }
    Point2D helperPoint(xMax + 5, point.getY());
    Line2D testLine(point, helperPoint);

    int count = 0;
    int next, next2;
    for (int i = 0; i < vertexList.getSize(); i++) {
        next = (i + 1) % vertexList.getSize();
        next2 = (i + 2) % vertexList.getSize();
        Line2D line(vertexList[i], vertexList[next]);

        if (line.isOnLine(point)) {
            return true;
        }

        auto ip = testLine.getIntersectionPoint(line);
        if (ip.first) {
            if (ip.second != line.getEnd() && ip.second != line.getStart()) {
                count++;
            } else if (ip.second == line.getEnd() &&
                       testLine.getOrientation(vertexList[i]) != testLine.getOrientation(vertexList[next2])) {
                count++;
            }
        }
    }
    return count % 2 ? true : false;
}

bool Polygon::isValidPolygon() const {
    return vertexList.getSize() < 3 ? false : true;
}

string Polygon::toString() const {
    stringstream result;
    for (int i = 0; i < vertexList.getSize(); i++) {
        if (i > 0) {
            result << " ";
        }
        result << vertexList[i].toString();
    }
    return result.str();
}