//
// Created by hubert.legec on 2016-01-16.
//

#include "../headers/TempBuffer.h"

using namespace std;

TempBuffer::TempBuffer() { }

void TempBuffer::erase(shared_ptr<EdgeEndpoint> endpoint) {
    elements.erase(endpoint);
}

shared_ptr<EdgeEndpoint> TempBuffer::insert(shared_ptr<EdgeEndpoint> endpoint) {
    elements.insert(endpoint);
    return 0;
}

shared_ptr<EdgeEndpoint> TempBuffer::find(shared_ptr<EdgeEndpoint> endpoint) {
    return *elements.find(endpoint);
}

shared_ptr<EdgeEndpoint> TempBuffer::prev(shared_ptr<EdgeEndpoint> endpoint) {
    auto el = elements.find(endpoint);
    el--;
    return *el;
}

std::shared_ptr<EdgeEndpoint> TempBuffer::next(shared_ptr<EdgeEndpoint> endpoint) {
    auto el = elements.find(endpoint);
    el++;
    return *el;
}