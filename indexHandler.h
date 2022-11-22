//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"
#include "myDocument.h"
#include "DocParser.h"
#include <filesystem>

#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H


class indexHandler {
private:
    AvlTree<key> info;
    AvlTree<key> peeps;
    AvlTree<key> orgs;
    DocParser parser;

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
            if(peeps.contains(doc.getPeople().at(i))){
                peeps.find(doc.getPeople().at(i)).addInst(doc.getUUID());
            }else{
                peeps.insert(key(doc.getPeople().at(i)));
            }
        }
    }

    void scanDocOrgs(myDocument doc){
        for(size_t i = 0; i<doc.getOrgs().size(); ++i){
            if(orgs.contains(doc.getOrgs().at(i))){
                orgs.find(doc.getOrgs().at(i)).addInst(doc.getUUID());
            }else{
                orgs.insert(key(doc.getOrgs().at(i)));
            }
        }
    }

    void populate(string path){
        for(const auto& entry: filesystem::recursive_directory_iterator(path)){
            if(entry.is_regular_file() && entry.path().extension().string() == ".json"){
                myDocument doc = parser.readJsonFile(entry.path().string());
                //Populate people index
                scanDocOrgs(doc);
                scanDocPeople(doc);
                scanDocWords(doc);
            }
        }
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
