#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "AVL_TREE.h"
#include "myDocument.h"
#include "key.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"


using namespace rapidjson;
using namespace std;

#ifndef FINALPROJEXAMPLES_DOCPARSER_H
#define FINALPROJEXAMPLES_DOCPARSER_H

class DocParser {
public:
    myDocument readJsonFile(const string &fileName) {
        myDocument doc;

        // open an ifstream on the file of interest and check that it could be opened.
        ifstream input(fileName);
        if (!input.is_open()) {
            cerr << "cannot open file: " << fileName << endl;
        }

        // Create a RapidJSON IStreamWrapper using the file input stream above.
        IStreamWrapper isw(input);

        // Create a RapidJSON myDocument object and use it to parse the IStreamWrapper object above.
        Document d;
        d.ParseStream(isw);

        //setting name of article
        auto val = d["title"].GetString();
        doc.setName(val);

        //setting uuid
        auto uu  = d["uuid"].GetString();
        doc.setUUID(uu);

        //setting all people
        auto persons = d["entities"]["persons"].GetArray();
        for (auto &p : persons)
        {
            doc.addPeople(p["name"].GetString());
        }

        //setting all orgs
        auto organizations = d["entities"]["organizations"].GetArray();
        for (auto &p : organizations)
        {
            doc.addOrgs(p["name"].GetString());
        }

        //setting all words
        auto text = d["text"].GetString();
        istringstream ss(text);
        string temp;

        while(ss>>temp){
            Porter2Stemmer::stem(temp);
            string delimit = " !@#$%^&*()+=/.,'\r''\n'";
            for(size_t i =0; i<temp.size(); ++i){
                for(size_t j=0; i<delimit.size();++i){
                    if(temp.at(i) == delimit.at(j)){
                        temp.erase(temp.at(i));
                        cout << "DOC PARSER STEMMING ACTUALLY GETS USED" << endl;
                    }
                }
            }
            doc.addWords(temp);
        }

        input.close();
        return doc;
    }
    };


#endif //FINALPROJEXAMPLES_DOCPARSER_H
