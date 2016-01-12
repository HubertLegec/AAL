#include <iostream>

#include "headers/UserInterface.h"

#include "headers/PrismGenerator.h"
#include "headers/Executor.h"

using namespace std;



int main(int argc, char *argv[]) {
	UserInterface userInterface;
    UserInterface::getStartInfo();
    if(!userInterface.parseComandLine(argc, argv)){
        UserInterface::getIncorrectCommandLineInfo();
        return 0;
    } else {
        vector<Prism> inputList;
        if(userInterface.fromFile()){
            inputList = userInterface.getPrismList();
        } else{
            PrismGenerator generator(false, userInterface.getNumberOfPrisms(), userInterface.getMaxVertex());
            inputList = generator.generate();
        }
        if(inputList.size() == 0){
            cout << "Input list is empty!!!" << endl;
        } else{
            Executor executor(inputList);
            executor.execute();
            //TODO
        }
    }



	system("PAUSE");
	return 0;
}


