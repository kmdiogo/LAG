//
// Created by Kenny on 4/26/2019.
//

#include "FileGenerator.h"
using namespace std;

void FileGenerator::generateHeader() {
    // Create token enum declaration
    string tokensStr = "enum Token{";
    for (auto & name: tokenNames) {
        tokensStr += name + ",";
    }
    tokensStr += "};\n\n";
    cout << tokensStr << endl << endl;

    // Create inputs vector declaration
    string inputSetStr = "vector<vector<char>> inputs;\n";
    for (auto & charSet : inputs) {
        inputSetStr += "inputs.emplace_back(vector<char>{";
        for (auto & ch : charSet) {
            inputSetStr += "'";
            inputSetStr += ch;
            inputSetStr += "'";
            inputSetStr += ",";
        }
        inputSetStr += "});\n";
    }
    inputSetStr += "\n\n";

    // Create state vector declaration string
    string statesStr = "vector<int> states;\n";
    for (int i=0; i < DFATable.size(); i++) {
        statesStr += "states.emplace_back(" + to_string(i) + ");\n";
    }
    statesStr += "\n\n";

    // Create DFA declaration
    string dfaStr = "vector< map<vector<char>, int> > dfa;\nmap<vector<char>, int> stateMap;\n";
    for (int i=0; i < DFATable.size(); i++) {
        for (auto & charSet : inputs) {
            dfaStr += "stateMap[vector<char>{";
            for (auto & ch : charSet) {
                dfaStr += "'";
                dfaStr += ch;
                dfaStr += "'";
                dfaStr += ",";
            }
            dfaStr += "}] = " + to_string(DFATable[i][charSet]) + ";\n";
        }
        dfaStr += "dfa.emplace_back(stateMap);\n";
    }



    ofstream outFile;
    outFile.open("../test.h");
    outFile << "#include <vector>\n#include <map>\nusing namespace std;\n";
    outFile << tokensStr << inputSetStr << statesStr << dfaStr;
    outFile.close();


}
