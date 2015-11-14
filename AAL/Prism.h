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
	Prism(int id, const Polygon& base);
	Prism(int id, std::vector<Point2D> vertexes);
	Prism(int id, double bottom, double top, const Polygon& base);
	Prism(int id, double bottom, double top, std::vector<Point2D> vertexes);
	Prism(const Prism& other);

	Prism& operator=(const Prism& other);
	bool operator==(const Prism& other) const;

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
	void addHeightRange(int id, double bottom, double top);
	Polygon getBase();
	Collection<Point2D> getVertexList() const;
	std::string toString();
};

#endif