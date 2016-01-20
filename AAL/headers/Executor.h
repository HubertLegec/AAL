/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef RING_EXECUTOR_H
#define RING_EXECUTOR_H


#include "Prism.h"

class Executor {
private:
    std::vector<Prism> input;
    std::vector<Prism> wailerAthertonOutput;
    std::vector<Prism> sweepOutput;
    long weilerAtherotonTime;
    long sweepTime;
    void executeWeilerAtherton();
    void executeSweep();
public:
    Executor(std::vector<Prism> input);
    void execute();
    long getWeilerAthertonTime() const;
    long getSweepTime() const;
    std::vector<Prism> getWeilerAthertonOutput() const;
    std::vector<Prism> getSweepOutput() const;
};


#endif //RING_EXECUTOR_H
