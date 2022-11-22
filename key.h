//
// Created by Alex Gonzalez on 11/8/22.
//
#include <string>
#include <vector>
#include <iostream>


#ifndef FINALPROJEXAMPLES_KEY_H
#define FINALPROJEXAMPLES_KEY_H

using namespace std;

class key {
private:
    string word;
    vector<string> instances;

public:
    key() = default;

    key(string name){
        word = name;
    };

    key(const key&rhs){
        word = rhs.word;
        instances =  rhs.instances;
    };

    key& operator=(const key& rhs){
        word = rhs.word;
        return *this;
    };

    bool operator<(const key& rhs) const{
        return this->word < rhs.word;
    };

    bool operator>(const key& rhs) const{
        return this->word > rhs.word;
    };

    void printAllInstances(){
        cout << word << " found in: ";
        for (auto & instance : instances) {
            cout << instance << ", ";
        }
    };
    string getName(){
        return word;
    };
    void setName(string name){
        word = name;
    };
    void addInst(string name){
        instances.push_back(name);
    };

    friend ostream& operator << (ostream& out, const key x){
        out << x.word;
        return out;
    }

};


#endif //FINALPROJEXAMPLES_KEY_H
