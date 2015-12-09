#ifndef SHUTERLAND_HODGMAN
#define SHUTERLAND_HODGMAN

#include "Prism.h"
#include "Collection.hpp"

class ShuterlandHodgman {
private:
	Prism firstPrism;
	Prism secondPrism;
	bool valid;
	Prism firstPrismPart;
	Prism intersectionPart;
	Prism secondPrismPart;
public:
	ShuterlandHodgman(const Prism& first, const Prism& second);
	void doIntersection();
	Prism getIntersection();
	Prism getFirstPart();
	Prism getSecondPart();
	Collection<Prism> getAllParts();

};

#endif
