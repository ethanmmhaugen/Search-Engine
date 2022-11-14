//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"

#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H


class indexHandler {
private:
    AvlTree<key> info;
    AvlTree<key> peeps;
    AvlTree<key> orgs;

public:
    indexHandler() = default;

    indexHandler(const indexHandler&rhs){
        info = rhs.info;
    };

    indexHandler operator=(const indexHandler&rhs){
        info = rhs.info;
        return *this;
    };

    ~indexHandler(){
        info.makeEmpty();
        peeps.makeEmpty();
        orgs.makeEmpty();
    };

    void insertDoc(key doc){
        info.insert(doc);
    }

    void insertPerson(key person){
        peeps.insert(person);
    }

    void insertOrg(key org){
        orgs.insert(org);
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
