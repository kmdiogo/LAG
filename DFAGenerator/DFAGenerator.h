//
// Created by Kenny on 4/24/2019.
//

#ifndef LAG_DFAGENERATOR_H
#define LAG_DFAGENERATOR_H

#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <queue>
#include <algorithm>
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
    map< set<int>, map<vector<char>, set<int>> > DFATable;
    vector<map<vector<char>, int>> DFATableSimplified;
    map< set<int>, string> acceptingStates;
    map<int, string> acceptingStateSimplified;
    set<int> ignores;
    map<set<int>, int> stateAliases;
    set<int> startingState;

private:
    // Methods
    void generateDFA();
    string IsDFAStateAccepting(set<int> DFAState);
    set<int> eClosure(set<int> state);
    set<int> move(set<int> state, vector<char> input);

};


#endif //LAG_DFAGENERATOR_H
