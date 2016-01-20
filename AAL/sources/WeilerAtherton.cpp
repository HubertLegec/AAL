/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <iostream>
#include <memory>
#include "../headers/WeilerAtherton.h"
#include "../headers/Line2D.h"

using namespace std;

void WeilerAtherton::generateVertexLists() {
    vector<shared_ptr<Point2D>> firstPrismVertices;
    for(Point2D p : firstPrism.getVertexList().getItems()){
        firstPrismVertices.push_back(shared_ptr<Point2D>(new Point2D(p)));
    }
    vector<shared_ptr<Point2D>> secondPrismVertices;
    for(Point2D p : secondPrism.getVertexList().getItems()){
        secondPrismVertices.push_back(shared_ptr<Point2D>(new Point2D(p)));
    }
    vector<vector<shared_ptr<Point2D>>> firstTempList(firstPrism.getVertexList().getSize());
    vector<vector<shared_ptr<Point2D>>> secondTempList(secondPrism.getVertexList().getSize());

    //dla każdego boku pierwszego wielokąta
    for (int i = 0; i < firstPrismVertices.size(); i++) {
        int inext = (i + 1) % firstPrismVertices.size();
        Line2D firstLine(*firstPrismVertices[i], *firstPrismVertices[inext]);

        //sprawdź przecięcie z każdym bokiem drugiego wielokąta
        for (int j = 0; j < secondPrismVertices.size(); j++) {
            int jnext = (j + 1) % secondPrismVertices.size();
            Line2D secondLine(*secondPrismVertices[j], *secondPrismVertices[jnext]);
            //sprawdź czy segmenty boków mają część wspólną
            if (firstLine.intersectableSegment(secondLine)) {
                //wyznacz punkt przecięcia
                pair<bool, Point2D> p = firstLine.getIntersectionPoint(secondLine);
                //jeśli istnieje punkt przecięcia to dodaj nowy wierzchołek
                if(p.first) {
                    if (p.second == firstLine.getEnd()) {
                        firstPrismVertices[inext]->setIntersectionPoint(true);
                        secondTempList[j].push_back(firstPrismVertices[inext]);
                    } else if(p.second == firstLine.getStart()){
                        firstPrismVertices[i]->setIntersectionPoint(true);
                        secondTempList[j].push_back(firstPrismVertices[i]);
                    }
                    else if (p.second == secondLine.getEnd()) {
                        secondPrismVertices[jnext]->setIntersectionPoint(true);
                        secondTempList[i].push_back(secondPrismVertices[jnext]);
                    } else if(p.second == secondLine.getStart()){
                        secondPrismVertices[j]->setIntersectionPoint(true);
                        firstTempList[i].push_back(secondPrismVertices[j]);
                    } else {
                        auto point = make_shared<Point2D>(p.second.getX(), p.second.getY(), true);
                        firstTempList[i].push_back(point);
                        secondTempList[j].push_back(point);
                    }
                }
            }
        }
    }

    for (int i = 0; i < firstPrism.getVertexList().getSize(); i++) {
        sortIntersections(firstPrismVertices[i], firstTempList[i]);
        vertexList[0].add(firstPrismVertices[i]);
        vertexList[0].add(firstTempList[i]);

    }

    for (int i = 0; i < secondPrism.getVertexList().getSize(); i++) {
        sortIntersections(secondPrismVertices[i], secondTempList[i]);
        vertexList[1].add(secondPrismVertices[i]);
        vertexList[1].add(secondTempList[i]);
    }

    cout << "PO:\n";
    for(auto p : vertexList[0]){
        cout << p->toString() << " ";
    }
    cout << endl;

    cout << "P1:\n";
    for(auto p : vertexList[1]){
        cout << p->toString() << " ";
    }
    cout << endl;

}

