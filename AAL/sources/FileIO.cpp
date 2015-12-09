#include "FileIO.h"
#include <sstream>
#include <fstream>

using namespace std;

FileIO::FileIO() {
	fileName = "";
}

FileIO::FileIO(const string fileName) {
	this->fileName = fileName;
}

void FileIO::setFileName(const string fileName) {
	this->fileName = fileName;
}

bool FileIO::saveToFile(const vector<Prism>& toSave) {
	fstream file(fileName, ios::out);
	
	for (Prism p : toSave) {
		string line = generateFileLine(p);
		file << line << endl;
	}

	file.close();
	return true;
}
/*
vector<Prism> FileIO::loadFromFile() {
	vector<Prism> result;
	fstream file(fileName, ios::in);
	while (!file.eof()) {
		string line;
		getline(file, line);
		result.push_back( processFileLine(line) );
	}
	file.close();
	return result;
}


Prism FileIO::processFileLine(const string line) {
	Prism result;
	stringstream ss;
	ss.str(line);

	char ch;
	double bottomZ;
	double upperZ;
	ss >> bottomZ;
	ss >> ch;
	ss >> upperZ;
	ss >> ch;
	result.setBottom(bottomZ);
	result.setTop(upperZ);

	while (!ss.eof()) {
		double x, y;
		ss >> x;
		ss >> ch;
		ss >> y;
		ss >> ch;
//		result.addVertex(Point2D(x, y));
	}

	return result;
}*/

string FileIO::generateFileLine(const Prism & prism) {
	stringstream ss;
	ss << prism.getBottom();
	ss << ",";
	ss << prism.getTop();
	ss << ";";

	for (Point2D v : prism.getVertexList().getItems()) {
		ss << " ";
		ss << v.getX();
		ss << ",";
		ss << v.getY();
		ss << ";";
	}

	return ss.str();
}