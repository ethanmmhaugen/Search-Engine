#include <iostream>
#include <string>
#include <fstream>
#include "indexHandler.h"


#ifndef FINALPROJEXAMPLES_USERINTERFACE_H
#define FINALPROJEXAMPLES_USERINTERFACE_H

#endif //FINALPROJEXAMPLES_USERINTERFACE_H

using namespace std;

class supersearch{
private:
public:
    static void superSearch(){
        char input;
        string name;
        indexHandler handler;

        while(true){
            cout << "|----WELCOME TO SUPERSEARCH: BULLETPROOF----|" << endl << "|                                           |" << endl << "|                                           |" << endl << "|                                           |" << endl << "|                                           |"<< endl;
            cout << "|Select an option below:                    |" << endl;
            cout << "|I - Upload documents to indices            |" << endl;
            cout << "|W - Write indices to persistency file      |" << endl;
            cout << "|Q - Query                                  |" << endl;
            cout << "|R - Recreate indices from persistency file |" << endl;
            cout << "|C - Clear indices                          |" << endl;
            cout << "|E - Exit SUPERSEARCH                       |" << endl;
            cout << "|___________________________________________|" << endl;
            cout << "Please enter a character and press enter: "    << endl;

            cin >> input;
            toupper(input);
            if(input == 'I'){
                cout << "Please enter directory name: " << endl;
                cin >> name;
                handler.populate(name);
                cout << "Index created and populated" << endl;
                continue;
            }else if(input == 'W'){
                //FIX FROM BEING ONLY STORING ORGS
                handler.storeTree(handler.getWords(), "wordTree.txt");
                handler.storeTree(handler.getPeeps(), "peopleTree.txt");
                handler.storeTree(handler.getOrgs(), "orgTree.txt");
                handler.storeMaps(handler.getHashMap(), handler.getCountMap(), handler.getUUIDs(), "titleMap.txt", "countMap.txt");
                continue;
            }else if(input == 'Q'){
                handler.search();
                continue;
            }else if(input == 'R'){
                handler.wordreloadTree("wordTree.txt");
                handler.peepreloadTree("peopleTree.txt");
                handler.orgreloadTree("orgTree.txt");
                handler.reloadMaps("titleMap.txt", "countMap.txt");
                continue;
            }else if(input == 'C'){
                handler.clear();
                continue;
            }else if(input == 'E'){
                break;
            }else{
                cout << "Invalid option! Please enter another letter and try again." << endl;
                cout << "Please enter a character and press enter: " << endl;
                cin >> input;
                continue;
            }
        }
        cout << "Thank you for using SUPERSEARCH!" << endl;
    }
};