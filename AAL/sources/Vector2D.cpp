#include "Vector2D.h"

#include <cmath>

const double Vector2D::PI = 3.14;

double Vector2D::radiansToDegrees(double a)
{
	return a* PI / 180;
}

double Vector2D::degreesToRadians(double a)
{
	return a * 180 / PI;
}

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(const Vector2D & other)
{
	this->x = other.x;
	this->y = other.y;
}

void Vector2D::set(double x, double y)
{
	this->x = x;
	this->y = y;
}


double Vector2D::getMagnitude() const
{
	return std::hypot(x, y);
}

double Vector2D::getX() const
{
	return x;
}

double Vector2D::getY() const
{
	return y;
}

Vector2D & Vector2D::operator=(const Vector2D & other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D & other) const
{
	double xS = x + other.x;
	double yS = y + other.y;

	return Vector2D(xS, yS);
}

Vector2D Vector2D::operator-(const Vector2D & other) const
{
	double xS = x - other.x;
	double yS = y - other.y;
	return Vector2D(xS, yS);
}

Vector2D Vector2D::operator*(double scalar) const
{
	return Vector2D(x*scalar, y*scalar);
}

double Vector2D::dotProduct(const Vector2D & other) const
{
	return x*other.x + y*other.y;
}

double Vector2D::getDirectionAngle() const
{
	return radiansToDegrees( atan2(y, x) );
}

double Vector2D::getAngleBetween(const Vector2D & other) const
{
	double rad = this->dotProduct(other) / (this->getMagnitude() * other.getMagnitude());
	return radiansToDegrees(acos(rad));
}