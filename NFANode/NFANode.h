//
// Created by Kenny on 4/23/2019.
//

#ifndef LAG_NFANODE_H
#define LAG_NFANODE_H

#include <vector>
#include <iostream>
using namespace std;

class edge {
public:
    edge(int transNode, vector<char> transChars) {
        this->transNode = transNode;
        this->transChars = transChars;
    }
    int transNode;
    vector<char> transChars;
};

class NFANode {
public:
    void printNode();
    vector<edge> edges;
    bool isAccepting = false;
};



#endif //LAG_NFANODE_H
