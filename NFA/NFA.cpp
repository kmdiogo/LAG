//
// Created by Kenny on 4/19/2019.
//

#include "NFA.h"

int first, last;
void NFA::printNFA() {
    for (int i = 0; i < nfaNodes.size(); i++) {
        cout << "----- Node " << i;
        if (nfaNodes[i].isAccepting) {
            cout << " (accepting)";
        }
        cout << " -----" << endl;

        cout << "  Edges" << endl;
        for (auto & edge : nfaNodes[i].edges) {
            cout << "\tto: " << edge.transNode << " | " << "char(s): ";
            if (edge.transChars.size() == 0)
                cout << "epsilon" << endl;
            else {
                for (auto & ch : edge.transChars) {
                    cout << ch << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}


NFA::NFA(vector<vector<RegexNode>> parseTrees, map<string, vector<char>> classLookupTable) {
    this->parseTrees = parseTrees;
    this->classLookupTable = classLookupTable;

    for (int i=0; i < this->parseTrees.size(); i++) {
        processNode(parseTrees[i].back(), 0);
        nfaNodes[parseTrees[i].back().lastNFA].isAccepting = true;
    }


}

void NFA::processNode(RegexNode &node, int treeNumber) {
    if (node.left != -1) {
        processNode(parseTrees[treeNumber][node.left], 0);
    }
    if (node.right != -1) {
        processNode(parseTrees[treeNumber][node.right], 0);
    }

    switch(node.type) {
        case StarNode:
            addStarClosure(node, treeNumber);
            break;
        case UnionNode:
            addUnion(node, treeNumber);
            break;
        case CharacterNode:
            addCharacter(node, treeNumber);
            break;
        case ConcatNode:
            addConcat(node, treeNumber);
            break;
        case IdNode:
            addId(node, treeNumber);
            break;
    }
}



void NFA::addStarClosure(RegexNode &node, int treeNumber) {
    node.firstNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    node.lastNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    nfaNodes[node.firstNFA].edges.emplace_back(edge(node.lastNFA, vector<char>()));

    int childLast = parseTrees[treeNumber][node.left].lastNFA;
    int childFirst = parseTrees[treeNumber][node.left].firstNFA;
    nfaNodes[node.firstNFA].edges.emplace_back( edge(childFirst, vector<char>()) );
    nfaNodes[childLast].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    nfaNodes[childLast].edges.emplace_back( edge(childFirst, vector<char>()) );

}


void NFA::addUnion(RegexNode &node, int treeNumber) {
    node.firstNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    node.lastNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    nfaNodes[node.firstNFA].edges.emplace_back( edge(parseTrees[treeNumber][node.left].firstNFA, vector<char>()) );
    nfaNodes[node.firstNFA].edges.emplace_back( edge(parseTrees[treeNumber][node.right].firstNFA, vector<char>()) );

    nfaNodes[parseTrees[treeNumber][node.left].lastNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    nfaNodes[parseTrees[treeNumber][node.right].lastNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
}

void NFA::addCharacter(RegexNode &node, int treeNumber) {
    node.firstNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    node.lastNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    nfaNodes[node.firstNFA].edges.emplace_back( edge(node.lastNFA, vector<char>{node.value[0]}) );
}

void NFA::addId(RegexNode &node, int treeNumber) {
    node.firstNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    node.lastNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    cout << node.value << endl;

    nfaNodes[node.firstNFA].edges.emplace_back( edge(node.lastNFA, classLookupTable[node.value]) );
}

void NFA::addConcat(RegexNode &node, int treeNumber) {
    RegexNode leftChild = parseTrees[treeNumber][node.left];
    RegexNode rightChild = parseTrees[treeNumber][node.right];

    nfaNodes[leftChild.lastNFA].edges.emplace_back( edge(rightChild.firstNFA, vector<char>()) );

    node.firstNFA = parseTrees[treeNumber][node.left].firstNFA;
    node.lastNFA = parseTrees[treeNumber][node.right].lastNFA;


    /*parseTrees[0][node.left].lastNFA = newLast;
    parseTrees[0][node.right].firstNFA = newFirst;*/
}



