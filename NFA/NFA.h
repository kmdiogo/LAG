//
// Created by Kenny on 4/19/2019.
//

#ifndef LAG_NFA_H
#define LAG_NFA_H

#include <vector>
#include <string>
#include <map>
#include "../NFANode/NFANode.h"
#include "../RegexNode/RegexNode.h"
using namespace std;

class NFA {
public:
    void printNFA();
    NFA(vector< vector<RegexNode> > parseTrees, map<string, vector<char>> classLookupTable);
private:
    void processNode(RegexNode &node, int treeNumber);
    void addUnion(RegexNode &node, int treeNumber);
    void addStarClosure(RegexNode &node, int treeNumber);
    void addCharacter(RegexNode &node, int treeNumber);
    void addConcat(RegexNode &node, int treeNumber);
    void addId(RegexNode &node, int treeNumber);

    vector<vector<RegexNode>> parseTrees;
    vector<NFANode> nfaNodes;
    map<string, vector<char>> classLookupTable;

};


#endif //LAG_NFA_H
