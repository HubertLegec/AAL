#ifndef VECTOR_2D
#define VECTOR_2D


class Vector2D {
private:
    static const double PI;
    double x;
    double y;

    static double radiansToDegrees(double a);

    static double degreesToRadians(double a);

public:
    Vector2D();

    Vector2D(double x, double y);

    Vector2D(const Vector2D &other);

    void set(double x, double y);

    double getMagnitude() const;

    double getX() const;

    double getY() const;

    Vector2D &operator=(const Vector2D &other);

    Vector2D operator+(const Vector2D &other) const;

    Vector2D operator-(const Vector2D &other) const;

    Vector2D operator*(double scalar) const;

    double dotProduct(const Vector2D &other) const;

    double getDirectionAngle() const;

    double getAngleBetween(const Vector2D &other) const;
};

#endif