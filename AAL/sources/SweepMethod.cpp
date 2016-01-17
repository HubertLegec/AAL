//
// Created by hubert.legec on 2015-12-16.
//

#include <iostream>
#include "../headers/SweepMethod.h"

using namespace std;



SweepMethod::SweepMethod(const Prism &firstPrism, const Prism &secondPrism) : firstPrism(firstPrism), secondPrism(secondPrism){

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

    /*while(!Q.empty()){
        cout << Q.top()->toString() << " " << Q.top()->getSecondEndpoint()->toString() << endl;
        Q.pop();
    }
    cout << endl;
    return;*/

    while(!Q.empty()){
        cout << S.toString();
        auto event = Q.top();
        Q.pop();
        cout << "POP: " << event->toString() << " " << event->getSecondEndpoint()->toString() << endl;

        if(event->isLeft()){    //jesli to poczatek odcinka
            cout << "is left\n";
            auto pos = S.insert(event);
            event->setInsideOtherPolygonFlag(S.prev(pos));
            possibleIntersection(pos, S.next(pos));
            possibleIntersection(pos, S.prev(pos));
        } else{ //koniec odcinka
            cout << "is right\n";
            S.sort(event->getX());
            auto next = S.next(event->getSecondEndpoint());
            auto prev = S.prev(event->getSecondEndpoint());
            if(event->isInside()){
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

    for(int i = 0; i < firstPrismVertices.size(); i++){
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(firstPrismVertices[i]));
        auto ep2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(firstPrismVertices[(i+1) % firstPrismVertices.size()]));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        ep1->setPolygonType(PolygonType::SUBJECT);
        ep2->setPolygonType(PolygonType::SUBJECT);
        if(ep1->getX() < ep2->getX() || (ep1->getX() == ep2->getX() && ep1->getY() < ep2->getY())){
            ep1->setLeft(true);
            ep2->setLeft(false);
        } else {
            ep1->setLeft(false);
            ep2->setLeft(true);
        }
        Q.push(ep1);
        Q.push(ep2);
    }

    for(int i = 0; i < secondPrismVertices.size(); i++){
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(secondPrismVertices[i]));
        auto ep2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(secondPrismVertices[(i+1) % secondPrismVertices.size()]));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        ep1->setPolygonType(PolygonType::CLIPPING);
        ep2->setPolygonType(PolygonType::CLIPPING);
        if(ep1->getX() < ep2->getX() || (ep1->getX() == ep2->getX() && ep1->getY() < ep2->getY())){
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
    if(first == nullptr || second == nullptr){
        return;
    }
    cout << "->possible intersections: ";
    Line2D line1(*first, *first->getSecondEndpoint());
    Line2D line2(*second, *second->getSecondEndpoint());
    cout << line1.toString() << " io: " << first->isInOut() << " ins: " << first->isInside() <<  " ; " << line2.toString() << " io: " << second->isInOut() << " ins: " << second->isInside() << endl;
    auto intersection = line1.getIntersectionPoint(line2);
    if(isValidIntersection(line1, line2, intersection.second, intersection.first)){
        cout << "->valid inters: " << intersection.second.toString() << endl;

        auto firstEnd = first->getSecondEndpoint();
        firstEnd->setInside(!firstEnd->isInside());
        auto p1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p1->setSecondEndpoint(firstEnd);
        p1->setInside(firstEnd->isInside());
        p1->setInOut(first->isInOut());
        p1->setPolygonType(first->getPolygonType());
        p1->setLeft(true);
        p1->setEdgeType(firstEnd->getEdgeType());
        p1->setPolygonType(firstEnd->getPolygonType());
        firstEnd->setSecondEndpoint(p1);

        auto p2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p2->setSecondEndpoint(first);
        p2->setInside(first->isInside());
        p2->setInOut(first->isInOut());
        p2->setPolygonType(first->getPolygonType());
        p2->setLeft(false);
        p2->setEdgeType(firstEnd->getEdgeType());
        p2->setPolygonType(firstEnd->getPolygonType());
        first->setSecondEndpoint(p2);

        auto secondEnd = second->getSecondEndpoint();
        secondEnd->setInside(!secondEnd->isInside());
        auto p3 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p3->setSecondEndpoint(secondEnd);
        p3->setInside(secondEnd->isInside());
        p3->setInOut(second->isInOut());
        p3->setPolygonType(second->getPolygonType());
        p3->setLeft(true);
        p3->setEdgeType(secondEnd->getEdgeType());
        p3->setPolygonType(secondEnd->getPolygonType());
        secondEnd->setSecondEndpoint(p3);

        auto p4 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(intersection.second));
        p4->setSecondEndpoint(second);
        p4->setInside(second->isInside());
        p4->setInOut(second->isInOut());
        p4->setPolygonType(second->getPolygonType());
        p4->setLeft(false);
        p4->setEdgeType(second->getEdgeType());
        p4->setPolygonType(second->getPolygonType());
        second->setSecondEndpoint(p4);

        //cout << "P1: " << p1->toString() << " P2: " << p2->toString() << " P3: " << p3->toString() << " P4: " << p4->toString() << endl;
        Q.push(p2);
        Q.push(p4);
        Q.push(p1);
        Q.push(p3);
    }
}

