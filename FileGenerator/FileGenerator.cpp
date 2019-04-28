//
// Created by Kenny on 4/26/2019.
//

#include "FileGenerator.h"
using namespace std;

const string fileLocation = "../../Lag_Driver/";
void FileGenerator::generateHeader() {
    // Create token enum declaration
    string tokensStr = "enum Token{";
    for (auto & name: tokenNames) {
        if (name != "ignore")
            tokensStr += name + ",";
    }
    tokensStr += "};\n\n";

    ofstream outFile;
    outFile.open(fileLocation + "test.h");

    outFile << R"(
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;
)";

    outFile << tokensStr;

    outFile << R"(
class LexicalAnalyzer {
    public:
        LexicalAnalyzer(ifstream &input);
        void start();
        bool next(Token &t, string &lexeme);

        vector< map<vector<char>, int> > dfa;
        map<int, Token> acceptingStates;
        unordered_set<int> ignores;
        ifstream & input;

};
)";

    //outFile << tokensStr << inputSetStr << statesStr << dfaStr;
    outFile.close();

}

void FileGenerator::generateBody() {
    // Create inputs vector declaration
    string genInputsStr;
    for (auto & charSet : inputs) {
        genInputsStr += "inputs.emplace_back(vector<char>{";
        for (auto & ch : charSet) {
            genInputsStr += "'";
            genInputsStr += ch;
            genInputsStr += "'";
            genInputsStr += ",";
        }
        genInputsStr += "});\n";
    }
    genInputsStr += "\n\n";


    // Create state vector declaration string
    string genStateStr;
    for (int i=0; i < DFATable.size(); i++) {
        genStateStr += "states.emplace_back(" + to_string(i) + ");\n";
    }
    genStateStr += "\n\n";


    // Create DFA declaration
    string genDFAStr = "map<vector<char>, int> stateMap;\n";
    for (int i=0; i < DFATable.size(); i++) {
        for (auto & charSet : inputs) {
            genDFAStr += "stateMap[vector<char>{";
            for (auto & ch : charSet) {
                genDFAStr += "'";
                genDFAStr += ch;
                genDFAStr += "'";
                genDFAStr += ",";
            }
            genDFAStr += "}] = " + to_string(DFATable[i][charSet]) + ";\n";
        }
        genDFAStr += "dfa.emplace_back(stateMap);\n\n";

    }

    // Create accepting states map
    string genAccStatesStr;
    for (auto & statePair : acceptingStates) {
        if (statePair.second != "ignore")
            genAccStatesStr += "acceptingStates[" + to_string(statePair.first) + "]=" + statePair.second + ";\n";
        else
            genAccStatesStr += "ignores.insert(" + to_string(statePair.first) + ");\n";
    }
    genAccStatesStr += "\n\n";




    ofstream outFile;
    outFile.open(fileLocation + "test.cpp");
    outFile << R"(
#include "test.h"
using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream &INPUT) : input(INPUT) {
)";
    outFile << genDFAStr << genAccStatesStr << "}\n\n\n";

    outFile << R"(
bool LexicalAnalyzer::next(Token &t, string &lexeme) {
    begin:
    if (input.eof()) {
        return false;
    }
    string lex = "";
    char curChar;
    int currentState = 0;
    while (input >> curChar) {
        bool inputMatched = false;
        for (auto & inp : dfa[currentState]) {
            for (auto & ch : inp.first) {
                if (curChar == ch) {
                    inputMatched = true;
                    if (inp.second == -1) {
                        input.seekg(-1, input.cur);
                        goto afterLoop;
                    }
                    lex += curChar;
                    currentState = inp.second;
                    break;
                }
            }
        }
        if (!inputMatched) throw "Input doesn't match any token";
    }
    afterLoop:

    if (ignores.find(currentState) != ignores.end()) {
        goto begin;
    }
    else if (acceptingStates.find(currentState) == acceptingStates.end()) {
        throw "Input doesn't match any token";
    }
    else {
        t = acceptingStates[currentState];
        lexeme = lex;
        return true;
    }
}
)";



    outFile.close();
}

unordered_set<int> FileGenerator::getIgnores() {
    unordered_set<int> igns;
    for (auto & x : acceptingStates) {
        if (x.second == "ignore") {
            igns.insert(x.first);
        }
    }
    return igns;
}
