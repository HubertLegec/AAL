/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <iostream>
#include "../headers/SweepMethod.h"

using namespace std;


SweepMethod::SweepMethod(const Prism &firstPrism, const Prism &secondPrism) : firstPrism(firstPrism),
                                                                              secondPrism(secondPrism) {

}

Collection<Prism> SweepMethod::getIntersectionParts() {
    return intersectionParts.getItems();
}

Collection<Prism> SweepMethod::getFirstPrismParts() {
    return clippedFirstPrism.getItems();
}

Collection<Prism> SweepMethod::getSecondPrismParts() {
    return clippedSecondPrism.getItems();
}

Collection<Prism> SweepMethod::getAllParts() {
    Collection<Prism> result;
    result.add(intersectionParts);
    result.add(clippedFirstPrism);
    result.add(clippedSecondPrism);
    return result.getItems();
}

void SweepMethod::doClipping() {
    initQ();

    while (!Q.empty()) {
        auto event = Q.top();
        Q.pop();

        if (event->isLeft()) {    //jesli to poczatek odcinka
            auto pos = S.insert(event);
            event->setInsideOtherPolygonFlag(S.prev(pos));
            possibleIntersection(pos, S.next(pos));
            possibleIntersection(pos, S.prev(pos));
        } else { //koniec odcinka
            S.sort(event->getX());
            auto next = S.next(event->getSecondEndpoint());
            auto prev = S.prev(event->getSecondEndpoint());
            if (event->isInside()) {
                addToIntersection(*event->getSecondEndpoint().get(), *event.get());
            }
            S.erase(event->getSecondEndpoint());
            possibleIntersection(prev, next);
        }
    }
}

void SweepMethod::initQ() {
    vector<Point2D> firstPrismVertices = firstPrism.getVertexList().getItems();
    vector<Point2D> secondPrismVertices = secondPrism.getVertexList().getItems();

    for (int i = 0; i < firstPrismVertices.size(); i++) {
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(firstPrismVertices[i], PolygonType::SUBJECT));
        auto ep2 = shared_ptr<EdgeEndpoint>(
                new EdgeEndpoint(firstPrismVertices[(i + 1) % firstPrismVertices.size()], PolygonType::SUBJECT));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        if (ep1->isToTheLeftOf(*ep2)) {
            ep1->setLeft(true);
            ep2->setLeft(false);
        } else {
            ep1->setLeft(false);
            ep2->setLeft(true);
        }
        Q.push(ep1);
        Q.push(ep2);
    }

    for (int i = 0; i < secondPrismVertices.size(); i++) {
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(secondPrismVertices[i], PolygonType::CLIPPING));
        auto ep2 = shared_ptr<EdgeEndpoint>(
                new EdgeEndpoint(secondPrismVertices[(i + 1) % secondPrismVertices.size()], PolygonType::CLIPPING));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        if (ep1->isToTheLeftOf(*ep2)) {
            ep1->setLeft(true);
            ep2->setLeft(false);
        } else {
            ep1->setLeft(false);
            ep2->setLeft(true);
        }
        Q.push(ep1);
        Q.push(ep2);
    }
}

void SweepMethod::possibleIntersection(std::shared_ptr<EdgeEndpoint> first, std::shared_ptr<EdgeEndpoint> second) {
    if (first == nullptr || second == nullptr) {
        return;
    }
    Line2D line1(*first, *first->getSecondEndpoint());
    Line2D line2(*second, *second->getSecondEndpoint());
    auto intersection = line1.getIntersectionPoint(line2);
    if (isValidIntersection(line1, line2, intersection.second, intersection.first)) {

        auto firstEnd = first->getSecondEndpoint();
        firstEnd->setInside(!firstEnd->isInside());
        auto p1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p1->joinToExistingEnd(firstEnd);
        firstEnd->setSecondEndpoint(p1);

        auto p2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p2->joinToExistingEnd(first);
        first->setSecondEndpoint(p2);

        auto secondEnd = second->getSecondEndpoint();
        secondEnd->setInside(!secondEnd->isInside());
        auto p3 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p3->joinToExistingEnd(secondEnd);
        secondEnd->setSecondEndpoint(p3);

        auto p4 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p4->joinToExistingEnd(second);
        second->setSecondEndpoint(p4);

        Q.push(p2);
        Q.push(p4);
        Q.push(p1);
        Q.push(p3);
    } else {
        if (line1.getOrientation(line2.getEnd()) == Orientation::COLINEAR &&
            line1.getOrientation(line2.getStart()) == Orientation::COLINEAR) {
            if (line1.getStart() < line2.getStart()) {
                auto firstEnd = first->getSecondEndpoint();
                auto secondEnd = second->getSecondEndpoint();
                firstEnd->setSecondEndpoint(second);
                second->setSecondEndpoint(firstEnd);
                second->setInside(true);
                second->getSecondEndpoint()->setInside(true);

                auto newFirstEnd = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(line2.getStart()));
                newFirstEnd->joinToExistingEnd(first);
                first->setSecondEndpoint(newFirstEnd);

                auto newThirdStart = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(line1.getEnd()));
                newThirdStart->joinToExistingEnd(secondEnd);
                secondEnd->setSecondEndpoint(newThirdStart);

                Q.push(newFirstEnd);
                Q.push(newThirdStart);
            } else {
                auto firstEnd = first->getSecondEndpoint();
                auto secondEnd = second->getSecondEndpoint();
                secondEnd->setSecondEndpoint(first);
                first->setSecondEndpoint(secondEnd);
                first->setInside(true);
                first->getSecondEndpoint()->setInside(true);

                auto newSecondEnd = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(line1.getStart()));
                newSecondEnd->joinToExistingEnd(second);
                second->setSecondEndpoint(newSecondEnd);

                auto newThirdStart = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(line2.getEnd()));
                newThirdStart->joinToExistingEnd(firstEnd);
                firstEnd->setSecondEndpoint(newThirdStart);

                Q.push(newSecondEnd);
                Q.push(newThirdStart);
            }
        }
    }
}

