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
    vector<string> orgQueries;
    vector<string> peepQueries;
    vector<string> wordQueries;
    vector<string> skipWords;
    vector<string> answers;
    int state;
    int negState;


public:
    query() = default;

    void getQuery(){
        state = 0;
        negState = 0;
        clearQuery();
        cout << "Google Search but better... whatchu want?: " << endl;
        string ans;
        getline(cin, ans);
        stringstream s(ans);
        string buff;
        while(!s.eof()) {
            negState = 0;
            getline(s, buff, ' ');

            if(buff.find('-') != string::npos){
                negState = 1;
                buff = buff.substr(1);
            }
            if(buff.find("ORG:")!= string::npos){
                state = 1;
                string tmp;
                buff = buff.substr(4);
                getline(s,tmp,'\n');
                buff += tmp;
            }
            if(buff.find("PERSON:")!= string::npos){
                state = 2;
                buff = buff.substr(7);
            }

            //ADD STEMMING
            Porter2Stemmer::stem(buff);
            /*string delimit = "!@#$%^&*()+=/.,'\r''\n'";
            for(size_t i =0; i<buff.size(); ++i){
                for(size_t j=0; i<delimit.size();++i){
                    if(buff.at(i) == delimit.at(j)){
                        buff.erase(buff.at(i));
                        cout << "QUERY SPEC CHAR STEMMING ACTUALLY GETS USED" << endl;
                    }
                }
            }*/
            if(state == 0 && negState == 0) {
                wordQueries.push_back(buff);
            }
            else if(state == 0 && negState == 1){
                skipWords.push_back(buff);
            }
            else if(state == 1){
                if(negState == 1){
                    orgQueries.push_back("negative");
                }
                orgQueries.push_back(buff);
            }
            else if(state == 2){
                if(negState == 1){
                    peepQueries.push_back("negative");
                }
                peepQueries.push_back(buff);
            }
        }

    }

    void clearQuery(){
        orgQueries.clear();
        peepQueries.clear();
        wordQueries.clear();
    }

    void clearAnswers(){
        answers.clear();
    }

    void storeAnswers(vector<string> input){
        clearAnswers();
        for(auto i:input){
            answers.push_back(i);
        }
    }

    void printAnswers(){
        cout << "We found these files for you: " << endl;
        for(size_t i = 0; i<answers.size(); i++){
            cout << answers[i] << endl;
        }
    }




};
#endif //FINALPROJEXAMPLES_QUERY_H
