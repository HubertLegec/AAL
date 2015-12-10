#include <c++/sstream>
#include "../headers/Prism.h"


Prism::Prism()
{
	this->id = -1;
}

Prism::Prism(int id, const Polygon & base)
{
	this->id = id;
	this->base = base;
}

Prism::Prism(int id, std::vector<Point2D> vertexes)
{
	this->id = id;
	this->base.add(vertexes);
}

Prism::Prism(const int id, double bottom, double top, const Polygon & base)
{
	this->id = id;
	heightRanges.emplace(id, std::pair<double, double>(bottom, top));
	this->base = base;
}

Prism::Prism(const int id, double bottom, double top, std::vector<Point2D> vertexes)
{
	this->id = id;
	heightRanges.emplace(id, std::pair<double, double>(bottom, top));
	this->base.add(vertexes);
}

Prism::Prism(const Prism & other)
{
	this->heightRanges = other.heightRanges;
	this->id = other.id;
	this->base = other.base;
}

Prism & Prism::operator=(const Prism & other)
{
	this->heightRanges = other.heightRanges;
	this->id = id;
	this->base = other.base;
	return *this;
}

bool Prism::operator==(const Prism & other) const
{
	return id == other.id;
}

double Prism::getTop() const
{
	return heightRanges.at(id).second;
}

double Prism::getBottom() const
{
	return heightRanges.at(id).first;
}

int Prism::getId() const
{
	return id;
}

std::map<int, std::pair<double, double>> Prism::getHeightRanges() const
{
	return heightRanges;
}

double Prism::getMinX() const
{
	return base.getMinX();
}

double Prism::getMaxX() const
{
	return base.getMaxX();
}

double Prism::getMinY() const
{
	return base.getMinY();
}

double Prism::getMaxY() const
{
	return base.getMaxY();
}

void Prism::setId(int id)
{
	this->id = id;
}

void Prism::setTop(double top)
{
	heightRanges.at(id).second = top;
}

void Prism::setBottom(double bottom)
{
	heightRanges.at(id).first = bottom;
}

void Prism::addHeightRange(const int id, double bottom, double top)
{
	heightRanges.emplace(id, std::pair<double, double>(bottom, top));
}

Polygon Prism::getBase()
{
	return base;
}

Collection<Point2D> Prism::getVertexList() const
{
	return base.getVertices();
}

std::string Prism::toString()
{
	std::stringstream result;
	result << "---------- Polygon [" << id << "] ----------------------\nHeightRanges:\n";
	for (std::pair<int, std::pair<double, double>> i : heightRanges) {
		result << "[" << i.first << "] from: " << i.second.first << " to: " << i.second.second << std::endl;
	}
	result << "Vertices:\n";
	for (Point2D p : base.getVertices()) {
		result << p.toString() << " ";
	}
	result << "\n--------------------------------------------------------" << std::endl;
	return result.str();
}