#include "Line2D.h"

#include <algorithm>

Line2D::Line2D()
{
}

Line2D::Line2D(double x1, double y1, double x2, double y2)
{
	this->start = Point2D(x1, y1);
	this->end = Point2D(x2, y2);
}

Line2D::Line2D(const Point2D & start, const Point2D & end)
{
	this->start = start;
	this->end = end;
}

Line2D::Line2D(const Line2D & other)
{
	this->start = other.getStart();
	this->end = other.getEnd();
}

Vector2D Line2D::getVector2D() const
{
	return Vector2D(end.getX() - start.getX(), end.getY() - start.getY());
}

Line2D& Line2D::operator=(const Line2D & other)
{
	this->start = other.start;
	this->end = other.end;
	return *this;
}

void Line2D::setStart(const Point2D & start)
{
	this->start = start;
}

void Line2D::setEnd(const Point2D & end)
{
	this->end = end;
}

Point2D Line2D::getStart() const
{
	return start;
}

Point2D Line2D::getEnd() const
{
	return end;
}

bool Line2D::isOnSegment(const Point2D & start, const Point2D & end, const Point2D & pointToCheck)
{
	double x1 = start.getX();
	double y1 = start.getY();
	double x2 = end.getX();
	double y2 = end.getY();
	if (pointToCheck.getX() <= std::max(x1, x2) && pointToCheck.getX() >= std::min(x1, x2)
		&& pointToCheck.getY() <= std::max(y1, y2) && pointToCheck.getY() >= std::min(y1, y2)) {
		return true;
	}
	else {
		return false;
	}
}

bool Line2D::isOnLine(const Point2D & pointToCheck) const
{
	if (start.getDistance(pointToCheck) + pointToCheck.getDistance(end) == start.getDistance(end) ) {
		return true;
	}
	else {
		return false;
	}
}

bool Line2D::isOnSegment(const Point2D & pointToCheck) const
{
	return isOnSegment(start, end, pointToCheck);
}

bool Line2D::intersectableLines(const Line2D & other) const
{
	double dx1 = end.getX() - start.getX();
	double dy1 = end.getY() - start.getY();

	double dx2 = other.end.getX() - other.start.getY();
	double dy2 = other.end.getY() - other.start.getY();

	return (dy1*dx2 != dx1*dy2);
}

bool Line2D::intersectableSegment(const Line2D & other) const
{
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

double Line2D::getSlope() const
{
	double dx = end.getX() - start.getX();
	double dy = end.getY() - end.getY();

	return dy / dx;
}

Orientation Line2D::getOrientation(const Point2D & point) const
{
	double sx = start.getX();
	double sy = start.getY();
	double ex = end.getX();
	double ey = end.getY();
	double px = point.getX();
	double py = point.getY();

	double result = (ey - sy)*(px - ex) - (ex - sx)*(py - ey);
	
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

std::pair<bool, Point2D> Line2D::getIntersectionPoint(const Line2D & other) const
{
	double x1 = start.getX();
	double y1 = start.getY();
	double x2 = end.getX();
	double y2 = end.getY();
	double x3 = other.start.getX();
	double y3 = other.start.getY();
	double x4 = other.end.getX();
	double y4 = other.end.getY();

	double d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
	if (d == 0) {
		return std::pair<bool, Point2D>(false, Point2D());
	}

	double xi = ((x3 - x4)*(x1*y2 - y1*x2) - (x1 - x2)*(x3*y4 - y3*x4)) / d;
	double yi = ((y3 - y4)*(x1*y2 - y1*x2) - (y1 - y2)*(x3*y4 - y3*x4)) / d;

	
	if (xi < std::min(x1, x2) || xi > std::max(x1, x2)) {
		return std::pair<bool, Point2D>(false, Point2D());
	}
	else if (xi < std::min(x3, x4) || xi > std::max(x3, x4)) {
		return std::pair<bool, Point2D>(false, Point2D());
	}
	else {
		return std::pair<bool, Point2D>(true, Point2D(xi, yi));
	}
	
}