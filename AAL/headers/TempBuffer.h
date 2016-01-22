/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef RING_TEMPBUFFER_H
#define RING_TEMPBUFFER_H

#include <vector>
#include <memory>
#include "EdgeEndpoint.h"

class TempBuffer {
private:
    std::vector<std::shared_ptr<EdgeEndpoint>> elements;
public:
    TempBuffer();

    std::shared_ptr<EdgeEndpoint> insert(std::shared_ptr<EdgeEndpoint> endpoint);

    std::shared_ptr<EdgeEndpoint> prev(std::shared_ptr<EdgeEndpoint> endpoint);

    std::shared_ptr<EdgeEndpoint> next(std::shared_ptr<EdgeEndpoint> endpoint);

    void erase(std::shared_ptr<EdgeEndpoint> endpoint);

    void sort(float x);

    std::string toString() const;
};

struct TempBufferComparator {
    float x;

    TempBufferComparator(float x) {
        this->x = x;
    }

    bool operator()(const std::shared_ptr<EdgeEndpoint> &eep1, const std::shared_ptr<EdgeEndpoint> &eep2) {
        if (eep1->getIntersectionY(x) < eep2->getIntersectionY(x)) return true;

        if (eep1->getIntersectionY(x) > eep2->getIntersectionY(x)) return false;

        //według rosnącego y drugiego końca krawędzi
        if (eep1->getSecondEndpoint()->getY() < eep2->getSecondEndpoint()->getY()) return true;

        return false;
    }
};

#endif //RING_TEMPBUFFER_H