void WeilerAtherton::sortIntersections(shared_ptr<Point2D> startPoint, vector<shared_ptr<Point2D>> &list) {
    if(list.size() == 0){
        return;
    }
    else if(list.size() == 1) {
        if (startPoint == *list.begin()) {
            startPoint->setIntersectionPoint(true);
            list.pop_back();
        }
    } else {
        for (int i = 0; i < list.size() - 1; i++) {
            for (int j = 0; j < list.size() - 1 - i; j++) {
                if (startPoint->getDistance(*list[j]) > startPoint->getDistance(*list[j + 1])) {
                    shared_ptr<Point2D> p = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = p;
                }
            }

            if(startPoint == list[0]){
                startPoint->setIntersectionPoint(true);
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
    if (valid) {
        return;
    }

    generateVertexLists();

    if(vertexList[0].getSize() == firstPrism.getVertexList().getSize() && vertexList[1].getSize() == secondPrism.getVertexList().getSize()){
        checkOneInsideAnother();
        return;
    }

    bool firstInsideSecond = true;

    for(auto v : vertexList[0].getItems()){
        if(!secondPrism.getBase().isInside(*v)){
            firstInsideSecond = false;
            break;
        }
    }

    if(firstInsideSecond){
        intersectionParts.add(firstPrism);
        return;
    }

    bool secondInsideFirst = true;

    for(auto v : vertexList[1].getItems()){
        if(!firstPrism.getBase().isInside(*v)){
            secondInsideFirst = false;
            break;
        }
    }

    if(secondInsideFirst){
        intersectionParts.add(secondPrism);
        return;
    }

    vector<Point2D> *intersectionPart = nullptr;
    //punkty startowe elementow pierwszego wielokata
    vector<shared_ptr<Point2D>> partsStartPoints;
    bool insideIntersectionFlag = false;
    int switcher = 0;
    int previousSwitcher = 0;
    bool first = true;
    bool firstInters = false;
    shared_ptr<Point2D> currentPoint = getStartPoint();
    shared_ptr<Point2D> previousPoint = nullptr;
    shared_ptr<Point2D> startPoint = currentPoint;
    shared_ptr<Point2D> intersectionStartPoint = nullptr;
    shared_ptr<Point2D> intersectionEndPoint = nullptr;
    do {
        //jeśli wchodzimy z pierwszego wielokąta do wnętrza drugiego
        if (!insideIntersectionFlag && switcher == 0 && currentPoint->isIntersectionPoint()) {
            //ustawiamy flagę, że jesteśmy wewnątrz części wspólnej
            insideIntersectionFlag = true;
            //ustawiamy punkt startowy przecięcia
            intersectionStartPoint = currentPoint;
            firstInters = true;
            //tworzymy nowy fragment części wspólnej
            if (intersectionPart != nullptr) {
                delete intersectionPart;
            }
            intersectionPart = new vector<Point2D>;
            //dodajemy punkt do części wspólnej
            intersectionPart->push_back(*currentPoint);

            //dodajemy czesc pierwszego i drugiego wielokata do listy
            partsStartPoints.push_back(currentPoint);

        } else if (insideIntersectionFlag && !currentPoint->isIntersectionPoint()) {
            //idziemy po części wspólnej więc dodajemy kolejne punkty do przecięcia
            intersectionPart->push_back(*currentPoint);

        } else if (insideIntersectionFlag && switcher == 0 && currentPoint->isIntersectionPoint()) {
            //idąc po pierwszym wielokącie dotarliśmy do kolejnego punktu przecięcia więc przechodzimy na drugi
            switcher = 1;
            if(intersectionEndPoint == nullptr) {
                //cout << "inters end p: " << currentPoint->toString() << endl;
                intersectionEndPoint = currentPoint;
            }
            intersectionPart->push_back(*currentPoint);
        } else if (insideIntersectionFlag && switcher == 1 && currentPoint->isIntersectionPoint()) {
            //idąc po drugim wielokącie osiągnęliśmy punkt przecięcia
            if (currentPoint == intersectionStartPoint) {
                //jeśli jest to punkt startowy przecięcia to zamykamy nowy wielokąt i dodajemy nową gotową część przecięcia do listy
                Prism pr(*intersectionPart);
                pr.addHeightRanges(firstPrism.getHeightRanges());
                pr.addHeightRanges(secondPrism.getHeightRanges());
                intersectionParts.add(pr);
                currentPoint = intersectionEndPoint;
                intersectionEndPoint = nullptr;
                intersectionStartPoint = nullptr;
                insideIntersectionFlag = false;
            } else {
                intersectionPart->push_back(*currentPoint);
                partsStartPoints.push_back(currentPoint);
            }
            switcher = 0;
        }
        if(!first && insideIntersectionFlag){
            Line2D l(*previousPoint, *currentPoint);
            if(l.getOrientation(*(vertexList[switcher].getNext(currentPoint))) == Orientation::COLINEAR && previousSwitcher != switcher){
                switcher = switcher == 0 ? 1 : 0;
            }
        }
        currentPoint->setVisited(true);
        previousPoint = currentPoint;
        previousSwitcher = switcher;
        while(currentPoint->isVisited()
              && (first || (currentPoint != startPoint))
              && (intersectionStartPoint == nullptr || firstInters || currentPoint != intersectionStartPoint)) {
            currentPoint = vertexList[switcher].getNext(currentPoint);
            first = false;
            firstInters = false;
        }
    } while (currentPoint != startPoint);


    for(auto p : partsStartPoints){
        addFirstPart(p);
        addSecondPart(p);
    }


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

shared_ptr<Point2D> WeilerAtherton::getStartPoint() {
    shared_ptr<Point2D> pointToReturn = vertexList[0][0];
    while(pointToReturn->isIntersectionPoint() || secondPrism.getBase().isInside(*pointToReturn)){
        pointToReturn = vertexList[0].getNext(pointToReturn);
    }
    return pointToReturn;
}

void WeilerAtherton::addFirstPart(shared_ptr<Point2D> point) {
    Line2D l(*vertexList[0].getPrev(point) ,*point);
    shared_ptr<Point2D> pt = vertexList[1].getPrev(point);
    if(point->isFirstPartAdded() || l.isOnLine(*pt)){
        return;
    }
    shared_ptr<Point2D> startPoint = point;
    shared_ptr<Point2D> currentPoint = point;
    int switcher = 0;
    bool first = true;
    vector<Point2D> result;
    do{
        if(currentPoint->isIntersectionPoint()){
            switcher = switcher == 0 ? 1 : 0;
        }
        currentPoint->setFirstPartAdded(true);
        result.push_back(*currentPoint);

        while(currentPoint->isFirstPartAdded() && (first || currentPoint != startPoint)){
            if(switcher == 1) {
                currentPoint = vertexList[switcher].getPrev(currentPoint);
            } else{
                currentPoint = vertexList[switcher].getNext(currentPoint);
            }
            first = false;
        }
    }while(currentPoint != startPoint);
    firstParts.add(Prism(firstPrism.getId(), firstPrism.getBottom(), firstPrism.getTop(), result));
}

void WeilerAtherton::addSecondPart(shared_ptr<Point2D> point) {
    Line2D l(*vertexList[0].getPrev(point) ,*point);
    shared_ptr<Point2D> pt = vertexList[1].getPrev(point);
    if(point->isSecondPartAdded() || l.isOnLine(*pt) || firstPrism.getBase().isInside(*(vertexList[1].getNext(point)))){
        return;
    }
    shared_ptr<Point2D> startPoint = point;
    shared_ptr<Point2D> currentPoint = point;
    int switcher = 0;
    bool first = true;
    vector<Point2D> result;
    do{
        if(currentPoint->isIntersectionPoint()){
            switcher = switcher == 0 ? 1 : 0;
        }
        currentPoint->setSecondPartAdded(true);
        result.push_back(*currentPoint);

        while (currentPoint->isSecondPartAdded() && (first || currentPoint != startPoint)){
            if(switcher == 1) {
                currentPoint = vertexList[switcher].getNext(currentPoint);
            } else{
                currentPoint = vertexList[switcher].getPrev(currentPoint);
            }
            first = false;
        }
    }while (currentPoint != startPoint);
    secondParts.add(Prism(secondPrism.getId(), secondPrism.getBottom(), secondPrism.getTop(), result));
}

void WeilerAtherton::checkOneInsideAnother() {
    //caly drugi zawiera sie w pierwszym
    if(firstPrism.getBase().isInside(secondPrism.getVertexList()[0])){
        Prism sp = secondPrism;
        sp.addHeightRanges(firstPrism.getHeightRanges());
        intersectionParts.add(sp);
        firstParts.add(firstPrism);
    } else if(secondPrism.getBase().isInside(firstPrism.getVertexList()[0])){
        //caly pierwszy zawiera sie w drugim
        Prism fp = firstPrism;
        fp.addHeightRanges(secondPrism.getHeightRanges());
        intersectionParts.add(fp);
        secondParts.add(secondPrism);
    }
}