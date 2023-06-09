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
        chrono::duration<double> timeTaken;
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
            cout << "|T - Print time from last search            |" << endl;
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
                handler.storeMaps(handler.getHashMap(), handler.getUUIDs(), "titleMap.txt");
                handler.storeMaps(handler.getCountMap(), handler.getUUIDs(), "countMap.txt");
                handler.storeMaps(handler.getUrlMap(), handler.getUUIDs(), "urlMap.txt");
                continue;
            }else if(input == 'Q'){
                chrono::duration<double> time = handler.search();
                timeTaken = time;
                continue;
            }else if(input == 'R'){
                handler.wordreloadTree("wordTree.txt");
                cout << "word tree complete" << endl;
                handler.peepreloadTree("peopleTree.txt");
                cout << "person tree complete" << endl;
                handler.orgreloadTree("orgTree.txt");
                cout << "organization tree complete" << endl;
                handler.reloadMaps("titleMap.txt", "countMap.txt", "urlMap.txt");
                continue;
            }else if(input == 'C') {
                handler.clear();
                continue;
            }
            else if(input == 'T'){
                cout << "The time taken for last query was " << timeTaken.count() << "seconds!! "<< endl;
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