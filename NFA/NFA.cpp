//
// Created by Kenny on 4/19/2019.
//

#include "NFA.h"

/**
 * Debug function that prints the NFA in a readable manner
 */
void NFA::printNFA() {
    for (int i = 0; i < nfaNodes.size(); i++) {
        cout << "----- Node " << i;
        if (nfaNodes[i].isAccepting) {
            cout << " (accepting)";
        }
        cout << " -----" << endl;

        cout << "  ";
        nfaNodes[i].printNode();
    }
}


NFA::NFA(vector<vector<RegexNode>> parseTrees, map<string, vector<char>> classLookupTable) {
    this->parseTrees = parseTrees;
    this->classLookupTable = classLookupTable;

    // Add the starting node
    nfaNodes.emplace_back(NFANode());


    // Iterate through all parse trees and generate their corresponding NFA
    for (int i=0; i < this->parseTrees.size(); i++) {
        processNode(parseTrees[i].back(), i);
        nfaNodes[parseTrees[i].back().lastNFA].isAccepting = true;
    }

    // Add epsilon transitions for the generated regex NFAs (connects them together)
    for (auto & tree: parseTrees) {
        nfaNodes[0].edges.emplace_back( edge(tree.back().firstNFA, vector<char>()) );
    }


}

/**
 * Recursive function for postorder traversal of a tree. Used to generate an NFA from a given parse tree using Thompson's construction
 * @param node - the current processed node in the parse tree
 * @param treeNumber - the index of the parse tree that it being processed
 */
void NFA::processNode(RegexNode &node, int treeNumber) {
    if (node.left != -1) {
        processNode(parseTrees[treeNumber][node.left], treeNumber);
    }
    if (node.right != -1) {
        processNode(parseTrees[treeNumber][node.right], treeNumber);
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

/**
 * Adds the NFA nodes for Star Closure
 */
void NFA::addStarClosure(RegexNode &node, int treeNumber) {
    // Add starting closure node
    node.firstNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    // Add end closure node
    node.lastNFA = nfaNodes.size();
    nfaNodes.emplace_back(NFANode());

    int childLast = parseTrees[treeNumber][node.left].lastNFA;
    int childFirst = parseTrees[treeNumber][node.left].firstNFA;
    // Connect first node and last node with epsilon
    nfaNodes[node.firstNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    // Connect first node to first node in child with epsilon
    nfaNodes[node.firstNFA].edges.emplace_back( edge(childFirst, vector<char>()) );
    // Connect the last node in child to the last node
    nfaNodes[childLast].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    // Connect the last node in child to the first node in child
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



