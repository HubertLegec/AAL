//
// Created by hubert.legec on 2015-12-16.
//

#include "../headers/SweepMethod.h"

SweepMethod::SweepMethod(const Prism &firstPrism, const Prism &secondPrism) : firstPrism(firstPrism), secondPrism(secondPrism){ }

std::vector<Prism> SweepMethod::getIntersectionParts() {
    if(!isValid){
        doClipping();
    }
    return intersectionParts.getItems();
}

std::vector<Prism> SweepMethod::getFirstPrismParts() {
    if(!isValid){
        doClipping();
    }
    return clippedFirstPrism.getItems();
}

std::vector<Prism> SweepMethod::getSecondPrismParts() {
    if(!isValid){
        doClipping();
    }
    return clippedSecondPrism.getItems();
}

std::vector<Prism> SweepMethod::getAllParts() {
    if(!isValid){
        doClipping();
    }
    Collection result;
    result.add(intersectionParts);
    result.add(clippedFirstPrism);
    result.add(clippedSecondPrism);
    return result.getItems();
}

void SweepMethod::doClipping() {

}
