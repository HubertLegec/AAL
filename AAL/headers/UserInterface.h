/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <vector>
#include <memory>
#include <string>
#include "Prism.h"


enum InputMode {
    FROM_FILE = 0,
    RANDOM = 1,
    TEST_PRISMS = 2,
    TEST_VERTICES = 3
};

enum OutputMode {
    TO_FILE = 0,
    SCREEN = 1
};

class UserInterface {
private:
    std::vector<std::shared_ptr<long>> testResults;

    InputMode inputMode;
    OutputMode outputMode;
    std::string inputFile;
    std::string outputFile;
    std::string generatorFile;
    int numberOfPrisms;
    int maxVertexesInPrismBase;
    int inputSize;
    int steeps;

    Prism generatePrismFromRow(std::string row);

public:
    static void getStartInfo();

    static void getIncorrectCommandLineInfo();

    bool parseComandLine(int argc, char *argv[]);

    std::vector<Prism> getPrismList();

    void showResult(const std::vector<Prism> &result, const std::vector<Prism> &result2, double time1, double time2);

    void toString() const;

    void setInputSize(int size);

    bool fromFile() const;

    bool verticesTest() const;

    bool prismsTest() const;

    void saveInput(const std::vector<Prism> &input);

    int getNumberOfPrisms() const;

    int getMaxVertex() const;

    void addResult(long size, long waTime, long smTime);

    void showTestResults(int algorithm, int complexity);

    int getSteeps() const;
};

#endif
