#include "Vatti.h"


void Vatti::updateLMLandSBL(Prism p, bool isClip)
{
}

void Vatti::addNewBoundPairs(double y)
{
}

void Vatti::processIntersections(double yb, double yt)
{
}

void Vatti::processEdgesInAEL(double yb, double yt)
{
}

void Vatti::buildIL(double dy)
{
}

void Vatti::processIL()
{
}

Vatti::Vatti(const Prism & prism1, const Prism & prism2) : firstPrism(prism1), secondPrism(prism2)
{

}

void Vatti::doVattiClip()
{
	double yb, yt;

	updateLMLandSBL(firstPrism, false);
	updateLMLandSBL(secondPrism, true);

	//utworz pusta liste AEL, PL == intersectionParts

	yb = SBL.top();
	SBL.pop();

	do {
		addNewBoundPairs(yb);

		yt = SBL.top();
		SBL.pop();
		processIntersections(yb, yt);
		processEdgesInAEL(yb, yt);
		yb = yt;
	} while (SBL.size() > 0);
}

Collection<Prism> Vatti::getIntersectionParts()
{
	if (!valid) {
		doVattiClip();
	}
	return intersectionParts;
}
