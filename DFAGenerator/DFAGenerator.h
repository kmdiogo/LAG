//
// Created by Kenny on 4/24/2019.
//

#ifndef LAG_DFAGENERATOR_H
#define LAG_DFAGENERATOR_H

#include <vector>
#include <set>
#include <map>
#include "../NFANode/NFANode.h"
using namespace std;

class DFAGenerator {
public:
    DFAGenerator(vector<NFANode> nfa, set<vector<char>> inputs) {
        NFA = nfa;
        this->inputs = inputs;
        generateDFA();
    }

    void printDFA();
    map< vector<int>, map<vector<char>, vector<int>> > getDFATable() {return DFATable;}

private:
    // Methods
    void generateDFA();

    vector<int> eClosure(vector<int> state);
    vector<int> move(vector<int> state, vector<char> input);

    // Attributes
    vector<NFANode> NFA;
    set<vector<char>> inputs;
    map< vector<int>, map<vector<char>, vector<int>> > DFATable;

};


#endif //LAG_DFAGENERATOR_H
