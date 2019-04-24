//
// Created by Kenny on 4/18/2019.
//

#ifndef LAG_PARSETREENODE_H
#define LAG_PARSETREENODE_H

#include <iostream>
using namespace std;

enum NodeType {
    ConcatNode, CharacterNode, IdNode, PlusNode, QuestionNode, StarNode, UnionNode
};

class ParseTreeNode {
public:
    explicit ParseTreeNode(NodeType nt, string v="") {
        firstNFA = lastNFA = left = right = index = -1;
        type = nt;
        value = v;
    }
    ParseTreeNode() = default;
    void printNode();

    NodeType type;
    int left;
    int right;
    int index;
    int firstNFA;
    int lastNFA;
    string value;
};


#endif //LAG_PARSETREENODE_H
