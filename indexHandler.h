//
// Created by Alex Gonzalez on 11/8/22.
//
#include <vector>
#include "AVL_TREE.h"
#include "key.h"
#include "myDocument.h"
#include "DocParser.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "Porter2/porter2_stemmer.h"

#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H

using namespace std;

class indexHandler {
private:
    AvlTree<key> info;
    AvlTree<key> peeps;
    AvlTree<key> orgs;
    DocParser parser;
    query google;
    unordered_map<string,string> hash;

    vector<string> uuids;

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
                hash[doc.getUUID()] = doc.getName();
                uuids.push_back(doc.getUUID());
            }
        }
    }

    void storeTree(AvlTree<key> tree, string filename){
        tree.saveToFile(filename);
    }

    void storeMap(unordered_map<string,string> hash, vector<string> uuids, string name){
        ofstream file;
        file.open(name);

        if(hash.empty()){
            file.close();
            return;
        }

        for(size_t i = 0; i<hash.size();++i){
            file << hash[uuids.at(i)] << endl;
        }

        file.close();
    }

    void reloadTree(const string& filename){
        info.makeEmpty();
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
            info.balancedInsert(insert);
        }

    }

    void search(){
        google.getQuery();
        vector<string> orgqueries = google.getOrgQueries();
        vector<string> peepqueries = google.getPeepQueries();
        vector<string> wordqueries = google.getWordQueries();
        vector<string> skipwords = google.getSkipAnswers();

        vector<string> results;
        vector<string> instancesPerWord;
        vector<string> it;
        int n = sizeof(results,sizeof(results[0]));
        //start with first word, since its logical AND
        // every following uuid needs to be in this first one
        instancesPerWord = info.find(wordqueries[0]).getInstances();
        for(auto & j : instancesPerWord){
            results.push_back(j);
        }
        sort(results.begin(), results.end());
        for(int i = 1; i<wordqueries.size(); i++){
            instancesPerWord = info.find(wordqueries[i]).getInstances();
            sort(instancesPerWord.begin(), instancesPerWord.end());
            it.end() = set_intersection(results.begin(),results.end(),instancesPerWord.begin(),instancesPerWord.end(),it.begin());
            results = it;
        }
        //search through peeps index
        /*else if(search[0] == "person"){
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
            //code to remove unique values??
        }
        else{
            //code to remove duplicates

        }
         */

        //duplicate remover but not sure if it works
        /*
        vector<string> duplicateChecker;
        for(size_t i = 0; i<results.size();++i){
            duplicateChecker.push_back(results.at(i));
            if(std::any_of(duplicateChecker.begin(), duplicateChecker.end(), [](string str){ ; }){
                std::remove(results.at(i).begin(), results.at(i).end(), results.at(i));
            }else{
                continue;
            }
        }
         */


        results = UuidtoTitles(it);

        google.storeAnswers(results);
        google.resultsMenu();
    }

    vector<string> UuidtoTitles(vector<string> uuids){
        vector<string> answers;
        for(size_t i = 0; i<uuids.size();++i){
            answers.push_back(hash[uuids.at(i)]);
        }
        return answers;
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

    AvlTree<key> getOrgs(){
        return this->orgs;
    }

    AvlTree<key> getPeeps(){
        return this->peeps;
    }

    AvlTree<key> getWords(){
        return this->info;
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
