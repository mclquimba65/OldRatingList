#include <iostream>
#include <string>
#include "Node.h"
#include "GamesList.h"
#include "utilities.h"

using namespace std;


bool switchStatement(GamesList<int>&);


int main() {
    GamesList<int> list;
    bool endProgram = false;

    list.inputFromFile();

    while (!endProgram) {
        endProgram = switchStatement(list);
    }
}



bool switchStatement(GamesList<int>& list) {
    
    ios defaultStream(NULL);
    defaultStream.copyfmt(cout);

    string chooseOptionString = "";
    int chooseOption = 0;
    bool error = false;
    bool end = false;

    displayMenu();

    cout << "[ Enter Option ]" << endl;
    cout << "-> ";
    getline(cin, chooseOptionString);

    try {
        verifyInteger(chooseOptionString);
        chooseOption = stoi(chooseOptionString);
        menuInputValidation(chooseOption);
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
        error = true;
    }

    if (!error) {

        switch (chooseOption) {
        case 1:

            previewList(list);
            break;

        case 2:

            addGame(list);
            break;

        case 3:

            removeGame(list);
            break;

        case 4:

            modifyGame(list);
            break;

        default:

            int returnValue = 0;
            returnValue = saveList(list);
            
            if (returnValue == 1) {
                end = true;
            }

            break;

        }
    }

    return end;
}