//
// Created by hubert.legec on 2015-12-16.
//

#include <iostream>
#include "../headers/SweepMethod.h"

using namespace std;

TempBuffer::TempBuffer() { }

void TempBuffer::erase(shared_ptr<EdgeEndpoint> endpoint) {
    //TODO
}

shared_ptr<EdgeEndpoint> TempBuffer::insert(shared_ptr<EdgeEndpoint> endpoint) {
    //TODO
    return 0;
}

shared_ptr<EdgeEndpoint> TempBuffer::find(shared_ptr<EdgeEndpoint> endpoint) {
    //TODO
    return 0;
}

shared_ptr<EdgeEndpoint> TempBuffer::prev(shared_ptr<EdgeEndpoint> endpoint) {
    //TODO
    return elements[0];
}

std::shared_ptr<EdgeEndpoint> TempBuffer::next(shared_ptr<EdgeEndpoint> endpoint) {
    //TODO
    return elements[0];
}


//-----------------------------------------------------------------------------------------------------------------------------

SweepMethod::SweepMethod(const Prism &firstPrism, const Prism &secondPrism) : firstPrism(firstPrism), secondPrism(secondPrism){

}

Collection<Prism> SweepMethod::getIntersectionParts() {
    if(!isValid){
        doClipping();
    }
    return intersectionParts.getItems();
}

Collection<Prism> SweepMethod::getFirstPrismParts() {
    if(!isValid){
        doClipping();
    }
    return clippedFirstPrism.getItems();
}

Collection<Prism> SweepMethod::getSecondPrismParts() {
    if(!isValid){
        doClipping();
    }
    return clippedSecondPrism.getItems();
}

Collection<Prism> SweepMethod::getAllParts() {
    if(!isValid){
        doClipping();
    }
    Collection<Prism> result;
    result.add(intersectionParts);
    result.add(clippedFirstPrism);
    result.add(clippedSecondPrism);
    return result.getItems();
}

void SweepMethod::doClipping() {
    if(isValid){
        return;
    }
    initQ();

    while(!Q.empty()){
        auto event = Q.top();
        Q.pop();
        cout << "POP: " << event->toString() << endl;

        if(event->isLeft()){    //jesli to poczatek odcinka
            auto pos = S.insert(event);
            event->setInsideOtherPolygonFlag(S.prev(pos));
            possibleIntersection(pos, S.next(pos));
            possibleIntersection(pos, S.prev(pos));
        } else{ //koniec odcinka
            auto pos = S.find(event->getSecondEndpoint());
            auto next = S.next(pos);
            auto prev = S.prev(pos);
            if(event->isInside()){
                addToIntersection(*event->getSecondEndpoint().get(), *event.get());
            }
            S.erase(pos);
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

void SweepMethod::possibleIntersection(std::shared_ptr<EdgeEndpoint> fir, std::shared_ptr<EdgeEndpoint> sec) {
    //TODO
}
