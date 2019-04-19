//
// Created by Kenny on 4/18/2019.
//

#ifndef LAG_REGEXNODE_H
#define LAG_REGEXNODE_H

#include <iostream>
using namespace std;

enum NodeType {
    ConcatNode, CharacterNode, IdNode, PlusNode, QuestionNode, StarNode, UnionNode
};

class RegexNode {
public:
    explicit RegexNode(NodeType nt, string v="") {
        firstNFA = lastNFA = left = right = index = -1;
        type = nt;
        value = v;
    }
    RegexNode() {}
    void printNode();

    NodeType type;
    int left;
    int right;
    int index;
    int firstNFA;
    int lastNFA;
    string value;
};


#endif //LAG_REGEXNODE_H
