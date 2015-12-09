#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <vector>
#include <string>
#include "Prism.h"


enum InputMode {
	FROM_FILE = 0,
	RANDOM = 1
};

enum OutputMode {
	TO_FILE = 0,
	SCREEN = 1
};

class UserInterface {
private:

	InputMode inputMode;
	OutputMode outputMode;
	std::string inputFile;
	std::string outputFile;
	std::string randomInputFile;
	int numberOfPrisms;
	int maxVertexesInPrismBase;
public:
	static void getStartInfo();
	static void getIncorrectCommandLineInfo();
	bool parseComandLine(int argc, char *argv[]);
	std::vector<Prism> getPrismList();
	void showResult(const std::vector<Prism>& result);
	void toString() const;
};

#endif
