/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

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

    static bool approximatelyEqual(float a, float b);
    static bool graterThan(float a, float b);
public:
    Line2D();

    Line2D(float x1, float y1, float x2, float y2);

    Line2D(const Point2D &start, const Point2D &end);

    Line2D(const Line2D &other);

    Vector2D getVector2D() const;

    Line2D &operator=(const Line2D &other);

    void setStart(const Point2D &start);

    void setEnd(const Point2D &end);

    Point2D getStart() const;

    Point2D getEnd() const;

    /**
     * Sprawdza czy dany punkt leży wewnątrz prostokąta którego przeciwległe wierzchołki wyznaczają podane punkty
     */
    static bool isOnSegment(const Point2D &start, const Point2D &end, const Point2D &pointToCheck);

    /**
     * Sprawdza czy dany punkt leży na linii
     */
    bool isOnLine(const Point2D &pointToCheck) const;

    /**
     * Sprawdza czy dany punkt leży wewnątrz prostokąta którego przeciwległe wierzchołki wyznaczają końce odcinka
     */
    bool isOnSegment(const Point2D &pointToCheck) const;

    /**
     * Sprawdza czy linie się przecinają
     */
    bool intersectableLines(const Line2D &other) const;

    /**
     * Sprawdza czy odcinki się przecinają
     */
    bool intersectableSegment(const Line2D &other) const;

    /**
     * Zwraca nachylenie linii
     */
    float getSlope() const;

    /**
     * Zwraca położenie punktu względem linii
     */
    Orientation getOrientation(const Point2D &point) const;

    /**
     * Wyznacza punkt przecięcia linii
     * Jeśli istnieje to pierwszy element pary to true, w przeciwnym wypadku false
     */
    std::pair<bool, Point2D> getIntersectionPoint(const Line2D &other) const;

    std::string toString() const;
};

#endif
