/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <deque>
#include <memory>
#include "../headers/Executor.h"
#include "../headers/Timer.h"
#include "../headers/WeilerAtherton.h"
#include "../headers/SweepMethod.h"

using namespace std;




Executor::Executor(std::vector<Prism> input) : input(input), weilerAtherotonTime(0), sweepTime(0) {

}

void Executor::execute() {
    //executeWeilerAtherton();
    executeSweep();
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

void Executor::executeWeilerAtherton() {

    Timer t;

    for(int i = 0; i < input.size() - 1; i++){
        for(int j = i+1; j < input.size(); j++){
            cout << "WAILER-ATHERTON przetwarzam pare: " << i << " " << j << endl;
            WeilerAtherton wa(input[i], input[j]);
            wa.doWeilerAtherton();
            for(Prism p : wa.getIntersectionParts()){
                wailerAthertonOutput.push_back(p);
            }
        }
    }

    weilerAtherotonTime = t.elapsed();
}

void Executor::executeSweep() {
    Timer t;
    for(int i = 0; i < input.size() - 1; i++){
        for(int j = i+1; j < input.size(); j++){
            cout << "SWEEP przetwarzam pare: " << i << " " << j << endl;
            SweepMethod sm(input[i], input[j]);
            sm.doClipping();
            for(Prism p : sm.getIntersectionParts()){
                sweepOutput.push_back(p);
            }
        }
    }
    sweepTime = t.elapsed();
}