/*
 * Przecięcia graniastosłupów AAL
 * Hubert Legęć nr albumu: 261461
 */

#include <iostream>

#include "headers/UserInterface.h"

#include "headers/PrismGenerator.h"
#include "headers/Executor.h"

using namespace std;


int main(int argc, char *argv[]) {
    if(argc == 1 || (argc == 2 && string(argv[1]) == string("-h"))){
        UserInterface::getStartInfo();
        return 0;
    }
	UserInterface userInterface;
    cout << endl << "----- ------ PRISM INTERSECTION ------ -----" << endl;
    if(!userInterface.parseComandLine(argc, argv)){
        UserInterface::getIncorrectCommandLineInfo();
        return 0;
    } else {
        vector<Prism> inputList;
        if(userInterface.prismsTest()){
            int quantity = userInterface.getNumberOfPrisms();
            for(int i = 1; i <= userInterface.getSteeps(); i++){
                cout << i << "/" << userInterface.getSteeps() << endl;
                PrismGenerator generator(false, quantity, userInterface.getMaxVertex());
                inputList = generator.generate();
                Executor executor(inputList);
                executor.execute();
                userInterface.addResult(quantity, executor.getWeilerAthertonTime(), executor.getSweepTime());
                quantity += userInterface.getNumberOfPrisms();
            }
            userInterface.showTestResults(0, 2);
            userInterface.showTestResults(1, 2);
        } else if(userInterface.verticesTest()){
            int quantity = userInterface.getMaxVertex();
            for(int i = 1; i <= userInterface.getSteeps(); i++){
                cout << i << "/" << userInterface.getSteeps() << endl;
                PrismGenerator generator(false, userInterface.getNumberOfPrisms(), quantity);
                inputList = generator.generate();
                Executor executor(inputList);
                executor.execute();
                userInterface.addResult(quantity, executor.getWeilerAthertonTime(), executor.getSweepTime());
                quantity += userInterface.getMaxVertex();
            }
            userInterface.showTestResults(0, 1);
            userInterface.showTestResults(1, 1);
        } else {
            if(userInterface.fromFile()){
                inputList = userInterface.getPrismList();
            } else{
                PrismGenerator generator(false, userInterface.getNumberOfPrisms(), userInterface.getMaxVertex());
                inputList = generator.generate();
                userInterface.saveInput(inputList);
            }
            if(inputList.size() == 0){
                cout << "Input list is empty!!!" << endl;
            } else{
                Executor executor(inputList);
                executor.execute();

                userInterface.showResult(executor.getWeilerAthertonOutput(), executor.getSweepOutput(), executor.getWeilerAthertonTime(), executor.getSweepTime());
            }
        }
    }


	return 0;
}


