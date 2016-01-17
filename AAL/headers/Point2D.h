#ifndef POINT_2D
#define POINT_2D

#include <string>

class Point2D {
protected:
    float x;
    float y;
private:
    bool intersectionPoint;
    bool visited = false;
    bool firstPartAdded = false;
    bool secondPartAdded = false;

    static bool approximatelyEqual(float a, float b);
    static bool graterThan(float a, float b);
public:
    Point2D() : x(0), y(0), intersectionPoint(false) { };

    Point2D(float x, float y, bool intersectionPoint = false);

    Point2D(const Point2D &other);

    Point2D &operator=(const Point2D &other);

    bool operator==(const Point2D &other) const;

    bool operator!=(const Point2D &other) const;

    bool operator<(const Point2D & other) const;

    float getDistance(const Point2D &other) const;

    void setX(float x);

    void setY(float y);

    float getX() const;

    float getY() const;

    bool isIntersectionPoint() const;

    void setIntersectionPoint(bool intersectionPoint);

    bool isVisited() const;

    void setVisited(bool visited);

    bool isFirstPartAdded() const;

    void setFirstPartAdded(bool firstPartAdded);

    bool isSecondPartAdded() const;

    void setSecondPartAdded(bool secondPartAdded);

    std::string toString() const;
};

#endif