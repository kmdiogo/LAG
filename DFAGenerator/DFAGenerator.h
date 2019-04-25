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

        /*for (auto & state : eClosure(vector<int>{0})) {
            cout << state << endl;
        }*/

        for (auto & x : move(vector<int>{3,3}, vector<char>{'b'})) {
            cout << x << endl;
        }
    }

private:
    // Methods
    vector<int> eClosure(vector<int> state);
    vector<int> move(vector<int> state, vector<char> input);

    // Attributes
    vector<NFANode> NFA;
    set<vector<char>> inputs;
    map< vector<int>, map<vector<char>, vector<int>> > DFATable;

};


#endif //LAG_DFAGENERATOR_H
