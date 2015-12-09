#include "PrismGenerator.h"

PrismGenerator::PrismGenerator()
{
	onlyConvex = false;
	howMany = 100;
	maxVertexInBase = 20;
}

PrismGenerator::PrismGenerator(bool onlyConvex, int howMany, int maxVertexInBase) : onlyConvex(onlyConvex), howMany(howMany), maxVertexInBase(maxVertexInBase)
{
}

void PrismGenerator::setOnlyConvex(bool setValue)
{
	this->onlyConvex = setValue;
}

void PrismGenerator::setHowMany(int howMany)
{
	this->howMany = howMany;
}

void PrismGenerator::setMaxVertexNumberInBase(int number)
{
	this->maxVertexInBase = number;
}

std::vector<Prism> PrismGenerator::generate() const
{
	//TODO
	return std::vector<Prism>();
}

Prism PrismGenerator::generateSingle() const
{
	//TODO
	return Prism();
}
