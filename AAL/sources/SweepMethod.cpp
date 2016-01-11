//
// Created by hubert.legec on 2015-12-16.
//

#include <iostream>
#include "../headers/SweepMethod.h"

using namespace std;

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

    cout << "Q:\n";
    while(!Q.empty()){
        auto e = Q.top();
        Q.pop();
        cout << e->toString() << " ";
    }
    cout << endl;
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
