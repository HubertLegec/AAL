#include <iostream>

#include "../headers/UserInterface.h"

#include "../headers/Polygon.h"
#include "../headers/WeilerAtherton.h"
#include "../headers/ShuterlandHodgman.h"

using namespace std;



int main(int argc, char *argv[]) {
	UserInterface userInterface;
	Polygon pol1;
	pol1.add(Point2D(1, 1));
	pol1.add(Point2D(5, 3));
	pol1.add(Point2D(1, 3));
	pol1.add(Point2D(1, 8));
	pol1.add(Point2D(6, 8));
	pol1.add(Point2D(6, 1));
	Polygon pol2;
	pol2.add(Point2D(4, -1));
	pol2.add(Point2D(4, 4));
	pol2.add(Point2D(9, 4));
	pol2.add(Point2D(9, -1));

	Polygon pol3;
	pol3.add(Point2D(7,1));
	pol3.add(Point2D(1,11));
	pol3.add(Point2D(9,11));
	pol3.add(Point2D(8,9));
	pol3.add(Point2D(4,8));
	pol3.add(Point2D(9,7));
	Polygon pol4;
	pol4.add(Point2D(7,12));
	pol4.add(Point2D(11,12));
	pol4.add(Point2D(11,5));
	pol4.add(Point2D(7,5));

	Polygon pol5;
	pol5.add(Point2D(2, 1));
	pol5.add(Point2D(2, 7));
	pol5.add(Point2D(7, 7));
	pol5.add(Point2D(7, 1));

	Polygon pol6;
	pol6.add(Point2D(11, 3));
	pol6.add(Point2D(11, 0));
	pol6.add(Point2D(5, 0));
	pol6.add(Point2D(5, 3));

	//cout << "argc: " << argc << endl;

	/*if (argc < 2 || argv[1] == "-h") {
		UserInterface::getStartInfo();
	}
	else {
		bool commandLineVeryfication = userInterface.parseComandLine(argc, argv);

		if (commandLineVeryfication == false) {
			UserInterface::getIncorrectCommandLineInfo();
			return -1;
		}
		else {
			userInterface.toString();
		}
	}*/

	/*WeilerAthertonClipping clipping;
	clipping.setCandidate(pol1);
	clipping.setClippingArea(pol2);

	
	Collection<Polygon> res = clipping.getClippedPolygon();

	for (int i = 0; i < res.getSize(); ++i) {
		cout << "-----------------------------------" << endl;
		cout << res[i].toString() << endl;
	}*/

	WeilerAtherton w1(Prism(0, 1, 2, pol1), Prism(1, 2, 3, pol2));
	w1.doWeilerAtherton();
	for (Prism p : w1.getIntersectionParts()) {
		std::cout << p.toString() << endl;
	}


	std::cout << std::endl << "TEST2:" << std::endl;

	WeilerAtherton w2(Prism(2, 1, 2, pol3), Prism(3, 2, 3, pol4));
	w2.doWeilerAtherton();
	for (Prism p : w2.getIntersectionParts()) {
		std::cout << p.toString() << endl;
	}

	std::cout << std::endl << "TEST3:" << std::endl;
	ShuterlandHodgman s1(Prism(4, 4, 5, pol6), Prism(3, 3, 4, pol5));
	s1.doIntersection();

	std::cout << s1.getIntersection().toString() << std::endl;

	system("PAUSE");
	return 0;
}


