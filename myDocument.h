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

    void addPeople(string names){
        people.push_back(names);
    }

    void addPeople(string names[]){
        for(size_t i = 0; i<names->size(); i++){
            people.push_back(names[i]);
        }
    }

    void addOrgs(string name){
        orgs.push_back(name);
    }

    void addOrgs(string names[]){
        for(size_t i = 0; i<names->size(); i++){
            orgs.push_back(names[i]);
        }
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
};


#endif //FINALPROJEXAMPLES_MYDOCUMENT_H
