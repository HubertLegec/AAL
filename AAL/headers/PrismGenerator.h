#ifndef PRISM_GENERATOR
#define PRISM_GENERATOR

#include "Prism.h"

class PrismGenerator {
private:
    static long id;
    int prismId = 0;
    int maxX = 1000;
    int maxY = 1000;
    int maxHeight = 1000;
    bool onlyConvex;
    int howMany;
    int maxVertexInBase;
    int areaRange;
    int minRadius = 2;
    int maxRadius = 3;

    Prism generateConvexSingle() const;

    Prism generateRandomSingle() const;

    std::pair<int, int> generateHeightRange() const;

    static long getNextID();

public:
    PrismGenerator();

    PrismGenerator(bool onlyConvex, int howMany, int maxVertexInBase);

    void setOnlyConvex(bool setValue);

    void setHowMany(int howMany);

    void setMaxVertexNumberInBase(int number);

    void setXRange(int x);

    void setYRange(int y);

    void setHeightRange(int h);

    std::vector<Prism> generate() const;
};

#endif