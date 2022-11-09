//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"

#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H


class index {
private:
    AvlTree<key> info;

public:
    index() = default;

    index(const index&rhs){
        info = rhs.info;
    };

    index operator=(const index&rhs){
        info = rhs.info;
        return *this;
    };

    ~index(){
        info.makeEmpty();
    };

    void insert(string word){
        info.insert(word);
    };

    string find(string word){
        if(info.contains(word)){
            //need to pull out word
        }else{
            return "not found";
        }
    };

    void remove(string word){
        info.remove(word);
    }

    bool isEmpty(){
        return info.isEmpty();
    }

    bool contains(string word){
        return info.contains(word);
    };

    void print(){
        info.printTree();
    };

    void prettyPrint(){
        info.prettyPrintTree();
    };
};


#endif //FINALPROJEXAMPLES_INDEX_H
