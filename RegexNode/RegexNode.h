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
        nodeType = nt;
        left = -1;
        right = -1;
        value = v;
        index = -1;
    }
    RegexNode() {}
    void printNode();

    NodeType nodeType;
    int left;
    int right;
    int index;
    string value;
};


#endif //LAG_REGEXNODE_H
