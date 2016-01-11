#include <c++/iostream>
#include "../headers/WeilerAtherton.h"
#include "../headers/Line2D.h"

using namespace std;

void WeilerAtherton::generateVertexLists() {
    vector<vector<Point2D>> firstTempList(firstPrism.getVertexList().getSize());
    vector<vector<Point2D>> secondTempList(secondPrism.getVertexList().getSize());

    //dla każdego boku pierwszego wielokąta
    for (int i = 0; i < firstPrism.getVertexList().getSize(); i++) {
        int inext = (i + 1) % firstPrism.getVertexList().getSize();
        Line2D firstLine(firstPrism.getVertexList()[i], firstPrism.getVertexList()[inext]);

        //sprawdź przecięcie z każdym bokiem drugiego wielokąta
        for (int j = 0; j < secondPrism.getVertexList().getSize(); j++) {
            int jnext = (j + 1) % secondPrism.getVertexList().getSize();
            Line2D secondLine(secondPrism.getVertexList()[j], secondPrism.getVertexList()[jnext]);
            //sprawdź czy segmenty boków mają część wspólną
            if (firstLine.intersectableSegment(secondLine)) {
                //wyznacz punkt przecięcia
                pair<bool, Point2D> p = firstLine.getIntersectionPoint(secondLine);
                //jeśli istnieje punkt przecięcia to dodaj nowy wierzchołek
                if(p.first) {
                    if(p.second != firstLine.getEnd() && p.second != secondLine.getEnd()) {
                        firstTempList[i].push_back(Point2D(p.second.getX(), p.second.getY(), true));
                        secondTempList[j].push_back(Point2D(p.second.getX(), p.second.getY(), true));
                    }
                }
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

    /*cout << "vertexList[0]" << endl;
    for(auto v : vertexList[0]){
        cout << v.toString() << " ";
    }

    cout << endl;

    cout << "vertexList[1]" << endl;
    for(auto v : vertexList[1]){
        cout << v.toString() << " ";
    }

    cout << endl;*/
}

void WeilerAtherton::sortIntersections(Point2D &startPoint, vector<Point2D> &list) {
    if(list.size() == 0){
        return;
    }
    else if(list.size() == 1) {
        if (startPoint == *list.begin()) {
            startPoint.setIntersectionPoint(true);
            list.pop_back();
        }
    } else {
        for (int i = 0; i < list.size() - 1; i++) {
            for (int j = 0; j < list.size() - 1 - i; j++) {
                if (startPoint.getDistance(list[j]) > startPoint.getDistance(list[j + 1])) {
                    Point2D p = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = p;
                }
            }

            if(startPoint == list[0]){
                startPoint.setIntersectionPoint(true);
                for(int i = 0; i < list.size() - 1; i++){
                    list[i] = list[i+1];
                }
                list.pop_back();
            }
        }
    }
}

WeilerAtherton::WeilerAtherton(const Prism &first, const Prism &second) : firstPrism(first), secondPrism(second), valid(false) {

}

void WeilerAtherton::doWeilerAtherton() {
    if (valid == true)
        return;
    cout << "--> doWeilerAtherton" << endl;

    generateVertexLists();

    vector<Point2D> *intersectionPart = nullptr;
    bool insideIntersectionFlag = false;
    int switcher = 0;
    bool first = true;
    Point2D* currentPoint = getStartPoint();
    Point2D* startPoint = currentPoint;
    Point2D* intersectionStartPoint;
    Point2D* intersectionEndPoint = nullptr;
    do {
        //jeśli wchodzimy z pierwszego wielokąta do wnętrza drugiego
        if (!insideIntersectionFlag && switcher == 0 && currentPoint->isIntersectionPoint()) {
            //ustawiamy flagę, że jesteśmy wewnątrz części wspólnej
            insideIntersectionFlag = true;
            //ustawiamy punkt startowy przecięcia
            intersectionStartPoint = currentPoint;
            //tworzymy nowy fragment części wspólnej
            if (intersectionPart != nullptr) {
                delete intersectionPart;
            }
            intersectionPart = new vector<Point2D>;
            //dodajemy punkt do części wspólnej
            intersectionPart->push_back(*currentPoint);

        } else if (insideIntersectionFlag && !currentPoint->isIntersectionPoint()) {
            //idziemy po części wspólnej więc dodajemy kolejne punkty do przecięcia
            intersectionPart->push_back(*currentPoint);

        } else if (insideIntersectionFlag && switcher == 0 && currentPoint->isIntersectionPoint()) {
            //idąc po pierwszym wielokącie dotarliśmy do kolejnego punktu przecięcia więc przechodzimy na drugi
            switcher = 1;
            if(intersectionEndPoint == nullptr) {
                intersectionEndPoint = currentPoint;
            }
            intersectionPart->push_back(*currentPoint);
        } else if (insideIntersectionFlag && switcher == 1 && currentPoint->isIntersectionPoint()) {
            //idąc po drugim wielokącie osiągnęliśmy punkt przecięcia
            if (*currentPoint == *intersectionStartPoint) {
                //jeśli jest to punkt startowy przecięcia to zamykamy nowy wielokąt i dodajemy nową gotową część przecięcia do listy
                Prism pr(*intersectionPart);
                pr.addHeightRanges(firstPrism.getHeightRanges());
                pr.addHeightRanges(secondPrism.getHeightRanges());
                intersectionParts.add(pr);
                currentPoint = intersectionEndPoint;
                intersectionEndPoint = nullptr;
                insideIntersectionFlag = false;
            }
            switcher = 0;
            intersectionPart->push_back(*currentPoint);
        }
        currentPoint->setVisited(true);
        //cout << "ODWIEDZONY: " << currentPoint->toString() << endl;
        while(currentPoint->isVisited() && (first || *currentPoint != *startPoint)) {
            currentPoint = &(vertexList[switcher].getNext(*currentPoint));
            first = false;
        }
    } while (*currentPoint != *startPoint);

    if (intersectionPart != nullptr) {
        delete intersectionPart;
    }

    valid = true;
}

Collection<Prism> WeilerAtherton::getFirstParts() {
    return firstParts;
}

Collection<Prism> WeilerAtherton::getSecondParts() {
    return secondParts;
}

Collection<Prism> WeilerAtherton::getIntersectionParts() {
    return intersectionParts;
}

Collection<Prism> WeilerAtherton::getAllParts() {
    Collection<Prism> result;
    result.add(firstParts);
    result.add(intersectionParts);
    result.add(secondParts);
    return result;
}

Point2D* WeilerAtherton::getStartPoint() {
    Point2D* pointToReturn = &vertexList[0][0];
    while(pointToReturn->isIntersectionPoint() || secondPrism.getBase().isInside(*pointToReturn)){
        pointToReturn = &(vertexList[0].getNext(*pointToReturn));
    }
    //cout << "start point: " << pointToReturn->toString() << endl;
    return pointToReturn;
}
