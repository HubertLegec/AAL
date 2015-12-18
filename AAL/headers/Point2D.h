#ifndef POINT_2D
#define POINT_2D

#include <string>

class Point2D {
protected:
	double x;
	double y;
private:
	bool intersectionPoint;

public:
	Point2D() : x(0), y(0), intersectionPoint(false) {};
	Point2D(double x, double y, bool intersectionPoint = false);
	Point2D(const Point2D& other);

	Point2D& operator=(const Point2D& other);
	bool operator==(const Point2D& other) const;
	bool operator!=(const Point2D& other) const;
	double getDistance(const Point2D& other) const;

	void setX(double x);
	void setY(double y);
	double getX() const;
	double getY() const;
	bool isIntersectionPoint() const;

	std::string toString() const;

};

#endif