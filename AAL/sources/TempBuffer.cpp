/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include "../headers/TempBuffer.h"

using namespace std;

TempBuffer::TempBuffer() { }

void TempBuffer::erase(shared_ptr<EdgeEndpoint> endpoint) {
    int i = 0;
    while (endpoint != elements[i] && i < elements.size()) {
        i++;
    }
    if (i < elements.size()) {
        elements.erase(elements.begin() + i);
    }
}

shared_ptr<EdgeEndpoint> TempBuffer::insert(shared_ptr<EdgeEndpoint> endpoint) {
    elements.push_back(endpoint);
    sort(endpoint->getX());
    return endpoint;
}


shared_ptr<EdgeEndpoint> TempBuffer::prev(shared_ptr<EdgeEndpoint> endpoint) {

    if (elements[0] == endpoint) {
        return nullptr;
    }
    int i = 1;
    while (elements[i] != endpoint && i < elements.size()) {
        i++;
    }
    if (i < elements.size()) {
        return elements[i - 1];
    } else {
        return nullptr;
    }
}

shared_ptr<EdgeEndpoint> TempBuffer::next(shared_ptr<EdgeEndpoint> endpoint) {
    int i = 0;
    while (elements[i] != endpoint && i < elements.size() - 1) {
        i++;
    }
    if (i == elements.size() - 1) {
        return nullptr;
    } else {
        return elements[i + 1];
    }
}

void TempBuffer::sort(float x) {
    auto comp = [&](shared_ptr<EdgeEndpoint> eep1, shared_ptr<EdgeEndpoint> eep2) -> bool {
        if (eep1->getIntersectionY(x) < eep2->getIntersectionY(x)) return true;

        if (eep1->getIntersectionY(x) > eep2->getIntersectionY(x)) return false;

        if (eep1->isVertical() && !eep2->isVertical()) return false;

        if (!eep1->isVertical() && eep2->isVertical()) return true;

        //według rosnącego y drugiego końca krawędzi
        if (eep1->getSecondEndpoint()->getY() < eep2->getSecondEndpoint()->getY()) return true;

        if (eep1->getX() < eep2->getX()) return true;

        return false;
    };

    for (int i = 0; i < elements.size() - 1; i++) {
        for (int j = 0; j < elements.size() - 1; j++) {
            if (!comp(elements[j], elements[j + 1])) {
                elements[j].swap(elements[j + 1]);
            }
        }
    }
}

string TempBuffer::toString() const {
    stringstream ss;
    ss << "--- TEMP BUFFER: size: " << elements.size() << "---\n";
    for (auto a : elements) {
        ss << a->toString() << " " << a->getSecondEndpoint()->toString() << endl;
    }
    ss << "---------------------\n";
    return ss.str();
}