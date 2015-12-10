#include "../headers/Point2D.h"

#include <cmath>
#include <sstream>


Point2D::Point2D(double x, double y, bool intersectionPoint)
{
	this->x = x;
	this->y = y;
	this->intersectionPoint = intersectionPoint;
}

Point2D::Point2D(const Point2D& other)
{
	this->x = other.x;
	this->y = other.y;
	this->intersectionPoint = other.intersectionPoint;
}

Point2D& Point2D::operator=(const Point2D& other) {
	this->x = other.x;
	this->y = other.y;
	this->intersectionPoint = other.intersectionPoint;
	return *this;
}

bool Point2D::operator==(const Point2D& other) const {
	return (this->x == other.x) && (this->y == other.y) && (this->intersectionPoint == other.intersectionPoint);
}

bool Point2D::operator!=(const Point2D& other) const {
	return !(*this == other);
}

double Point2D::getDistance(const Point2D& other) const
{
	double dx = other.getX() - x;
	double dy = other.getY() - y;
	return std::hypot(dx, dy);
}

void Point2D::setX(double x)
{
	this->x = x;
}

void Point2D::setY(double y)
{
	this->y = y;
}

double Point2D::getX() const 
{
	return x;
}

double Point2D::getY() const
{
	return y;
}

bool Point2D::isIntersectionPoint() const
{
	return intersectionPoint;
}

std::string Point2D::toString() const
{
	std::stringstream result;
	result << "(" << x << "," << y << ")";
	return result.str();
}