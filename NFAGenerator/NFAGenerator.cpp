//
// Created by Kenny on 4/19/2019.
//

#include "NFAGenerator.h"

/**
 * Debug function that prints the NFA in a readable manner
 */
void NFAGenerator::printNFA() {
    for (int i = 0; i < NFA.size(); i++) {
        cout << "----- Node " << i;
        if (NFA[i].isAccepting) {
            cout << " (accepting)";
        }
        cout << " -----" << endl;

        cout << "  ";
        NFA[i].printNode();
    }
}

void NFAGenerator::printInputs() {
    int i =0;
    for (auto & input : inputs) {
        cout << "Input " << i << ": ";
        for (auto & ch : input) {
            cout << ch << " ";
        }
        cout << endl;
        i++;
    }
}


NFAGenerator::NFAGenerator(vector<vector<ParseTreeNode>> parseTrees, map<string, vector<char>> classLookupTable, vector<string> tokenNames) {
    this->parseTrees = parseTrees;
    this->classLookupTable = classLookupTable;

    // Add the starting node
    NFA.emplace_back(NFANode());

    // Iterate through all parse trees and generate their corresponding NFAGenerator
    for (int i=0; i < this->parseTrees.size(); i++) {
        processNode(parseTrees[i].back(), i);
        NFA[parseTrees[i].back().lastNFA].isAccepting = true;
        NFA[parseTrees[i].back().lastNFA].tokenName = tokenNames[i];
    }

    // Add epsilon transitions for the generated regex NFAs (connects them together)
    for (auto & tree: parseTrees) {
        NFA[0].edges.emplace_back( edge(tree.back().firstNFA, vector<char>()) );
    }


}

/**
 * Recursive function for postorder traversal of a tree. Used to generate an NFA from a given parse tree using Thompson's construction
 * @param node - the current processed node in the parse tree
 * @param treeNumber - the index of the parse tree that it being processed
 */
void NFAGenerator::processNode(ParseTreeNode &node, int treeNumber) {
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
void NFAGenerator::addStarClosure(ParseTreeNode &node, int treeNumber) {
    // Add starting closure node
    node.firstNFA = NFA.size();
    NFA.emplace_back(NFANode());

    // Add end closure node
    node.lastNFA = NFA.size();
    NFA.emplace_back(NFANode());

    int childLast = parseTrees[treeNumber][node.left].lastNFA;
    int childFirst = parseTrees[treeNumber][node.left].firstNFA;
    // Connect first node and last node with epsilon
    NFA[node.firstNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    // Connect first node to first node in child with epsilon
    NFA[node.firstNFA].edges.emplace_back( edge(childFirst, vector<char>()) );
    // Connect the last node in child to the last node
    NFA[childLast].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    // Connect the last node in child to the first node in child
    NFA[childLast].edges.emplace_back( edge(childFirst, vector<char>()) );

}


void NFAGenerator::addUnion(ParseTreeNode &node, int treeNumber) {
    node.firstNFA = NFA.size();
    NFA.emplace_back(NFANode());

    node.lastNFA = NFA.size();
    NFA.emplace_back(NFANode());

    NFA[node.firstNFA].edges.emplace_back( edge(parseTrees[treeNumber][node.left].firstNFA, vector<char>()) );
    NFA[node.firstNFA].edges.emplace_back( edge(parseTrees[treeNumber][node.right].firstNFA, vector<char>()) );

    NFA[parseTrees[treeNumber][node.left].lastNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
    NFA[parseTrees[treeNumber][node.right].lastNFA].edges.emplace_back( edge(node.lastNFA, vector<char>()) );
}

void NFAGenerator::addCharacter(ParseTreeNode &node, int treeNumber) {
    node.firstNFA = NFA.size();
    NFA.emplace_back(NFANode());

    node.lastNFA = NFA.size();
    NFA.emplace_back(NFANode());


    NFA[node.firstNFA].edges.emplace_back( edge(node.lastNFA, vector<char>{node.value[0]}) );

    if (inputs.find(vector<char>{node.value[0]}) == inputs.end()) {
        inputs.insert(vector<char>{node.value[0]});
    }
}

void NFAGenerator::addId(ParseTreeNode &node, int treeNumber) {
    node.firstNFA = NFA.size();
    NFA.emplace_back(NFANode());

    node.lastNFA = NFA.size();
    NFA.emplace_back(NFANode());

    NFA[node.firstNFA].edges.emplace_back( edge(node.lastNFA, classLookupTable[node.value]) );

    if (inputs.find(classLookupTable[node.value]) == inputs.end()) {
        inputs.insert(classLookupTable[node.value]);
    }
}

void NFAGenerator::addConcat(ParseTreeNode &node, int treeNumber) {
    ParseTreeNode leftChild = parseTrees[treeNumber][node.left];
    ParseTreeNode rightChild = parseTrees[treeNumber][node.right];

    NFA[leftChild.lastNFA].edges.emplace_back( edge(rightChild.firstNFA, vector<char>()) );

    node.firstNFA = parseTrees[treeNumber][node.left].firstNFA;
    node.lastNFA = parseTrees[treeNumber][node.right].lastNFA;


    /*parseTrees[0][node.left].lastNFA = newLast;
    parseTrees[0][node.right].firstNFA = newFirst;*/
}



