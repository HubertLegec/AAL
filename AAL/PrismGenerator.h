#ifndef PRISM_GENERATOR
#define PRISM_GENERATOR

#include "Prism.h"

class PrismGenerator {
private:
	bool onlyConvex;
	int howMany;
	int maxVertexInBase;

public:
	PrismGenerator();
	PrismGenerator(bool onlyConvex, int howMany, int maxVertexInBase);
	void setOnlyConvex(bool setValue);
	void setHowMany(int howMany);
	void setMaxVertexNumberInBase(int number);
	std::vector<Prism> generate() const;
	Prism generateSingle() const;
};

#endif