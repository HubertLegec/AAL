#ifndef VATTI
#define VATTI

#include <stack>
#include <vector>
#include "Prism.h"
#include "VattiEdge.h"


class Vatti {
private:
	Prism firstPrism;
	Prism secondPrism;
	Collection<Prism> intersectionParts;
	bool valid = false;

	std::stack<double> SBL;
	std::vector<std::pair<std::vector<VattiEdge>, std::vector<VattiEdge>>> LML;
	std::vector<VattiEdge> AEL;

	void updateLMLandSBL(Prism p, bool isClip);
	void addNewBoundPairs(double y);
	void processIntersections(double yb, double yt);
	void processEdgesInAEL(double yb, double yt);

	void buildIL(double dy);
	void processIL();
public:
	Vatti(const Prism& prism1, const Prism& prism2);
	void doVattiClip();
	Collection<Prism> getIntersectionParts();

	
};

#endif
