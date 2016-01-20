/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "../headers/UserInterface.h"
#include <iostream>
#include <c++/fstream>
#include <c++/sstream>


using namespace std;


void UserInterface::getStartInfo() {
    cout << endl << "----- ------ PRISM INTERSECTION ------ -----" << endl;
    cout << "To run the application you have to put some parameters in command line:" << endl;
    cout << "\t-f <filename>   -   input from text file" << endl;
    cout << "\t-r <number of prisms> <max number of vertexes in base> <filename> - random input" << endl;
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
    if (string(argv[argCounter]) == string("-f")) {
        argCounter++;
        if (argCounter < argc) {
            inputFile = string(argv[argCounter++]);
            inputMode = InputMode::FROM_FILE;
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
        if (argCounter + 3 < argc) {
            inputMode = InputMode::RANDOM;
            numberOfPrisms = atoi(argv[argCounter++]);
            maxVertexesInPrismBase = atoi(argv[argCounter++]);
            generatorFile = string(argv[argCounter++]);
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

void UserInterface::showResult(const vector<Prism> &result, const vector<Prism> & result2, double time1, double time2) {
    if(outputMode == OutputMode::SCREEN){
        if(result.size() > 0){
            cout << "----- WEILER ATHERTON -----\n";
            for(Prism p : result){
                cout << p.toString() << endl;
            }

            cout << endl << "input size: " << inputSize;
            cout << endl << "execution time: " << time1;
            cout << endl << "-------------------------------\n";
        }
        if(result2.size() > 0){
            cout << "----- SWEEP METHOD -----\n";
            for(Prism p : result2){
                cout << p.toString() << endl;
            }

            cout << endl << "input size: " << inputSize;
            cout << endl << "execution time: " << time2;
            cout << endl << "-------------------------------\n";
        }
    } else {
        fstream output;
        output.open(outputFile, ios::out);
        if(result.size() > 0){
            fstream rawOutput;
            rawOutput.open("output_wa_raw.txt", ios::out);
            output << "\n----- WEILER ATHERTON -----\n";
            for(Prism p : result){
                output << p.toString() << endl;
                rawOutput << "---" << endl;
                for(auto r : p.getHeightRanges()){
                    rawOutput << r.first << " " << r.second.first << " " << r.second.second << endl;
                }
                for(auto v : p.getVertexList()){
                    rawOutput << v.getX() << " " << v.getY() << " ";
                }
                rawOutput << endl;
            }

            rawOutput.close();
            output << endl << "execution time: " << time1;
            cout << "weiler atherton time: " << time1 << endl;
            output << endl << "-------------------------------\n";
        }
        if(result2.size() > 0){
            fstream rawOutput;
            rawOutput.open("output_sm_raw.txt", ios::out);
            output << "\n----- SWEEP METHOD -----\n";
            for(Prism p : result2){
                output << p.toString() << endl;
                rawOutput << "---" << endl;
                for(auto r : p.getHeightRanges()){
                    rawOutput << r.first << " " << r.second.first << " " << r.second.second << endl;
                }
                for(auto v : p.getVertexList()){
                    rawOutput << v.getX() << " " << v.getY() << " ";
                }
                rawOutput << endl;
            }

            rawOutput.close();
            output << endl << "execution time: " << time2;
            output << endl << "-------------------------------\n";
        }

        output.close();
    }
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
        double x;
        ss >> x;
        double y;
        ss >> y;
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

void UserInterface::setInputSize(int size) {
    this->inputSize = size;
}

void UserInterface::saveInput(const std::vector<Prism> &input) {
    fstream file;
    fstream file2;
    file2.open("generator_raw.txt", ios::out);
    file.open(generatorFile, ios::out);
    for(Prism p : input){
        file << p.toString() << endl;
        file2 << p.getId() << " " << p.getHeightRanges().at(p.getId()).first << " " << p.getHeightRanges().at(p.getId()).second;
        for(Point2D pt : p.getVertexList()){
            file2 << " " << pt.getX() << " " << pt.getY();
        }
        file2 << endl;
    }
    file.close();
    file2.close();
}