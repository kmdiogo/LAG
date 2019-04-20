//
// Created by Kenny on 4/19/2019.
//

#ifndef LAG_NFA_H
#define LAG_NFA_H

#include <vector>
#include <string>
#include "../RegexNode/RegexNode.h"
using namespace std;

class edge {
public:
    edge(int transNode, string transChar) {
        this->transNode = transNode;
        this->transChar = transChar;
    }
    int transNode;
    string transChar;
};

class NFANode {
public:
    bool isNull=false;
    vector<edge> edges;
};

class NFA {
public:
    void printNFA();
    NFA(vector< vector<RegexNode> > parseTrees);
private:
    void processNode(RegexNode& node);
    void addUnion(RegexNode& node);
    void addStarClosure(RegexNode& node);
    void addCharacter(RegexNode& node);
    void addConcat(RegexNode& node);

    vector<vector<RegexNode>> parseTrees;
    vector<NFANode> nodes;

};


#endif //LAG_NFA_H