void SweepMethod::addToIntersection(Point2D startPoint, Point2D endPoint) {
    auto sIter = resultParts.find(startPoint);
    auto eIter = resultParts.find(endPoint);

    if (sIter != resultParts.end() && eIter != resultParts.end() && sIter->second == eIter->second) {
        //Jeśli domknięcie wielokąta
        vector<Point2D> v;
        for (auto p : *sIter->second) {
            v.push_back(p);
        }
        Prism p(v);
        p.addHeightRanges(firstPrism.getHeightRanges());
        p.addHeightRanges(secondPrism.getHeightRanges());
        intersectionParts.add(p);
        resultParts.erase(sIter);
        resultParts.erase(eIter);
    } else if (sIter != resultParts.end() && eIter != resultParts.end() && sIter->second != eIter->second) {
        //trzeba połączyć dwie listy
        if (sIter->first == sIter->second->front() && eIter->first == eIter->second->front()) {
            //łączymy przody list
            auto toErase = resultParts.find(eIter->second->back());
            for (auto el : *eIter->second) {
                sIter->second->push_front(el);
            }
            resultParts.erase(eIter);
            resultParts.erase(toErase);
            resultParts.insert(make_pair(sIter->second->front(), sIter->second));
            resultParts.erase(sIter);
        } else if (sIter->first == sIter->second->back() && eIter->first == eIter->second->back()) {
            //łączymy tyły list
            auto toErase = resultParts.find(eIter->second->front());
            for (int i = eIter->second->size() - 1; i >= 0; i--) {
                sIter->second->push_back((*eIter->second)[i]);
            }
            resultParts.erase(eIter);
            resultParts.erase(toErase);
            resultParts.insert(make_pair(sIter->second->back(), sIter->second));
            resultParts.erase(sIter);
        } else if (sIter->first == sIter->second->back() && eIter->first == eIter->second->front()) {
            //łączymy tył pierwszej z początkiem drugiej
            auto toErase = resultParts.find(eIter->second->back());
            for (auto el : *eIter->second) {
                sIter->second->push_back(el);
            }
            resultParts.erase(eIter);
            resultParts.erase(toErase);
            resultParts.insert(make_pair(sIter->second->back(), sIter->second));
            resultParts.erase(sIter);
        } else if (sIter->first == sIter->second->front() && eIter->first == eIter->second->back()) {
            //łączymy początek pierwszej z końcem drugiej
            auto toErase = resultParts.find(sIter->second->back());
            for (auto el : *sIter->second) {
                eIter->second->push_back(el);
            }
            resultParts.erase(sIter);
            resultParts.erase(toErase);
            resultParts.insert(make_pair(eIter->second->back(), eIter->second));
            resultParts.erase(eIter);
        }
    } else if (sIter != resultParts.end()) {
        //pierwszy punkt już istnieje w liście
        auto l = sIter->second;
        if (startPoint == l->front()) {
            l->push_front(endPoint);
        } else {
            l->push_back(endPoint);
        }
        resultParts.erase(sIter);
        resultParts.insert(make_pair(endPoint, l));
    } else if (eIter != resultParts.end()) {
        //drugi punkt już istnieje w liście
        auto l = eIter->second;
        if (endPoint == l->front()) {
            l->push_front(startPoint);
        } else {
            l->push_back(startPoint);
        }
        resultParts.erase(eIter);
        resultParts.insert(make_pair(startPoint, l));
    } else {
        //żadnego z punktów nie ma jeszcze na liście
        auto newD = make_shared<deque<Point2D>>();
        newD->push_back(startPoint);
        newD->push_back(endPoint);
        resultParts.insert(make_pair(startPoint, newD));
        resultParts.insert(make_pair(endPoint, newD));
    }
}

bool SweepMethod::isValidIntersection(const Line2D &l1, const Line2D &l2, const Point2D &p, bool result) {
    if (!result) {
        return false;
    } else if ((p == l1.getStart() || p == l1.getEnd()) && (p == l2.getStart() || p == l2.getEnd())) {
        return false;
    } else {
        return true;
    }
}