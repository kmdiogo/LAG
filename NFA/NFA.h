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
    edge(int tn, string tc) {
        transNode = tn;
        transChar = tc;
    }
    int transNode;
    string transChar;
};

class NFANode {
public:
    vector<edge> edges;
};

class NFA {
public:
    void printNFA();
    NFA(vector< vector<RegexNode> > parseTrees);
private:
    void getNextParseNode();
    void processNode(RegexNode node);
    void addUnion(int start, int end);
    void addStarClosure(int start, int end);
    void addCharacter(int start, int end);

    vector<vector<RegexNode>> parseTrees;
    vector<NFANode> nodes;
    RegexNode curNode;

};


#endif //LAG_NFA_H
