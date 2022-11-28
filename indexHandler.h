//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"
#include "myDocument.h"
#include "DocParser.h"
#include <filesystem>
#include <ostream>
#include "Porter2/porter2_stemmer.h"

#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H


class indexHandler {
private:
    AvlTree<key> info;
    AvlTree<key> peeps;
    AvlTree<key> orgs;
    DocParser parser;
    query google;

    key storeinfoTree(string filename){


    }

public:
    indexHandler() = default;

    indexHandler(const indexHandler&rhs){
        info = rhs.info;
        peeps = rhs.peeps;
        orgs = rhs.orgs;
        parser = rhs.parser;
    };

    indexHandler operator=(const indexHandler&rhs){
        info = rhs.info;
        peeps = rhs.peeps;
        orgs = rhs.orgs;
        parser = rhs.parser;
        return *this;
    };

    ~indexHandler(){
        clear();
    };

    void clear(){
        info.makeEmpty();
        peeps.makeEmpty();
        orgs.makeEmpty();
    }

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
            Porter2Stemmer::stem(doc.getWords().at(i));
            if(!info.contains(doc.getWords().at(i))) {
                info.insert(key(doc.getWords().at(i)));
            }
            info.find(key(doc.getWords().at(i))).addInst(doc.getUUID());
        }
    }

    void scanDocPeople(myDocument doc){
        for(size_t i = 0; i<doc.getPeople().size(); ++i){
            Porter2Stemmer::stem(doc.getPeople().at(i));
            if(!peeps.contains(doc.getPeople().at(i))) {
                peeps.insert(key(doc.getPeople().at(i)));
            }
            peeps.find(key(doc.getPeople().at(i))).addInst(doc.getUUID());
        }
    }

    void scanDocOrgs(myDocument doc){
        for(size_t i = 0; i<doc.getOrgs().size(); ++i){
            Porter2Stemmer::stem(doc.getOrgs().at(i));
            if(!orgs.contains(doc.getOrgs().at(i))) {
                orgs.insert(key(doc.getOrgs().at(i)));
            }
            orgs.find(key(doc.getOrgs().at(i))).addInst(doc.getUUID());
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
                //INSERT NAME UUID PAIR TO HASHMAP HERE
            }
        }
    }
/*
    void storeTree(AvlTree<key>& tree, string& filename){
        ifstream file;
        tree.saveToFile(file, filename);
    }
*/
    void reloadTree(const string& filename){
        orgs.makeEmpty();
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error, file not found" << endl;
        }
        string buff;
        while(!file.eof()){
            getline(file, buff);
            stringstream s(buff);
            getline(s, buff, ' ');
            key insert = key(buff);
            while(!s.eof()){
                getline(s, buff, ' ');
                insert.addInst(buff);
            }
            orgs.balancedInsert(insert);
        }

    }

    void search(){
        vector<string> search = google.getQuery();
        int andor = 0;
        for(auto & i : search){
            if(i == "or"){
                andor = 1;
            }
        }
        vector<string> results;
        vector<string> wordResults;
        //search through orgs index
        if(search[0] == "org"){
            for(unsigned i = 1; i<search.size(); i++){
                wordResults = orgs.find(search[i]).getInstances();
                for(auto & wordResult : wordResults){
                    results.push_back(wordResult);
                }
            }
        }
        //search through peeps index
        else if(search[0] == "person"){
            for(unsigned i = 1; i<search.size(); i++){
                wordResults = peeps.find(search[i]).getInstances();
                for(auto & wordResult : wordResults){
                    results.push_back(wordResult);
                }
            }
        }
        //search through normal index
        else {
            for(auto & i : search){
                wordResults = info.find(i).getInstances();
                for(auto & wordResult : wordResults){
                    results.push_back(wordResult);
                }
            }
        }
        //remove duplicates(?)
        if(andor == 1){
            //code to remove duplicates
        }
        else{
            //code to remove unique values??

        }

        google.storeAnswers(results);
        google.printAnswers();
    }

    void printInfo(){
        info.prettyPrintTree();
    }

    void printPeeps(){
        peeps.prettyPrintTree();
    }

    void printOrgs(){
        orgs.prettyPrintTree();
    }


    void checkKey(string& code){
        orgs.find(code).printAllInstances();
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
