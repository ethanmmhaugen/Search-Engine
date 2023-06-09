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
    unordered_map<string, string> hashUrls;
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
    void scanDocOrgs(Document& d, string& uuid){
        auto organizations = d["entities"]["organizations"].GetArray();
        for (auto &p : organizations)
        {
            string tempO = parser.orgLowerCase(p["name"].GetString());
            Porter2Stemmer::stem(tempO);

            if(!orgs.contains(tempO)) {
                orgs.insert(key(tempO));
            }
            orgs.find(key(tempO)).addInst(uuid);
        }
    }

    void scanDocPeople(Document& d, string& uuid){
        auto people = d["entities"]["persons"].GetArray();
        for (auto &p : people)
        {
            string tempP = parser.orgLowerCase(p["name"].GetString());
            Porter2Stemmer::stem(tempP);

            if(!peeps.contains(tempP)) {
                peeps.insert(key(tempP));
            }
            peeps.find(key(tempP)).addInst(uuid);
        }
    }


    void scanDocWords(Document& d, string& uuid){
        auto text = d["text"].GetString();
        istringstream ss(text);
        string tempW;
        while(ss>>tempW) {
            tempW = parser.lowerCase(tempW);
            Porter2Stemmer::stem(tempW);

            if (!info.contains(tempW)) {
                info.insert(key(tempW));
            }
            info.find(key(tempW)).addInst(uuid);
        }
    }

    void populate(string path){
        int count = 0;
        for(const auto& entry: filesystem::recursive_directory_iterator(path)){
            if(entry.is_regular_file() && entry.path().extension().string() == ".json"){
                Document doc;
                //Populate people index
                ifstream input(entry.path().string());
                if (!input.is_open()) {
                    cerr << "cannot open file: " << entry.path().string() << endl;
                }
                IStreamWrapper isw(input);
                doc.ParseStream(isw);
                string uuid = doc["uuid"].GetString();
                scanDocOrgs(doc, uuid);
                scanDocPeople(doc, uuid);
                scanDocWords(doc, uuid);
                hash[uuid] = doc["title"].GetString();
                hcount[uuid] = 0;
                hashUrls[uuid] = doc["url"].GetString();

                uuids.push_back(uuid);
                count++;
                if(count%100 == 0){
                    cout << count << " documents parsed... " << endl;
                }
            }
        }
    }
    void storeTree(AvlTree<key> tree, string filename){
        tree.saveToFile(filename);
    }

    void storeMaps(unordered_map<string,string> shash, vector<string> suuids, string name){
        ofstream file;
        file.open(name);

        //SAVING FIRST MAP
        if(shash.empty()){
            file.close();
            return;
        }

        for(size_t i = 0; i<shash.size();++i) {
            file << suuids.at(i) << " " << shash[suuids.at(i)] << endl;
        }

        file.close();

    }
    void storeMaps(unordered_map<string,size_t> shcount, vector<string> suuids, string name){
        ofstream file;
        file.open(name);
        if(shcount.empty()){
            file.close();
            return;
        }

        for(size_t i = 0; i<shcount.size();++i){
            file << suuids.at(i) << " " << shcount[suuids.at(i)] << endl;
        }

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

    void reloadMaps(const string filename, const string filename2, const string filename3){
        hash.clear();
        hcount.clear();
        hashUrls.clear();
        ifstream file(filename);
        ifstream file2(filename2);
        ifstream file3(filename3);
        if(!file.is_open()||!file2.is_open() || !file3.is_open()){
            cout << "Error, one or more of your map files not found" << endl;
        }
        vector<string> tempUs;
        string buff;
        size_t buf;
        string buff2;
        string tmpU;
        while(!file.eof()){
            getline(file, buff);
            stringstream s(buff);
            getline(s, tmpU, ' ');
            tempUs.push_back(tmpU);
            getline(s, buff);
            hash[tmpU] = buff;
        }
        file.close();
        cout << "Title Map Reloaded" << endl;
        while(!file2.eof()){
            getline(file2, buff);
            stringstream s(buff);
            getline(s, tmpU, ' ');
            s >> buf;
            s << endl;
            hcount[tmpU] = buf;
        }
        file2.close();
        cout << "Count Map Reloaded" << endl;
        while(!file3.eof()){
            getline(file3, buff);
            stringstream s(buff);
            getline(s, tmpU, ' ');
            s >> buff2;
            s << endl;
            hashUrls[tmpU] = buff2;
        }
        cout << "Url Map Reloaded" << endl;
        uuids = tempUs;
        file3.close();
    }

    chrono::duration<double> search(){
        chrono::time_point<chrono::system_clock> start, end;
        chrono::duration<double> elapsed_time;
        start = chrono::system_clock::now();
        google.getQuery();
        vector<string> orgqueries = google.getOrgQueries();
        vector<string> peepqueries = google.getPeepQueries();
        vector<string> wordqueries = google.getWordQueries();
        vector<string> skipwords = google.getSkipAnswers();

        vector<string> results;
        vector<string> subtract;
        vector<string> instancesPerWord;
        vector<string> it;
        vector<string> req;
        vector<string> final;
        bool peepStart = false;
        bool orgStart = false;
        bool negPeepStart = false;
        bool negOrgStart = false;

        //for loop lets us skip if we hit a catch
        for(int i = 0; i<1; i++) {
            //If wordqueries has something, takes all of them and adds to results
            if (!wordqueries.empty()) {
                //gets starting word
                try { instancesPerWord = info.find(wordqueries[0]).getInstances(); }
                catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}

                for (auto &j: instancesPerWord) {

                    try{auto it = hcount.find(j);
                        if (it != hcount.end()) {
                            it->second++;
                        }
                    }
                    catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}

                    results.push_back(j);
                }
                sort(results.begin(), results.end());
                //get the rest of that sucker
                for (size_t i = 1; i < wordqueries.size(); i++) {
                    try{instancesPerWord = info.find(wordqueries[i]).getInstances();}
                    catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                    for (auto &j: instancesPerWord) {
                        try {
                            auto it = hcount.find(j);
                            if (it != hcount.end()) {
                                it->second++;
                            }

                            if (hash[j].find(wordqueries[i]) != string::npos) {
                                auto it = hcount.find(j);
                                if (it != hcount.end()) {
                                    it->second++;
                                }
                            }
                        }
                        catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                    }

                    sort(instancesPerWord.begin(), instancesPerWord.end());
                    set_intersection(results.begin(), results.end(), instancesPerWord.begin(), instancesPerWord.end(),
                                     back_inserter(it));
                    results = it;
                }
            }
                //if wordqueries empty, we start with the first word of peepqueries assuming its positive
            else if (!peepqueries.empty() && peepqueries[0] != "negative") {
                try {
                    instancesPerWord = peeps.find(peepqueries[0]).getInstances();
                    for (auto &j: instancesPerWord) {
                        auto it = hcount.find(j);
                        if (it != hcount.end()) {
                            it->second++;
                        }
                        results.push_back(j);
                    }
                }
                catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                sort(results.begin(), results.end());
                peepStart = true;


            }
                //Or just go to Orgs to get our starting results vector
            else {
                try {
                    instancesPerWord = orgs.find(orgqueries[0]).getInstances();
                    for (auto &j: instancesPerWord) {
                        auto it = hcount.find(j);
                        if (it != hcount.end()) {
                            it->second++;
                        }
                        results.push_back(j);
                    }
                    sort(results.begin(), results.end());
                }
                catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                orgStart = true;
            }

            //now add in rest of peepqueries
            if (!peepqueries.empty()) {
                if (peepqueries[0] != "negative") {
                    for (size_t i = (!peepStart ? 1 : 2); i < peepqueries.size(); i++) {
                        try {
                            instancesPerWord = peeps.find(peepqueries[i]).getInstances();
                            for (auto &j: instancesPerWord) {
                                auto it = hcount.find(j);
                                if (it != hcount.end()) {
                                    it->second++;
                                }
                                if (hash[j].find(peepqueries[i]) != string::npos) {
                                    auto it = hcount.find(j);
                                    if (it != hcount.end()) {
                                        it->second++;
                                    }
                                }
                            }

                            sort(instancesPerWord.begin(), instancesPerWord.end());
                            set_intersection(results.begin(), results.end(), instancesPerWord.begin(),
                                             instancesPerWord.end(),
                                             back_inserter(it));
                            results = it;
                        }
                        catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                    }

                }
            }
            //add in rest of orgqueries
            if (!orgqueries.empty()) {
                if (orgqueries[0] != "negative") {
                    for (size_t i = (!orgStart ? 1 : 2); i < orgqueries.size(); i++) {
                        try {
                            instancesPerWord = orgs.find(orgqueries[i]).getInstances();
                            for (auto &j: instancesPerWord) {
                                auto it = hcount.find(j);
                                if (it != hcount.end()) {
                                    it->second++;
                                }
                                if (hash[j].find(orgqueries[i]) != string::npos) {
                                    auto it = hcount.find(j);
                                    if (it != hcount.end()) {
                                        it->second++;
                                    }
                                }
                            }

                            sort(instancesPerWord.begin(), instancesPerWord.end());
                            set_intersection(results.begin(), results.end(), instancesPerWord.begin(),
                                             instancesPerWord.end(),
                                             back_inserter(it));
                            results = it;
                        }
                        catch (std::runtime_error) { cout << "Not found, sorry" << endl;  end = chrono::system_clock::now(); break;}
                    }
                }
            }

            //normal stopwords
            if(!skipwords.empty()){
                //gets starting word
                try { instancesPerWord = info.find(skipwords[0]).getInstances(); }
                catch (std::runtime_error) {}

                for (auto &j: instancesPerWord) {
                    subtract.push_back(j);
                }
                for (size_t i = 1; i < skipwords.size(); i++) {
                    try{instancesPerWord = info.find(skipwords[i]).getInstances();}
                    catch (std::runtime_error) {}
                    sort(instancesPerWord.begin(), instancesPerWord.end());
                    set_intersection(subtract.begin(), subtract.end(), instancesPerWord.begin(), instancesPerWord.end(),
                                     back_inserter(it));
                    subtract = it;
                }
            }
            //start with PERSON
            else if(!peepqueries.empty()){
                if(peepqueries[0] == "negative"){
                    try {
                        instancesPerWord = peeps.find(peepqueries[1]).getInstances();
                        for (auto &j: instancesPerWord) {
                            subtract.push_back(j);
                        }
                    }
                    catch (std::runtime_error) {}
                    sort(subtract.begin(), subtract.end());
                    negPeepStart = true;
                }
            }
            //start with ORG
            else if(!orgqueries.empty()){
                if(orgqueries[0] == "negative"){
                    try {
                        instancesPerWord = orgs.find(orgqueries[1]).getInstances();
                        for (auto &j: instancesPerWord) {
                            subtract.push_back(j);
                        }
                    }
                    catch (std::runtime_error) {}
                    sort(subtract.begin(), subtract.end());
                    negOrgStart = true;
                }
            }
            //now add in rest of the negative peepqueries
            if (!peepqueries.empty()) {
                if (peepqueries[0] == "negative") {
                    for (size_t i = (!negPeepStart ? 1 : 2); i < peepqueries.size(); i++) {
                        try {
                            instancesPerWord = peeps.find(peepqueries[i]).getInstances();
                            sort(instancesPerWord.begin(), instancesPerWord.end());
                            set_intersection(subtract.begin(), subtract.end(), instancesPerWord.begin(),
                                             instancesPerWord.end(),
                                             back_inserter(it));
                            subtract = it;
                        }
                        catch (std::runtime_error) {}
                    }

                }
            }
            //now add in rest of the negative orgqueries
            if (!orgqueries.empty()) {
                if (orgqueries[0] == "negative") {
                    for (size_t i = (!negOrgStart ? 1 : 2); i < orgqueries.size(); i++) {
                        try {
                            instancesPerWord = orgs.find(orgqueries[i]).getInstances();
                            sort(instancesPerWord.begin(), instancesPerWord.end());
                            set_intersection(subtract.begin(), subtract.end(), instancesPerWord.begin(),
                                             instancesPerWord.end(),
                                             back_inserter(it));
                            subtract = it;
                        }
                        catch (std::runtime_error) {}
                    }

                }
            }

            sort(results.begin(), results.end());
            results.erase(unique(results.begin(),results.end()), results.end());
            for(size_t i = 0; i<results.size(); i++){
                if(std::find(subtract.begin(), subtract.end(),(results[i])) != subtract.end()){
                    results.erase(results.begin()+i);
                }
            }

            string temp;
            for(size_t i = 0; i<results.size(); i++) {
                for (size_t j = i + 1; j < results.size(); j++) {

                    if (hcount[results[j]] > hcount[results[i]]) {
                        temp = results[i];
                        results[i] = results[j];
                        results[j] = temp;
                    }
                }
            }

            google.storeAnswers(results);
            end = chrono::system_clock::now();
            google.resultsMenu(hashUrls, hash);

        }
        elapsed_time = end-start;
        return elapsed_time;
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


    void checkKey(string code){
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

    unordered_map<string, string> getUrlMap(){
        return this->hashUrls;
    }
};


#endif //FINALPROJEXAMPLES_INDEX_H
