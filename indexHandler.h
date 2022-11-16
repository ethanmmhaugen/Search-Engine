//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"
#include "myDocument.h"

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

    void insertWord(key word){
        info.insert(word);
    }

    void insertPerson(key person){
        peeps.insert(person);
    }

    void insertOrg(key org){
        orgs.insert(org);
    }

    //function for adding instances of a word to index or adding to word index
    void scanDocWords(myDocument doc){
        for(size_t i = 0; i<doc.getWords().size(); ++i){
            if(info.contains(doc.getWords().at(i))){
                info.find(doc.getWords().at(i)).addInst(doc.getUUID());
            }else{
                info.insert(key(doc.getWords().at(i)));
            }
        }
    }

    void scanDocPeople(myDocument doc){
        for(size_t i = 0; i<doc.getPeople().size(); ++i){
            if(info.contains(doc.getPeople().at(i))){
                info.find(doc.getPeople().at(i)).addInst(doc.getUUID());
            }else{
                info.insert(key(doc.getPeople().at(i)));
            }
        }
    }

    void scanDocOrgs(myDocument doc){
        for(size_t i = 0; i<doc.getOrgs().size(); ++i){
            if(info.contains(doc.getOrgs().at(i))){
                info.find(doc.getOrgs().at(i)).addInst(doc.getUUID());
            }else{
                info.insert(key(doc.getOrgs().at(i)));
            }
        }
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
