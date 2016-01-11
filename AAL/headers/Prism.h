#ifndef PRISM
#define PRISM

#include <vector>
#include <map>

#include "Polygon.h"


class Prism {
private:
    std::map<int, std::pair<double, double>> heightRanges;
    Polygon base;
    int id;

public:
    Prism();

    Prism(int id, const Polygon &base);

    Prism(std::vector<Point2D> vertexes, int id = -1);

    Prism(int id, double bottom, double top, const Polygon &base);

    Prism(int id, double bottom, double top, std::vector<Point2D> vertexes);

    Prism(const Prism &other);

    Prism &operator=(const Prism &other);

    bool operator==(const Prism &other) const;

    double getTop() const;

    double getBottom() const;

    int getId() const;

    std::map<int, std::pair<double, double>> getHeightRanges() const;

    double getMinX() const;

    double getMaxX() const;

    double getMinY() const;

    double getMaxY() const;

    void setId(int id);

    void setTop(double top);

    void setBottom(double bottom);

    void addHeightRange(const int id, const double bottom, const double top);

    void addHeightRanges(const std::map<int, std::pair<double, double>> &ranges);

    Polygon getBase();

    Collection<Point2D> getVertexList() const;

    std::string toString();
};

#endif