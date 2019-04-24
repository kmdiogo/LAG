//
// Created by Kenny on 4/18/2019.
//

#include "ParseTreeNode.h"
string nodeStr[] = {"ConcatNode", "CharacterNode", "IdNode", "PlusNode", "QuestionNode", "StarNode", "UnionNode"};

void ParseTreeNode::printNode() {
    cout << "Index: " << index << endl;
    cout << "Type: " << nodeStr[type] << endl;
    cout << "Left: [" << left << "]" << endl;
    cout << "Right: [" << right << "]" << endl;
    cout << "Value: " << value << endl;
    cout << "First NFAGenerator Node: (" << firstNFA << ")" << endl;
    cout << "Last NFAGenerator Node: (" << lastNFA << ")" << endl << endl;
}