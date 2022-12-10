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
    int pageNum;


public:
    query(){
        pageNum = 0;
        state = 0;
        negState = 0;
    };

    void getQuery(){
        state = 0;
        negState = 0;
        string ans;
        clearQuery();
        cout << "Google Search but better... whatchu want?: " << endl;
        cin.ignore();
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
            buff = lowerCase(buff);
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

    vector<string> getOrgQueries(){
        return orgQueries;
    }

    vector<string> getPeepQueries(){
        return peepQueries;
    }

    vector<string> getWordQueries(){
        return wordQueries;
    }

    vector<string> getSkipAnswers(){
        return skipWords;
    }

    void clearQuery(){
        orgQueries.clear();
        peepQueries.clear();
        wordQueries.clear();
        skipWords.clear();
    }

    void clearAnswers(){
        answers.clear();
    }

    void storeAnswers(vector<string>& input){
        clearAnswers();
        for(const auto& i:input){
            answers.push_back(i);
        }
    }



    void nextPage(){
        if((pageNum+1)*15 < answers.size()) {
            pageNum += 1;
        }
        else{
            cout << "Sorry, out of results" << endl;
            cout << "\n\n\n";
        }
    }

    void prevPage(){
        if(pageNum < 1){
            cout << "Can't go back from page 1... nice try shockley" << endl;
            cout << "\n\n\n";
        }
        else {
            pageNum -= 1;
        }
    }




    string lowerCase(string data){
        string tmp;
        for (char &i: data) {
            if(i > 47 && i<58){
                tmp += i;
            }
            else if(i>96 && i<123){
                tmp += i;
            }
            else if (i>64 && i<91){
                tmp += (i+32);
            }
        }
        return tmp;
    }

    string orgLowerCase(string data){
        string tmp;
        for (char &i: data) {
            if(i == 32){
                tmp+= i;
            }
            else if(i > 47 && i<58){
                tmp += i;
            }
            else if(i>96 && i<123){
                tmp += i;
            }
            else if (i>64 && i<91){
                tmp += (i+32);
            }
        }
        return tmp;

    }

    void printAnswers(unordered_map<string, string>& hash){
        vector<string> results = UuidtoTitles(answers, hash);
        if(results.size()<1){
            cout << "No files found... try again!" << endl;
            return;
        }
        else {
            cout << "We found these files for you: " << endl;
            for (size_t i = pageNum * 15, j = pageNum * 15; i < min(j + 15, results.size()); i++) {
                cout << i+1 << ". " << results[i] << endl;
            }
        }
    }

    void resultsMenu(unordered_map<string, string>& hashUrls, unordered_map<string, string>& hash){
        pageNum = 0;
        char input;
        while(true){
            printAnswers(hash);
            cout << "|Page " << pageNum+1 << "                                     |" << endl;
            cout << "|                                           |" << endl;
            cout << "|                                           |" << endl;
            cout << "|R - Return the URL of a result             |" << endl;
            cout << "|N - next page of results                   |" << endl;
            cout << "|P - previous page of results               |" << endl;
            cout << "|E - exit the query and go back to main menu|" << endl;
            cout << "|Select an option:                          |" << endl;

            cin >> input;
            if(input == 'N'){
                nextPage();
                continue;
            }
            else if(input == 'P'){
                prevPage();
                continue;
            }
            else if(input == 'R'){
                int num;
                cout << "Enter the # result you would like the url for" << endl;
                cin >> num;
                cout << hashUrls[answers[num-1]] << endl;
                continue;
            }
            else if(input == 'E'){
                break;
            }
        }
    }

    vector<string> UuidtoTitles(vector<string>& uuidst, unordered_map<string, string>& hash){
        vector<string> answers;
        answers.reserve(uuidst.size());
        for(auto & uuid : uuidst){
            answers.push_back(hash[uuid]);
        }
        return answers;
    }
};
#endif //FINALPROJEXAMPLES_QUERY_H