void SweepMethod::addToIntersection(Point2D startPoint, Point2D endPoint) {
    cout << "->add to intersection: " << startPoint.toString() << " " << endPoint.toString() << endl;
    bool added = false;
    bool front = false;
    int checkFirst = -1;
    int checkSecond = -1;
    auto iter = resultPartsBegin.find(startPoint);
    auto p1 = startPoint;
    auto p2 = endPoint;

    if(iter == resultPartsBegin.end() && resultPartsBegin.find(endPoint) != resultPartsBegin.end()){
        iter = resultPartsBegin.find(endPoint);
        p1 = endPoint;
        p2 = startPoint;
    }

    if(iter != resultPartsBegin.end()){
        auto l = iter->second;
        if(l->back() == p2){
            vector<Point2D> v;
            for(auto p : *l){
                v.push_back(p);
            }
            intersectionParts.add(Prism(v));
            resultPartsBegin.erase(iter);
            resultPartsEnd.erase(p2);
        } else {
            auto eIter = resultPartsBegin.find(p2);
            auto eIterE = resultPartsEnd.find(p2);
            if(eIter != resultPartsBegin.end()){
                auto l2 = eIter->second;
                resultPartsBegin.erase(eIter);
                resultPartsEnd.erase(l2->back());
                for(auto v : *l2){
                    l->push_front(v);
                }
            } else if(eIterE != resultPartsEnd.end()){
                auto l2 = eIterE->second;
                resultPartsEnd.erase(eIterE);
                resultPartsBegin.erase(l2->front());
                for(int i = l2->size() - 1; i >= 0; i--){
                    l->push_front((*l2)[i]);
                }
            } else {
                l->push_front(p2);
            }
            resultPartsBegin.erase(iter);
            resultPartsBegin.insert(make_pair(l->front(), l));
        }
    } else {
        auto iter2 = resultPartsEnd.find(startPoint);
        auto p11 = startPoint;
        auto p22 = endPoint;

        if(iter2 == resultPartsEnd.end() && resultPartsEnd.find(endPoint) != resultPartsEnd.end()){
            iter2 = resultPartsEnd.find(endPoint);
            p11 = endPoint;
            p22 = startPoint;
        }

        if(iter2 != resultPartsEnd.end()){
            auto l = iter2->second;
            if(l->front() == p22){
                vector<Point2D> v;
                for(auto p : *l){
                    v.push_back(p);
                }
                intersectionParts.add(Prism(v));
                resultPartsEnd.erase(iter);
                resultPartsBegin.erase(p2);
            } else {
                auto eIter2 = resultPartsEnd.find(p22);
                auto eIterE2 = resultPartsBegin.find(p22);
                if(eIter2 != resultPartsEnd.end()){
                    auto l2 = eIter2->second;
                    resultPartsEnd.erase(eIter2);
                    resultPartsBegin.erase(l2->front());
                    for(int i = l2->size() - 1; i >= 0; i--){
                        l->push_back((*l2)[i]);
                    }
                } else if(eIterE2 != resultPartsBegin.end()){
                    auto l2 = eIterE2->second;
                    resultPartsBegin.erase(eIterE2);
                    resultPartsEnd.erase(l2->back());
                    for(auto v : *l2){
                        l->push_back(v);
                    }
                } else {
                    l->push_back(p2);
                }
                resultPartsEnd.erase(iter2);
                resultPartsEnd.insert(make_pair(l->back(), l));
            }
        }
    }


    if(!added){
        cout << "new result element created\n";
        auto newD = make_shared<deque<Point2D>>();
        newD->push_back(startPoint);
        newD->push_back(endPoint);
        resultPartsBegin.insert(make_pair(startPoint, newD));
        resultPartsEnd.insert(make_pair(endPoint, newD));
    }
}

bool SweepMethod::isValidIntersection(const Line2D &l1, const Line2D &l2,
                                      const Point2D &p, bool result) {
    if(!result) {
        return false;
    } else if(p == l1.getStart() && (p == l2.getStart() || p == l2.getEnd() )){
        return false;
    } else if(p == l1.getEnd() && (p == l2.getEnd() || p == l2.getStart())){
        return false;
    } else {
        return true;
    }
}