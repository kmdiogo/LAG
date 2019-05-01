//
// Created by Kenny on 4/26/2019.
//

#include "FileGenerator.h"
using namespace std;

const string fileLocation = "../../LAG_Driver/";
const string fileName = "test";
void FileGenerator::generateHeader() {
    // Create token enum declaration
    string tokensStr = "enum Token{";
    for (auto & name: tokenNames) {
        if (name != "ignore")
            tokensStr += name + ",";
    }
    tokensStr += "};\n\n";

    ofstream outFile;
    outFile.open(fileLocation + fileName + ".h");
    if (!outFile) {
        cout << "File write error" << endl;
        exit(0);
    }

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
        bool nextMatchesIgnore();
    private:
        vector< map<vector<char>, int> > dfa;
        map<int, Token> acceptingStates;
        unordered_set<int> ignores;
        ifstream & input;

};
)";

    outFile.close();

}

void FileGenerator::generateBody() {
    // Create inputs vector declaration
    string genInputsStr;
    for (auto & charSet : inputs) {
        genInputsStr += "\tinputs.emplace_back(vector<char>{";
        for (auto & ch : charSet) {
            genInputsStr += "'";
            cout << "Input : " << ch << endl;
            if (ch == '\n')
                genInputsStr += "\\n";
            else if (ch == '\t')
                genInputsStr += "\\t";
            else if (ch == '\f')
                genInputsStr += "\\f";
            else if (ch == '\v')
                genInputsStr += "\\v";
            else if (ch == '\r')
                genInputsStr += "\\r";
            else
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
        genStateStr += "\tstates.emplace_back(" + to_string(i) + ");\n";
    }
    genStateStr += "\n\n";


    // Create DFA declaration
    string genDFAStr = "\tmap<vector<char>, int> stateMap;\n";
    for (int i=0; i < DFATable.size(); i++) {
        for (auto & charSet : inputs) {
            genDFAStr += "\tstateMap[vector<char>{";
            for (auto & ch : charSet) {
                genDFAStr += "'";
                if (ch == '\n') {
                    genDFAStr += "\\n";
                }
                else if (ch == '\t')
                    genDFAStr += "\\t";
                else if (ch == '\f')
                    genDFAStr += "\\f";
                else if (ch == '\v')
                    genDFAStr += "\\v";
                else if (ch == '\r')
                    genDFAStr += "\\r";
                else
                    genDFAStr += ch;
                genDFAStr += "'";
                genDFAStr += ",";
            }
            genDFAStr += "}] = " + to_string(DFATable[i][charSet]) + ";\n";
        }
        genDFAStr += "\tdfa.emplace_back(stateMap);\n\n";

    }

    // Create accepting states map and ignore set
    string genAccStatesStr;
    for (auto & statePair : acceptingStates) {
        if (statePair.second == "ignore")
            genAccStatesStr += "\tignores.insert(" + to_string(statePair.first) + ");\n";
        else
            genAccStatesStr += "\tacceptingStates[" + to_string(statePair.first) + "]=" + statePair.second + ";\n";
    }
    genAccStatesStr += "\n\n";

    // Create input class genLookup table
    /*string genLookup;
    for (auto & inPair : charClassLookup) {
        genLookup += "inputClassLookup[vector<char>{";
        for (auto & ch : inPair.second) {
            genLookup += "'";
            genLookup += ch;
            genLookup += "'";
            genLookup += ",";
        }
        genLookup += "}] = \"" + inPair.first + "\";\n";
    }
    genLookup += "\n\n";*/

    ofstream outFile;
    outFile.open(fileLocation + fileName + ".cpp");

    outFile << R"(
#include "test.h"
using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream &INPUT) : input(INPUT) {
)";

    outFile << genDFAStr << genAccStatesStr <<  "}\n\n\n";

    outFile << R"(
bool LexicalAnalyzer::next(Token &t, string &lexeme) {
    begin:
    if (input.eof()) {
        return false;
    }
    string lex = "";
    char curChar;
    int currentState = 0;
    nextCharacter:;
    while (input.peek() != EOF) {
        curChar = input.peek();
        bool inputMatched = false;
        for (auto & inp : dfa[currentState]) {
            for (auto & ch : inp.first) {
                if (curChar == ch) {
                    if (inp.second == -1) {
                        break;
                    }
                    inputMatched = true;
                    lex += curChar;
                    currentState = inp.second;
                    input.get();
                    goto nextCharacter;
                }
            }
        }
        if (!inputMatched) {
            if (acceptingStates.find(currentState) != acceptingStates.end()) {
                break;
            }
            if (ignores.find(currentState) != ignores.end())
                goto begin;
            cout << "Errored on state: " << currentState << endl;
            throw "Wrong";
        }
    }

    if (ignores.find(currentState) != ignores.end())
        goto begin;
    if (acceptingStates.find(currentState) == acceptingStates.end()) {
        cout << "Errored on state: " << currentState << endl;
        throw "Input doesn't match any token";
    }
    else {
        t = acceptingStates[currentState];
        lexeme = lex;
        return true;
    }
}
)";
    /*outFile << R"(
bool LexicalAnalyzer::next(Token &t, string &lexeme) {
    begin:
    if (input.eof()) {
        return false;
    }
    string lex = "";
    char curChar;
    int currentState = 0;

    while (input.get(curChar)) {
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

    if (acceptingStates.find(currentState) != acceptingStates.end() && acceptingStates[currentState] == "ignore") {
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
)";*/

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

void FileGenerator::generateListingFile() {
    ofstream outFile;
    outFile.open(fileLocation + "listingFile.txt");

    for (int i=0; i < DFATable.size(); i++) {
        outFile << "------ STATE " << i;
        if (acceptingStates.find(i) != acceptingStates.end())
            outFile << " (accepting for token " << acceptingStates[i] << ") ";
        outFile << " ------\n";
        for (auto & inputPair : DFATable[i]) {
            outFile << "\tinput [";
            if (charClassLookup.find(inputPair.first) != charClassLookup.end())
                outFile << charClassLookup[inputPair.first];
            else
                outFile << inputPair.first[0];
            outFile << "]: " << inputPair.second << "\n";
        }
    }
    outFile.close();
}
