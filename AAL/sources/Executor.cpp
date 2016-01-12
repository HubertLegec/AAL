//
// Created by hubert.legec on 2016-01-13.
//

#include "../headers/Executor.h"

Executor::Executor(std::vector<Prism> input) : input(input), weilerAtherotonTime(0), sweepTime(0) {

}

void Executor::execute() {
    //TODO
}

long Executor::getSweepTime() const {
    return sweepTime;
}

long Executor::getWeilerAthertonTime() const {
    return weilerAtherotonTime;
}

std::vector<Prism> Executor::getSweepOutput() const {
    return sweepOutput;
}

std::vector<Prism> Executor::getWeilerAthertonOutput() const {
    return wailerAthertonOutput;
}