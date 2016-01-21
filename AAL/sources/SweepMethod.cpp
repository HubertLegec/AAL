/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

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

    while(!Q.empty()){
        cout << S.toString() << endl;
        auto event = Q.top();
        Q.pop();

        if(event->isLeft()){    //jesli to poczatek odcinka
            auto pos = S.insert(event);
            event->setInsideOtherPolygonFlag(S.prev(pos));
            possibleIntersection(pos, S.next(pos));
            possibleIntersection(pos, S.prev(pos));
        } else{ //koniec odcinka
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
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(firstPrismVertices[i], PolygonType::SUBJECT));
        auto ep2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(firstPrismVertices[(i+1) % firstPrismVertices.size()], PolygonType::SUBJECT));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        if(ep1->isToTheLeftOf(*ep2)){
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
        auto ep1 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(secondPrismVertices[i], PolygonType::CLIPPING));
        auto ep2 = shared_ptr<EdgeEndpoint>(new EdgeEndpoint(secondPrismVertices[(i+1) % secondPrismVertices.size()], PolygonType::CLIPPING));
        ep1->setSecondEndpoint(ep2);
        ep2->setSecondEndpoint(ep1);
        if(ep1->isToTheLeftOf(*ep2)){
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
    Line2D line1(*first, *first->getSecondEndpoint());
    Line2D line2(*second, *second->getSecondEndpoint());
    auto intersection = line1.getIntersectionPoint(line2);
    if(isValidIntersection(line1, line2, intersection.second, intersection.first)){

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
        if(line1.getOrientation(line2.getEnd()) == Orientation::COLINEAR && line1.getOrientation(line2.getStart()) == Orientation::COLINEAR){
            if(line1.getStart() < line2.getStart()){
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
    cout << "add to intersection: " << startPoint.toString() << " ; " << endPoint.toString() << endl;
    bool added = false;
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
        added = true;
        if(l->back() == p2){
            vector<Point2D> v;
            for(auto p : *l){
                v.push_back(p);
            }
            Prism p(v);
            p.addHeightRanges(firstPrism.getHeightRanges());
            p.addHeightRanges(secondPrism.getHeightRanges());
            intersectionParts.add(p);
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
            added = true;
            auto l = iter2->second;
            if(l->front() == p22){
                vector<Point2D> v;
                for(auto p : *l){
                    v.push_back(p);
                }
                Prism p(v);
                p.addHeightRanges(firstPrism.getHeightRanges());
                p.addHeightRanges(secondPrism.getHeightRanges());
                intersectionParts.add(p);
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
        auto newD = make_shared<deque<Point2D>>();
        newD->push_back(startPoint);
        newD->push_back(endPoint);
        resultPartsBegin.insert(make_pair(startPoint, newD));
        resultPartsEnd.insert(make_pair(endPoint, newD));
    }
    cout << "intersection parts:\n";
    for(auto p : intersectionParts){
       cout <<  p.toString() << endl;
    }

    cout << "rp begin:\n";
    for(auto p : resultPartsBegin){
        cout << "***" << p.first.toString() << endl;
        for(auto f : *p.second){
            cout << f.toString() << " ";
        }
        cout << endl;
    }

    cout << "rp end:\n";
    for(auto p : resultPartsEnd){
        cout << "***" << p.first.toString() << endl;
        for(auto f : *p.second){
            cout << f.toString() << " ";
        }
        cout << endl;
    }
}

bool SweepMethod::isValidIntersection(const Line2D &l1, const Line2D &l2, const Point2D &p, bool result) {
    if(!result) {
        return false;
    } else if((p == l1.getStart() || p == l1.getEnd()) && (p == l2.getStart() || p == l2.getEnd() )){
        return false;
    }  else {
        return true;
    }
}