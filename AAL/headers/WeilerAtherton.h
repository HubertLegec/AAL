#ifndef WEILER_ATHERTON
#define WEILER_ATHERTON

#include <memory>
#include "Prism.h"
#include "Collection.hpp"

class WeilerAtherton {
private:
    Prism firstPrism;
    Prism secondPrism;
    Collection<std::shared_ptr<Point2D>> vertexList[2];
    Collection<Prism> intersectionParts;
    Collection<Prism> firstParts;
    Collection<Prism> secondParts;
    bool valid;

    void generateVertexLists();

    void sortIntersections(std::shared_ptr<Point2D> startPoint, std::vector<std::shared_ptr<Point2D>> &list);

    std::shared_ptr<Point2D> getStartPoint();

    void addFirstPart(std::shared_ptr<Point2D> point);

    void addSecondPart(std::shared_ptr<Point2D> point);

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