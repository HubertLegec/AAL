#include "../headers/UserInterface.h"
#include <iostream>
#include <c++/fstream>
#include <c++/sstream>


using namespace std;


void UserInterface::getStartInfo() {
    cout << endl << "----- ------ PRISM INTERSECTION ------ -----" << endl;
    cout << "To run the application you have to put some parameters in command line:" << endl;
    cout << "\t-f <filename>   -   input from text file" << endl;
    cout << "\t-r <number of prisms> <max number of vertexes in base>  - random input" << endl;
    cout <<
    "\t-o <filename> - you can add this flag to save output in file, otherwise it will be shown on the screen" << endl;
    cout << "----- ------ ****************** ------ -----" << endl << endl;
}

void UserInterface::getIncorrectCommandLineInfo() {
    cout << "Your invocation arguments are incorrect !!!" << endl;
    cout << "To show help run program with '-h' parameter." << endl;
}

bool UserInterface::parseComandLine(int argc, char *argv[]) {
    int argCounter = 1;
    cout << "argv1: " << argv[argCounter] << endl;
    if (string(argv[argCounter]) == string("-f")) {
        argCounter++;
        if (argCounter < argc) {
            inputFile = string(argv[argCounter++]);
            inputMode = InputMode::FROM_FILE;
            cout << "test: " << argc << " - " << argCounter << endl;
            if (argCounter == argc) {
                return true;
            }
        }
        else {
            outputMode = OutputMode::SCREEN;
            return false;
        }
    }
    else if (string(argv[argCounter]) == string("-r")) {
        argCounter++;
        if (argCounter + 2 < argc) {
            inputMode = InputMode::RANDOM;
            numberOfPrisms = atoi(argv[argCounter++]);
            maxVertexesInPrismBase = atoi(argv[argCounter++]);
            if (argCounter == argc) {
                outputMode = OutputMode::SCREEN;
                return true;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    if (string(argv[argCounter++]) == string("-o") && argCounter < argc) {
        outputFile = string(argv[argCounter++]);
        outputMode = OutputMode::TO_FILE;
        if (argCounter == argc) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void UserInterface::toString() const {
    cout << "*** UserInterface ***" << endl;
    cout << "InputMode: " << inputMode << endl;
    cout << "OutputMode: " << outputMode << endl;
    cout << "InputFile: " << inputFile << endl;
    cout << "OutputFile: " << outputFile << endl;
    cout << "NumberOfPrisms: " << numberOfPrisms << endl;
    cout << "MaxVertexesInPrismBase: " << maxVertexesInPrismBase << endl;
}

vector<Prism> UserInterface::getPrismList() {
    fstream input;
    input.open(inputFile, ios::in);
    vector<Prism> result;
    string row;
    if (input.good()) {
        while (getline(input, row))
            result.push_back(generatePrismFromRow(row));
        input.close();
    }
    return result;
}

void UserInterface::showResult(const vector<Prism> &result) {

}

Prism UserInterface::generatePrismFromRow(string row) {
	stringstream ss(row);
    int id;
    ss >> id;
    double bottom;
    double top;
    ss >> bottom;
    ss >> top;
    vector<Point2D> vertices;
    while(!ss.eof()){
        ss.ignore(2, '(');
        double x;
        ss >> x;
        ss.ignore(1, ',');
        double y;
        ss >> y;
        ss.ignore(1, ')');
        vertices.push_back(Point2D(x, y));
    }
    return Prism(id, bottom, top, vertices);
}

bool UserInterface::fromFile() const {
    return inputMode == FROM_FILE;
}

int UserInterface::getNumberOfPrisms() const {
    return numberOfPrisms;
}

int UserInterface::getMaxVertex() const {
    return maxVertexesInPrismBase;
}