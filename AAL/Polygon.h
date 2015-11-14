#ifndef POLYGON
#define POLYGON

#include "Collection.hpp"
#include "Point2D.h"
#include <vector>
#include <string>

class Polygon {
private:
	Collection<Point2D> vertexList;
	double xMax;
	double yMax;
	double xMin;
	double yMin;

	void updateMinMax(const Point2D& vertex);
	void updateMinMax(const std::vector<Point2D>& vertices);
public:
	Polygon();
	Polygon(const Polygon& other);
	Polygon(const Collection<Point2D>& vertices);
	Polygon& operator=(const Polygon& other);
	bool operator==(const Polygon& other) const;

	void add(const Point2D& point);
	void add(const std::vector<Point2D>& vertices);
	void add(const Collection<Point2D>& vertices);
	int size() const;
	double getMinX() const;
	double getMinY() const;
	double getMaxX() const;
	double getMaxY() const;

	Point2D& operator[](int index);
	Point2D operator[](int index) const;
	bool exist(const Point2D& vertex) const;
	int getIndex(const Point2D& vertex) const;
	Collection<Point2D> getVertices() const;
	bool isInside(const Point2D& point) const;
	bool isValidPolygon() const;
	std::string toString() const;
};

#endif
