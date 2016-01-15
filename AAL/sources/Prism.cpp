#include <c++/sstream>
#include "../headers/Prism.h"

using namespace std;

Prism::Prism() {
    this->id = -1;
}

Prism::Prism(int id, const Polygon &base) {
    this->id = id;
    this->base = base;
}

Prism::Prism(vector<Point2D> vertexes, int id) {
    this->id = id;
    this->base.add(vertexes);
}

Prism::Prism(const int id, float bottom, float top, const Polygon &base) {
    this->id = id;
    heightRanges.insert(make_pair(id, make_pair(bottom, top)));
    this->base = base;
}

Prism::Prism(const int id, float bottom, float top, vector<Point2D> vertexes) {
    this->id = id;
    heightRanges.insert(make_pair(id, make_pair(bottom, top)));
    this->base.add(vertexes);
}

Prism::Prism(const Prism &other) {
    this->heightRanges = other.heightRanges;
    this->id = other.id;
    this->base = other.base;
}

Prism &Prism::operator=(const Prism &other) {
    this->heightRanges = other.heightRanges;
    this->id = id;
    this->base = other.base;
    return *this;
}

bool Prism::operator==(const Prism &other) const {
    return id == other.id;
}

float Prism::getTop() const {
    return heightRanges.at(id).second;
}

float Prism::getBottom() const {
    return heightRanges.at(id).first;
}

int Prism::getId() const {
    return id;
}

map<int, pair<float, float>> Prism::getHeightRanges() const {
    return heightRanges;
}

float Prism::getMinX() const {
    return base.getMinX();
}

float Prism::getMaxX() const {
    return base.getMaxX();
}

float Prism::getMinY() const {
    return base.getMinY();
}

float Prism::getMaxY() const {
    return base.getMaxY();
}

void Prism::setId(int id) {
    this->id = id;
}

void Prism::setTop(float top) {
    heightRanges.at(id).second = top;
}

void Prism::setBottom(float bottom) {
    heightRanges.at(id).first = bottom;
}

void Prism::addHeightRange(const int id, float bottom, float top) {
    heightRanges.insert(make_pair(id, make_pair(bottom, top)));
}

void Prism::addHeightRanges(const std::map<int, std::pair<float, float>> &ranges) {
    for(auto p : ranges){
        heightRanges.insert(p);
    }
}

Polygon Prism::getBase() {
    return base;
}

Collection<Point2D> Prism::getVertexList() const {
    return base.getVertices();
}

string Prism::toString() {
    stringstream result;
    result << "---------- Prism [" << id << "] ----------------------\nHeightRanges:\n";
    for (auto i : heightRanges) {
        result << "[" << i.first << "] from: " << i.second.first << " to: " << i.second.second << endl;
    }
    result << "Vertices:\n";
    for (Point2D p : base.getVertices()) {
        result << p.toString() << " ";
    }
    result << "\n--------------------------------------------------------" << endl;
    return result.str();
}