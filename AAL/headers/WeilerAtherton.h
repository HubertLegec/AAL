#ifndef WEILER_ATHERTON
#define WEILER_ATHERTON

#include "Prism.h"
#include "Collection.hpp"

class WeilerAtherton {
private:
    Prism firstPrism;
    Prism secondPrism;
    Collection<Point2D> vertexList[2];
    Collection<Prism> intersectionParts;
    Collection<Prism> firstParts;
    Collection<Prism> secondParts;
    bool valid;

    void generateVertexLists();

    void sortIntersections(Point2D &startPoint, std::vector<Point2D> &list);

    Point2D* getStartPoint();

    void addFirstPart(Point2D* point);

    void addSecondPart(Point2D* point);

    void checkOneInsideAnother();

public:
    WeilerAtherton(const Prism &first, const Prism &second);

    void doWeilerAtherton();

    Collection<Prism> getFirstParts();

    Collection<Prism> getSecondParts();

    Collection<Prism> getIntersectionParts();

    Collection<Prism> getAllParts();
};

#endif