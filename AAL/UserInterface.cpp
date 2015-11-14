#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;


void UserInterface::getStartInfo(){
	cout << endl << "----- ------ PRISM INTERSECTION ------ -----" << endl;
	cout << "To run the application you have to put some parameters in command line:" << endl;
	cout << "\t-f <filename>   -   input from text file" << endl;
	cout << "\t-r <number of prisms> <max number of vertexes in base> <filename>  - random input (stored in filename) " << endl;
	cout << "\t-o <filename> - you can add this flag to save output in file, otherwise it will be shown on the screen" << endl;
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
			randomInputFile = argv[argCounter++];
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
	cout << "InputFile: " << inputFile.c_str() << endl;
	cout << "OutputFile: " << outputFile.c_str() << endl;
	cout << "RandomInputFile: " << randomInputFile.c_str() << endl;
	cout << "NumberOfPrisms: " << numberOfPrisms << endl;
	cout << "MaxVertexesInPrismBase: " << maxVertexesInPrismBase << endl;
 }

vector<Prism> UserInterface::getPrismList() {
	if (inputMode == InputMode::FROM_FILE) {

	}
	vector<Prism> result;
	return result;
}

void UserInterface::showResult(const vector<Prism>& result) {

}