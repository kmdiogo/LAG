//
// Created by Kenny on 4/18/2019.
//

#include "RegexNode.h"
string nodeStr[] = {"ConcatNode", "CharacterNode", "IdNode", "PlusNode", "QuestionNode", "StarNode", "UnionNode"};

void RegexNode::printNode() {
    cout << "Index: " << index << endl;
    cout << "Type: " << nodeStr[nodeType] << endl;
    cout << "Left: [" << left << "]" << endl;
    cout << "Right: [" << right << "]" << endl;
    cout << "Value: " << value << endl << endl;
}