#include "../headers/WeilerAtherton.h"
#include "../headers/Line2D.h"

void WeilerAtherton::generateVertexLists()
{
	std::vector<std::vector<Point2D>> firstTempList(firstPrism.getVertexList().getSize());
	std::vector<std::vector<Point2D>> secondTempList(secondPrism.getVertexList().getSize());

	for (int i = 0; i < firstPrism.getVertexList().getSize(); i++) {
		int inext = (i + 1) % firstPrism.getVertexList().getSize();
		Line2D firstLine(firstPrism.getVertexList()[i], firstPrism.getVertexList()[inext]);

		for (int j = 0; j < secondPrism.getVertexList().getSize(); j++) {
			int jnext = (j + 1) % secondPrism.getVertexList().getSize();
			Line2D secondLine(secondPrism.getVertexList()[j], secondPrism.getVertexList()[jnext]);

			if (firstLine.intersectableSegment(secondLine)) {
				std::pair<bool, Point2D> p = firstLine.getIntersectionPoint(secondLine);
				firstTempList[i].push_back(Point2D(p.second.getX(), p.second.getY(), true));
				secondTempList[j].push_back(Point2D(p.second.getX(), p.second.getY(), true));
			}
		}
	}

	for (int i = 0; i < firstPrism.getVertexList().getSize(); i++) {
		sortIntersections(firstPrism.getVertexList()[i], firstTempList[i]);
		vertexList[0].add(firstPrism.getVertexList()[i]);
		vertexList[0].add(firstTempList[i]);
	}

	for (int i = 0; i < secondPrism.getVertexList().getSize(); i++) {
		sortIntersections(secondPrism.getVertexList()[i], secondTempList[i]);
		vertexList[1].add(secondPrism.getVertexList()[i]);
		vertexList[1].add(secondTempList[i]);
	}
}

void WeilerAtherton::sortIntersections(const Point2D & startPoint, std::vector<Point2D>& list)
{
	if (list.size() < 2)
		return;

	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = 0; j < list.size() - 1 - i; j++) {
			if (startPoint.getDistance(list[j]) > startPoint.getDistance(list[j + 1])) {
				Point2D p = list[j];
				list[j] = list[j + 1];
				list[j + 1] = p;
			}
		}
	}
}

WeilerAtherton::WeilerAtherton(const Prism& first, const Prism& second) : firstPrism(first), secondPrism(second)
{
}

void WeilerAtherton::doWeilerAtherton()
{
	if (valid == true)
		return;

	int idCounter = 10000;

	generateVertexLists();

	std::vector<Point2D> *intersectionPart = nullptr;
	bool insideIntersectionflag = false;
	int switcher = 0;

	Point2D currentPoint = vertexList[0][0];
	Point2D intersectionStartPoint;
	Point2D intersectionEndPoint;
	do {
		if (!insideIntersectionflag && switcher == 0 && currentPoint.isIntersectionPoint()) {
			insideIntersectionflag = true;
			intersectionStartPoint = currentPoint;
			if (intersectionPart == nullptr) {
				delete intersectionPart;
			}
			intersectionPart = new std::vector<Point2D>;
			intersectionPart->push_back(currentPoint);
		}
		else if (insideIntersectionflag && !currentPoint.isIntersectionPoint()) {
			intersectionPart->push_back(currentPoint);
		}
		else if (insideIntersectionflag && switcher == 0 && currentPoint.isIntersectionPoint()) {
			switcher = 1;
			intersectionEndPoint = currentPoint;
			intersectionPart->push_back(currentPoint);
		}
		else if (insideIntersectionflag && switcher == 1 && currentPoint.isIntersectionPoint()) {
			if (currentPoint == intersectionStartPoint) {
				Prism pr(idCounter++, *intersectionPart);
				//FIXME
				pr.addHeightRange(firstPrism.getId(), firstPrism.getBottom(), firstPrism.getTop());
				pr.addHeightRange(secondPrism.getId(), secondPrism.getBottom(), secondPrism.getTop());
				intersectionParts.add(pr);
				currentPoint = intersectionEndPoint;
				insideIntersectionflag = 0;
			}
			switcher = 0;
			intersectionPart->push_back(currentPoint);
		}
		currentPoint = vertexList[switcher].getNext(currentPoint);
	} while (currentPoint != vertexList[0][0]);
		
	if (intersectionPart == nullptr) {
		delete intersectionPart;
	}

	valid = true;
}

Collection<Prism> WeilerAtherton::getFirstParts()
{
	return firstParts;
}

Collection<Prism> WeilerAtherton::getSecondParts()
{
	return secondParts;
}

Collection<Prism> WeilerAtherton::getIntersectionParts()
{
	return intersectionParts;
}

Collection<Prism> WeilerAtherton::getAllParts()
{
	Collection<Prism> result;
	result.add(firstParts);
	result.add(intersectionParts);
	result.add(secondParts);
	return result;
}
