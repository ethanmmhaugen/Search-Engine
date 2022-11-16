//
// Created by ethan on 11/16/2022.
//

#ifndef FINALPROJEXAMPLES_QUERY_H
#define FINALPROJEXAMPLES_QUERY_H


#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class query {
private:
    vector<string> queries;
    vector<string> answers;

public:
    query() = default;

    string getQuery(){
        cout << "Google Search but better... whatchu want?: " << endl;
        string ans;
        cin >> ans;
        stringstream s(ans);
        string buff;
        while(!s.eof()) {
            getline(s, buff, ' ');
            //ADD STEMMING
            queries.push_back(buff);
        }


    }




};
#endif //FINALPROJEXAMPLES_QUERY_H
