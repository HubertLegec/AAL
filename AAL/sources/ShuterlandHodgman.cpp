/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include "../headers/ShuterlandHodgman.h"

#include "../headers/Line2D.h"

ShuterlandHodgman::ShuterlandHodgman(const Prism& first, const Prism& second) : firstPrism(first), secondPrism(second) {

}

void ShuterlandHodgman::doIntersection()
{
	Collection<Point2D> clipper = firstPrism.getBase().getVertices();
	Collection<Point2D>* subject = new Collection<Point2D>(secondPrism.getBase().getVertices());
	int len = clipper.getSize();
	for (int i = 0; i < len; i++) {

		int len2 = subject->getSize();
		Collection<Point2D> input(*subject);
		delete subject;
		subject = new  Collection<Point2D>();

		Point2D startA(clipper[i]);
		Point2D endA(clipper[(i+1) % len]);

		for (int j = 0; j < len2; j++) {
			Point2D startB(input[j]);
			Point2D endB(input[(j+1) % len2]);

			Line2D line(startA, endA);

			if (line.getOrientation(endB) == Orientation::CLOCK_WISE) // endB is inside
			{
				if (line.getOrientation(startB) == Orientation::COUNTERCLOCK_WISE) {
					subject->add(line.getIntersectionPoint(Line2D(startB, endB)).second);
				}
				subject->add(endB);
			}
			else if (line.getOrientation(startB) == Orientation::CLOCK_WISE) // startB is inside
			{
				subject->add(line.getIntersectionPoint(Line2D(startB, endB)).second);
			}
		}
	}

	intersectionPart = Prism(1, Polygon(*subject));
	//FIXME
	intersectionPart.addHeightRange(firstPrism.getId(), firstPrism.getBottom(), firstPrism.getTop());
	intersectionPart.addHeightRange(secondPrism.getId(), secondPrism.getBottom(), secondPrism.getTop());
}

Prism ShuterlandHodgman::getIntersection()
{
	return intersectionPart;
}

Prism ShuterlandHodgman::getFirstPart()
{
	return firstPrismPart;
}

Prism ShuterlandHodgman::getSecondPart()
{
	return secondPrismPart;
}

Collection<Prism> ShuterlandHodgman::getAllParts()
{
	Collection<Prism> result;
	result.add(firstPrism);
	result.add(intersectionPart);
	result.add(secondPrism);
	return result;
}