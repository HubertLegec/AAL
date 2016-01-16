//
// Created by hubert.legec on 2016-01-16.
//

#ifndef RING_TEMPBUFFER_H
#define RING_TEMPBUFFER_H

#include <set>
#include <memory>
#include "EdgeEndpoint.h"

class TempBuffer{
private:
    std::set<std::shared_ptr<EdgeEndpoint>, EdgeEndpointComparator> elements;
public:
    TempBuffer();
    std::shared_ptr<EdgeEndpoint> insert(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> find(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> prev(std::shared_ptr<EdgeEndpoint> endpoint);
    std::shared_ptr<EdgeEndpoint> next(std::shared_ptr<EdgeEndpoint> endpoint);
    void erase(std::shared_ptr<EdgeEndpoint> endpoint);
};

#endif //RING_TEMPBUFFER_H
