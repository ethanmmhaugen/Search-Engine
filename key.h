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

    key operator=(const key&rhs){
        instances = rhs.instances;
        word = rhs.word;
        return *this;
    };

    void printAllInstances(){
        cout << word << " found in: ";
        for (int i = 0; i < instances.size(); ++i) {
            cout << instances.at(i) << ", ";
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

};


#endif //FINALPROJEXAMPLES_KEY_H
