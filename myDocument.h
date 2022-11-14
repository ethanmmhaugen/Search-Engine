//
// Created by ethan on 11/8/2022.
//

#ifndef FINALPROJEXAMPLES_MYDOCUMENT_H
#define FINALPROJEXAMPLES_MYDOCUMENT_H
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
    myDocument(){

    }
    myDocument(string x){
        name = x;
    }

    void setName(string x){
        name = x;
    }

    string getName(){
        return name;
    }

    void setUUID(string x){
        uuid = x;
    }

    string getUUID(){
        return uuid;
    }

    void addPeople(string names){
        people.push_back(names);
    }


    void addOrgs(string name){
        orgs.push_back(name);
    }

    void setPeople(const vector<string> &people) {
        myDocument::people = people;
    }

    void setOrgs(const vector<string> &orgs) {
        myDocument::orgs = orgs;
    }

    void setWords(const vector<string> &words) {
        myDocument::words = words;
    }

    void addWords(string name){
        words.push_back(name);
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
        for(size_t i = 0; i<words.size(); i++){
            cout << words[i] << ", ";
        }
        cout << endl;
    }
    void printOrgs(){
        for(size_t i = 0; i<orgs.size(); i++){
            cout << orgs[i] << ", ";
        }
        cout << endl;
    }
    void printPeople(){
        for(size_t i = 0; i<people.size(); i++){
            cout << people[i] << ", ";
        }
        cout << endl;
    }
};


#endif //FINALPROJEXAMPLES_MYDOCUMENT_H
