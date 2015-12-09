#ifndef LINE_2D
#define LINE_2D

#include "Point2D.h"
#include "Vector2D.h"

enum Orientation {
	COLINEAR = 0,
	CLOCK_WISE = 1,
	COUNTERCLOCK_WISE = 2
};

class Line2D {
protected:
	Point2D start;
	Point2D end;
public:
	Line2D();
	Line2D(double x1, double y1, double x2, double y2);
	Line2D(const Point2D& start, const Point2D& end);
	Line2D(const Line2D& other);

	Vector2D getVector2D() const;

	Line2D& operator=(const Line2D& other);
	void setStart(const Point2D& start);
	void setEnd(const Point2D& end);
	Point2D getStart() const;
	Point2D getEnd() const;

	static bool isOnSegment(const Point2D& start, const Point2D& end, const Point2D& pointToCheck);
	bool isOnLine(const Point2D& pointToCheck) const;
	bool isOnSegment(const Point2D& pointToCheck) const;
	bool intersectableLines(const Line2D& other) const;
	bool intersectableSegment(const Line2D& other) const;
	double getSlope() const;
	Orientation getOrientation(const Point2D& point) const;
	std::pair<bool, Point2D> getIntersectionPoint(const Line2D& other) const;
};

#endif
