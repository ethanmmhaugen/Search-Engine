//
// Created by ethan on 11/16/2022.
//

#ifndef FINALPROJEXAMPLES_QUERY_H
#define FINALPROJEXAMPLES_QUERY_H


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Porter2/porter2_stemmer.h"

using namespace std;

class query {
private:
    vector<string> queries;
    vector<string> answers;

public:
    query() = default;

    vector<string> getQuery(){
        cout << "Google Search but better... whatchu want?: " << endl;
        string ans;
        getline(cin, ans);
        stringstream s(ans);
        string buff;
        while(!s.eof()) {
            getline(s, buff, ' ');
            //ADD STEMMING
            Porter2Stemmer::stem(buff);
            cout << buff << endl;
            queries.push_back(buff);

        }
        return queries;
    }

    void printAnswers(){
        cout << "We found these files for you: " << endl;
        for(size_t i = 0; i<answers.size(); i++){
            cout << answers[i] << ", ";
            if(i%5 == 0){
                cout << endl;
            }
        }
    }




};
#endif //FINALPROJEXAMPLES_QUERY_H
