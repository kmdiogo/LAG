//
// Created by Kenny on 4/26/2019.
//

#ifndef LAG_FILEGENERATOR_H
#define LAG_FILEGENERATOR_H

#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <unordered_set>
using namespace std;

class FileGenerator {
public:
    FileGenerator(vector<map<vector<char>, int> > & DFATable,
            map< int, string> & acceptingStates,
            vector<string> tokenNames,
            const set<vector<char>> & inputs,
            map<string, vector<char>> charClassLookup) {

        this->DFATable = DFATable;
        this->acceptingStates = acceptingStates;
        this->tokenNames = tokenNames;
        this->inputs = inputs;
        for (auto & p : charClassLookup) {
            this->charClassLookup[p.second] = p.first;
        }


        generateHeader();
        generateBody();
        generateListingFile();
    }

private:
    void generateHeader();
    void generateBody();
    void generateListingFile();
    unordered_set<int> getIgnores();

    vector<map<vector<char>,int> > DFATable;
    map<int, string> acceptingStates;
    set<vector<char>> inputs;
    vector<string> tokenNames;
    map<vector<char>, string> charClassLookup;
};


#endif //LAG_FILEGENERATOR_H
