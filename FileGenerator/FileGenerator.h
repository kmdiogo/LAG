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
using namespace std;

class FileGenerator {
public:
    FileGenerator(vector<map<vector<char>, int> > & DFATable,
            map< vector<int>, string> & acceptingStates,
            map<vector<int>, int> & stateAliases,
            vector<int> & startingState,
            vector<string> tokenNames,
            const set<vector<char>> & inputs) {

        this->DFATable = DFATable;
        this->acceptingStates = acceptingStates;
        this->stateAliases = stateAliases;
        this->startingState = startingState;
        this->tokenNames = tokenNames;
        this->inputs = inputs;

        generateHeader();
    }

private:
    void generateHeader();
    vector<map<vector<char>,int> > DFATable;
    map< vector<int>, string> acceptingStates;
    map<vector<int>, int> stateAliases;
    vector<int> startingState;
    set<vector<char>> inputs;
    vector<string> tokenNames;
};


#endif //LAG_FILEGENERATOR_H
