#ifndef FILE_IO
#define FILE_IO

#include <string>
#include <vector>
#include "Prism.h"


class FileIO {
private:
	std::string fileName;

	Prism processFileLine(const std::string line);
	std::string generateFileLine(const Prism& prism);
public:
	FileIO();
	FileIO(const std::string fileName);
	void setFileName(const std::string fileName);
	bool saveToFile(const std::vector<Prism>& toSave);
	std::vector<Prism> loadFromFile();
};

#endif
