/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <time.h>
#include <iostream>
#include "../headers/PrismGenerator.h"

using namespace std;

long PrismGenerator::id = 0;

PrismGenerator::PrismGenerator() : onlyConvex(false), howMany(100), maxVertexInBase(20) {
    srand(time(NULL));
    minRadius = rand() % 20 + 30;
    maxRadius = rand() % 100 + minRadius + 2;
    areaRange = howMany * 2 < 300 ? howMany * 2 : 300;
}

PrismGenerator::PrismGenerator(bool onlyConvex, int howMany, int maxVertexInBase) : onlyConvex(onlyConvex),
                                                                                    howMany(howMany),
                                                                                    maxVertexInBase(maxVertexInBase) {
    srand(time(NULL));
    minRadius = rand() % 20 + 30;
    maxRadius = rand() % 100 + minRadius + 2;
    areaRange = howMany * 2 < 300 ? howMany * 2 : 300;
}

void PrismGenerator::setOnlyConvex(bool setValue) {
    this->onlyConvex = setValue;
}

void PrismGenerator::setHowMany(int howMany) {
    maxRadius = howMany > 6 ? howMany / 2 : 3;
    this->howMany = howMany;
    areaRange = howMany * 2;
}

void PrismGenerator::setMaxVertexNumberInBase(int number) {
    this->maxVertexInBase = number;
}

vector<Prism> PrismGenerator::generate() const {
    vector<Prism> result;
    for (int i = 0; i < howMany; i++) {
        if (onlyConvex) {
            result.push_back(generateConvexSingle());
        } else {
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

    pair<int, int> height = generateHeightRange();

    int randomVerticesInBase = rand() % (maxVertexInBase - 3) + 3;

    for (int i = 0; i < randomVerticesInBase; i++) {
        double range = 6.28 / (0.5 * randomVerticesInBase) < angleSum ? 6.28 / (0.5 * randomVerticesInBase) : angleSum;
        double angle = ((rand() % 100) / (double) 100) * range;
        angleSum -= angle;
        resultVertices.push_back(Point2D(centerX + radius * cos(angleSum), centerY + radius * sin(angleSum)));
    }

    return Prism(getNextID(), height.first, height.second, resultVertices);
}

Prism PrismGenerator::generateRandomSingle() const {
    int centerX = rand() % areaRange;
    int centerY = rand() % areaRange;
    pair<int, int> height = generateHeightRange();
    int randomVerticesInBase = rand() % (maxVertexInBase - 3) + 3;
    int radius = rand() % (maxRadius - minRadius) + minRadius;
    float irregularity = ((rand() % 101) / 100.0) * 2 * 3.14 / randomVerticesInBase;
    float spikeyness = ((rand() % 101) / 100.0) * radius * 0.9;
    vector<float> angleSteeps;
    float lower = (2 * 3.14 / randomVerticesInBase) - irregularity;
    float upper = (2 * 3.14 / randomVerticesInBase) + irregularity;
    float sum = 0;
    for (int i = 0; i < randomVerticesInBase; i++) {
        float tmp = (rand() % 101) / 100.0 * (upper - lower) + lower;
        angleSteeps.push_back(tmp);
        sum += tmp;
    }

    float k = sum / (2 * 3.14);
    for (int i = 0; i < randomVerticesInBase; i++) {
        angleSteeps[i] = angleSteeps[i] / k;
    }

    vector<Point2D> vertices;
    float angle = ((rand() % 101) / 100.0) * 6.28;
    for (int i = 0; i < randomVerticesInBase; i++) {
        float t = ((rand() % 101) / 100.0) * spikeyness;
        int sign = rand() % 2;
        if (sign == 1) {
            t *= -1;
        }
        float ri = min(radius + t, (float) 2 * radius);
        ri = max(ri, (float) 0.0);

        float x = centerX + ri * cos(angle);
        float y = centerY + ri * sin(angle);
        vertices.push_back(Point2D(x, y));

        angle += angleSteeps[i];
    }
    reverse(vertices.begin(), vertices.end());

    return Prism(getNextID(), height.first, height.second, vertices);
}

std::pair<int, int> PrismGenerator::generateHeightRange() const {
    int minHeight = rand() % 100;
    int maxHeight = rand() % 100 + minHeight;
    return make_pair(minHeight, maxHeight);
}

long PrismGenerator::getNextID() {
    return id++;
}