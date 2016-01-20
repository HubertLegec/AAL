/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef PRISM
#define PRISM

#include <vector>
#include <map>

#include "Polygon.h"


class Prism {
private:
    std::map<int, std::pair<float, float>> heightRanges;
    Polygon base;
    int id;

public:
    Prism();

    Prism(int id, const Polygon &base);

    Prism(std::vector<Point2D> vertexes, int id = -1);

    Prism(int id, float bottom, float top, const Polygon &base);

    Prism(int id, float bottom, float top, std::vector<Point2D> vertexes);

    Prism(const Prism &other);

    Prism &operator=(const Prism &other);

    bool operator==(const Prism &other) const;

    float getTop() const;

    float getBottom() const;

    int getId() const;

    std::map<int, std::pair<float, float>> getHeightRanges() const;

    float getMinX() const;

    float getMaxX() const;

    float getMinY() const;

    float getMaxY() const;

    void setId(int id);

    void setTop(float top);

    void setBottom(float bottom);

    void addHeightRange(const int id, const float bottom, const float top);

    void addHeightRanges(const std::map<int, std::pair<float, float>> &ranges);

    Polygon getBase();

    Collection<Point2D> getVertexList() const;

    std::string toString();
};

#endif