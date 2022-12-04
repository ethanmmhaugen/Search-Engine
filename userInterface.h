#include <iostream>
#include <string>
#include <fstream>
#include "indexHandler.h"


#ifndef FINALPROJEXAMPLES_USERINTERFACE_H
#define FINALPROJEXAMPLES_USERINTERFACE_H

#endif //FINALPROJEXAMPLES_USERINTERFACE_H

using namespace std;

class supersearch{

    void superSearch(){
        char input;

        cout << "---WELCOME TO SUPERSEARCH: BULLETPROOF---" << endl << "|                                         |" << endl << "|                                         |" << endl << "|                                         |" << endl << "|                                         |"<< endl;
        cout << "|Select an option below:                  |" << endl;
        cout << "|I - Create a new index                   |"  << endl;
        cout << "|W - Write index to file                  |" << endl;
        cout << "|Q - Query an index                       |" << endl;
        cout << "|R - Read in index from file              |" << endl;
        cout << "|E - Exit SUPERSEARCH                     |" << endl;
        cout << "|_________________________________________|";
        cout << "Please enter a character and press enter: ";

        cin >> input;
        toupper(input);

        string name;
        indexHandler handler;

        while(input != '.'){
            if(input == 'I'){
                cout << "Please enter directory name: ";
                cin >> name;
                handler.populate(name);

                cout << "Index created and populated";

                continue;
            }else if(input == 'W'){
                cout << "Please choose a name for your saved index: ";
                cin >> name;
                //FIX FROM BEING ONLY STORING ORGS
                handler.storeTree(handler.getOrgs(), name);
                cout << "Index successfully stored in " << name << endl;
                continue;
            }else if(input == 'Q'){

                continue;
            }else if(input == 'R'){
                continue;
            }else if(input == 'E'){
                input = '.';
                continue;
            }else{
                cout << "Invalid option! Please enter another letter and try again." << endl;
                cout << "Please enter a character and press enter: " << endl;
                cin >> input;
            }
        }
        cout << "Thank you for using SUPERSEARCH!" << endl;

    }



};