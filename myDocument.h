//
// Created by ethan on 11/8/2022.
//

#ifndef FINALPROJEXAMPLES_MYDOCUMENT_H
#define FINALPROJEXAMPLES_MYDOCUMENT_H
#include <utility>
#include <vector>
#include <string>

using namespace std;

class myDocument{
private:
    string name;
    string uuid;
    vector<string> people;
    vector<string> orgs;
    vector<string> words;
public:
    myDocument()= default;

    void setName(string x){
        name = move(x);
    }

    string getName(){
        return name;
    }

    void setUUID(string x){
        uuid = move(x);
    }

    string getUUID(){
        return uuid;
    }

    void addPeople(string& x){
        people.push_back(x);
    }


    void addOrgs(string& x){
        orgs.push_back(x);
    }

    void setPeople(const vector<string> &x) {
        myDocument::people = x;
    }

    void setOrgs(const vector<string> &x) {
        myDocument::orgs = x;
    }

    void setWords(const vector<string> &x) {
        myDocument::words = x;
    }

    void addWords(string& names){
        words.push_back(names);
    }

    vector<string> getPeople(){
        return people;
    }

    vector<string> getOrgs(){
        return orgs;
    }

    vector<string> getWords(){
        return words;
    }

    void printWords(){
        for(auto & word : words){
            cout << word << ", ";
        }
        cout << endl;
    }
    void printOrgs(){
        for(auto & org : orgs){
            cout << org << ", ";
        }
        cout << endl;
    }
    void printPeople(){
        for(auto & person : people){
            cout << person << ", ";
        }
        cout << endl;
    }
};


#endif //FINALPROJEXAMPLES_MYDOCUMENT_H
