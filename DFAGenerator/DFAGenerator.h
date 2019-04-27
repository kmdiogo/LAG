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
    void printSimpleDFA();
    void simulateDFA(string input);

    // Attributes
    vector<NFANode> NFA;
    set<vector<char>> inputs;
    map< vector<int>, map<vector<char>, vector<int>> > DFATable;
    vector<map<vector<char>, int>> DFATableSimplified;
    map< vector<int>, string> acceptingStates;
    map<vector<int>, int> stateAliases;
    vector<int> startingState;

private:
    // Methods
    void generateDFA();
    string IsDFAStateAccepting(vector<int> DFAState);
    vector<int> eClosure(vector<int> state);
    vector<int> move(vector<int> state, vector<char> input);

};


#endif //LAG_DFAGENERATOR_H
