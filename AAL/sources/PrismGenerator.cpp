#include <time.h>
#include <c++/iostream>
#include "../headers/PrismGenerator.h"

using namespace std;

long PrismGenerator::id = 0;

PrismGenerator::PrismGenerator() : onlyConvex(false), howMany(100), maxVertexInBase(20) {
    maxRadius = howMany > 6 ? howMany / 2 : 3;
    areaRange = howMany*2;
    srand(time(NULL));
}

PrismGenerator::PrismGenerator(bool onlyConvex, int howMany, int maxVertexInBase) : onlyConvex(onlyConvex),
                                                                                    howMany(howMany),
                                                                                    maxVertexInBase(maxVertexInBase) {
    maxRadius = howMany > 6 ? howMany / 2 : 3;
    areaRange = howMany*2;
    srand(time(NULL));
}

void PrismGenerator::setOnlyConvex(bool setValue) {
    this->onlyConvex = setValue;
}

void PrismGenerator::setHowMany(int howMany) {
    maxRadius = howMany > 6 ? howMany / 2 : 3;
    this->howMany = howMany;
    areaRange = howMany*2;
}

void PrismGenerator::setMaxVertexNumberInBase(int number) {
    this->maxVertexInBase = number;
}

vector<Prism> PrismGenerator::generate() const {
    vector<Prism> result;
    for(int i = 0; i < howMany; i++){
        if(onlyConvex){
            result.push_back(generateConvexSingle());
        } else{
            result.push_back(generateRandomSingle());
        }
    }

    return result;
}


Prism PrismGenerator::generateConvexSingle() const {
    double angleSum = 6.28;
    vector<Point2D> resultVertices;

    int radius = rand() % (maxRadius - minRadius) + minRadius;
    int centerX = rand() % areaRange;
    int centerY = rand() % areaRange;
    //cout << "wylosowano: r=" << radius << " x=" << centerX << " y=" << centerY << endl;

    pair<int, int> height = generateHeightRange();

    int randomVerticesInBase = rand() % (maxVertexInBase - 3) + 3;
    //cout << "liczba wierzcholkow: " << randomVerticesInBase << endl;

    for(int i = 0; i < randomVerticesInBase; i++){
        double range = 6.28/(0.5*randomVerticesInBase) < angleSum ? 6.28/(0.5*randomVerticesInBase) : angleSum;
        double angle = ((rand() % 99) / (double)100) * range;
        angleSum -= angle;
        //cout << "angle: " << angleSum << endl;
        resultVertices.push_back(Point2D(centerX + radius * cos(angleSum), centerY + radius * sin(angleSum)));
    }

    return Prism(getNextID(), height.first, height.second, resultVertices);
}

Prism PrismGenerator::generateRandomSingle() const {
    double angleSum = 6.28;
    vector<Point2D> resultVertices;

    int centerX = rand() % areaRange;
    int centerY = rand() % areaRange;
    //cout  << "wylosowano x=" << centerX << " y=" << centerY << endl;

    pair<int, int> height = generateHeightRange();

    int randomVerticesInBase = rand() % (maxVertexInBase - 3) + 3;
    //cout << "liczba wierzcholkow: " << randomVerticesInBase << endl;

    for(int i = 0; i < randomVerticesInBase; i++){
        int radius = rand() % (maxRadius - minRadius) + minRadius;
        double range = 6.28/(0.5*randomVerticesInBase) < angleSum ? 6.28/(0.5*randomVerticesInBase) : angleSum;
        double angle = ((rand() % 99) / (double)100) * range;
        angleSum -= angle;
        resultVertices.push_back(Point2D(centerX + radius * cos(angleSum), centerY + radius * sin(angleSum)));
    }

    return Prism(getNextID(), height.first, height.second, resultVertices);
}

std::pair<int, int> PrismGenerator::generateHeightRange() const {
    int minHeight = rand() % 100;
    int maxHeight = rand() % 100 + minHeight;
    return make_pair(minHeight, maxHeight);
}

long PrismGenerator::getNextID() {
    return id++;
}