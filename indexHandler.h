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
    unordered_map<string, size_t> hcount;
    vector<string> uuids;
    vector<string> stop{"a", "an", "for", "and", "nor", "but", "or", "yet", "both", "not", "the", "my", "me", "you", "your", "yours", "his", "her", "they", "them", "he", "him", "she", "in", "on", "by"};

public:
    indexHandler() = default;

    indexHandler(const indexHandler&rhs){
        info = rhs.info;
        peeps = rhs.peeps;
        orgs = rhs.orgs;
        parser = rhs.parser;
    };

    indexHandler& operator=(const indexHandler&rhs){
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

    /*
    void insertWord(key word){
        info.insert(word);
    }

    void insertPerson(key person){
        peeps.insert(person);
    }



    void insertOrg(key &org){
        orgs.insert(org);
    }
*/

    //function for adding instances of a word to index or adding to word index
    void scanDocWords(myDocument doc){
        for(size_t i = 0; i<doc.getWords().size(); ++i){
            Porter2Stemmer::stem(doc.getWords().at(i));
            for(auto &j : stop){
                if (doc.getWords().at(i) == j)continue;
            }
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

    void populate(string& path){
        for(const auto& entry: filesystem::recursive_directory_iterator(path)){
            if(entry.is_regular_file() && entry.path().extension().string() == ".json"){
                myDocument doc = parser.readJsonFile(entry.path().string());
                //Populate people index
                scanDocOrgs(doc);
                scanDocPeople(doc);
                scanDocWords(doc);
                hash[doc.getUUID()] = doc.getName();
                hcount[doc.getUUID()] = 0;
                uuids.push_back(doc.getUUID());
            }
        }
    }

    void storeTree(AvlTree<key> tree, string filename){
        tree.saveToFile(filename);
    }

    void storeMaps(unordered_map<string,string> shash, unordered_map<string, size_t> shcount,vector<string> suuids, string name, string name2){
        ofstream file;
        ofstream file2;
        file.open(name);
        file2.open(name2);

        //SAVING FIRST MAP
        if(shash.empty()){
            file.close();
            return;
        }

        for(size_t i = 0; i<shash.size();++i){
            file << suuids.at(i) << " " << shash[suuids.at(i)] << endl;
        }
        //SAVING SECOND MAP
        if(shcount.empty()){
            file2.close();
            return;
        }

        for(size_t i = 0; i<shcount.size();++i){
            file2 << suuids.at(i) << " " << shcount[suuids.at(i)] << endl;
        }

        file.close();
        file2.close();
    }

    void orgreloadTree(const string& filename){
        orgs.makeEmpty();
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error, org tree file not found" << endl;
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
        file.close();
    }
    void peepreloadTree(const string& filename){
        peeps.makeEmpty();
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error, people tree file not found" << endl;
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
            peeps.balancedInsert(insert);
        }
        file.close();
    }
    void wordreloadTree(const string& filename){
        info.makeEmpty();
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error, word tree file not found" << endl;
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
        file.close();
    }

    void reloadMaps(const string& filename, const string& filename2){
        hash.clear();
        hcount.clear();
        ifstream file(filename);
        ifstream file2(filename2);
        if(!file.is_open()||!file2.is_open()){
            cout << "Error, one or more of your map files not found" << endl;
        }
        string buff;
        size_t buf;
        string tmpU;
        while(!file.eof()){
            getline(file, buff);
            stringstream s(buff);
            getline(s, tmpU, ' ');
            getline(s, buff);
            hash[tmpU] = buff;
        }
        while(!file2.eof()){
            getline(file2, buff);
            stringstream s(buff);
            getline(s, tmpU, ' ');
            s >> buf;
            s << endl;
            hcount[tmpU] = buf;
        }
        file.close();
        file2.close();
    }

    void search(){
        info.prettyPrintTree();
        google.getQuery();
        vector<string> orgqueries = google.getOrgQueries();
        vector<string> peepqueries = google.getPeepQueries();
        vector<string> wordqueries = google.getWordQueries();
        vector<string> skipwords = google.getSkipAnswers();

        vector<string> results;
        vector<string> instancesPerWord;
        vector<string> it;
        vector<string> req;
        vector<string> final;
        int n = sizeof(results,sizeof(results[0]));
        //start with first word, since its logical AND
        // every following uuid needs to be in this first one
        instancesPerWord = info.find(wordqueries[0]).getInstances();
        for(auto & j : instancesPerWord){
            auto it = hcount.find(j);
            if(it != hcount.end()){
                it -> second++;
            }
            results.push_back(j);
        }
        sort(results.begin(), results.end());
        for(auto & wq: wordqueries){
            instancesPerWord = info.find(wq).getInstances();
            for (auto &j: instancesPerWord)hcount[j] = +1;
            sort(instancesPerWord.begin(), instancesPerWord.end());
            set_intersection(results.begin(),results.end(),instancesPerWord.begin(),instancesPerWord.end(), back_inserter(it));
            results = it;
        }
        //extra weight if word exists in title
        for(auto & wq : wordqueries){
            instancesPerWord = info.find(wq).getInstances();
            for(auto & j : instancesPerWord){
                if(hash[j].find(wq) != string::npos){
                    auto it = hcount.find(j);
                    if(it != hcount.end()){
                        it -> second+=10;
                    }
                }
            }
        }

        //IF PERSON IS SEARCHED
        if(!peepqueries.empty()){
            for(auto & pq : peepqueries){
                instancesPerWord = info.find(pq).getInstances();
                for (auto &j: instancesPerWord){
                    if(std::find(results.begin(), results.end(), j)!=results.end()){
                        auto it = hcount.find(j);
                        if(it != hcount.end()){
                            it -> second++;
                        }
                        req.push_back(j);
                    }
                }
            }

            //extra weight if person exists in title
            for(auto & pq : peepqueries){
                instancesPerWord = info.find(pq).getInstances();
                for(auto & j : instancesPerWord){
                    if(hash[j].find(pq) != string::npos){
                        auto it = hcount.find(j);
                        if(it != hcount.end()){
                            it -> second+=10;
                        }
                    }
                }
            }
        }

        if(!orgqueries.empty()){
            for(auto & oq : orgqueries){
                instancesPerWord = info.find(oq).getInstances();
                for (auto &j: instancesPerWord){
                    if(std::find(results.begin(), results.end(), j)!=results.end()){
                       if(!peepqueries.empty()){
                           if(std::find(req.begin(), req.end(), j)!=req.end()){
                               auto it = hcount.find(j);
                               if(it != hcount.end()){
                                   it -> second++;
                               }
                               final.push_back(j);
                           }
                       }else{
                           auto it = hcount.find(j);
                           if(it != hcount.end()){
                               it -> second++;
                           }
                           final.push_back(j);
                       }
                    }
                }
            }

            //extra weight if org exists in title
            for(auto & oq : orgqueries){
                instancesPerWord = info.find(oq).getInstances();
                for(auto & j : instancesPerWord){
                    if(hash[j].find(oq) != string::npos){
                        auto it = hcount.find(j);
                        if(it != hcount.end()){
                            it -> second+=10;
                        }
                    }
                }
            }
        }

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


        results = UuidtoTitles(results);

        google.storeAnswers(results);
        google.resultsMenu();
    }

    vector<string> UuidtoTitles(vector<string> uuidst){
        vector<string> answers;
        answers.reserve(uuidst.size());
        for(auto & uuid : uuidst){
            answers.push_back(hash[uuid]);
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

    vector<string> getUUIDs(){
        return this->uuids;
    }

    unordered_map<string, string> getHashMap(){
        return this->hash;
    }

    unordered_map<string, size_t> getCountMap(){
        return this->hcount;
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
