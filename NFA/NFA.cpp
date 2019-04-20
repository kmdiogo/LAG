//
// Created by Kenny on 4/19/2019.
//

#include "NFA.h"

int first, last;
void NFA::printNFA() {
    cout << nodes.size() << endl;
    for (int i = 0; i < nodes.size(); i++) {
        if (!nodes[i].isNull) {
            cout << "----- Node " << i << " -----" << endl;
            cout << "  Edges" << endl;
            for (auto & edge : nodes[i].edges) {
                cout << "\t" << edge.transNode << " " << edge.transChar << endl;
            }
            cout << endl;
        }
    }
}


NFA::NFA(vector<vector<RegexNode>> parseTrees) {
    this->parseTrees = parseTrees;
    vector<RegexNode> tree = parseTrees[0];
    processNode(parseTrees[0].back());

}

void NFA::processNode(RegexNode& node){
    if (node.left != -1) {
        processNode(parseTrees[0][node.left]);
    }
    if (node.right != -1) {
        processNode(parseTrees[0][node.right]);
    }

    switch(node.type) {
        case StarNode:
            addStarClosure(node);
            break;
        case UnionNode:
            addUnion(node);
            break;
        case CharacterNode:
            addCharacter(node);
            break;
        case ConcatNode:
            addConcat(node);
    }
}



void NFA::addStarClosure(RegexNode& node) {
    node.firstNFA = nodes.size();
    nodes.emplace_back(NFANode());

    node.lastNFA = nodes.size();
    nodes.emplace_back(NFANode());

    nodes[node.firstNFA].edges.emplace_back(edge(node.lastNFA, "%"));

    int childLast = parseTrees[0][node.left].lastNFA;
    int childFirst = parseTrees[0][node.left].firstNFA;
    nodes[node.firstNFA].edges.emplace_back( edge(childFirst, "%") );
    nodes[childLast].edges.emplace_back( edge(node.lastNFA, "%") );
    nodes[childLast].edges.emplace_back( edge(childFirst, "%") );
}


void NFA::addUnion(RegexNode& node) {
    node.firstNFA = nodes.size();
    nodes.emplace_back(NFANode());

    node.lastNFA = nodes.size();
    nodes.emplace_back(NFANode());

    nodes[node.firstNFA].edges.emplace_back( edge(parseTrees[0][node.left].firstNFA, "%") );
    nodes[node.firstNFA].edges.emplace_back( edge(parseTrees[0][node.right].firstNFA, "%") );

    nodes[parseTrees[0][node.left].lastNFA].edges.emplace_back( edge(node.lastNFA, "%") );
    nodes[parseTrees[0][node.right].lastNFA].edges.emplace_back( edge(node.lastNFA, "%") );
}

void NFA::addCharacter(RegexNode& node) {
    node.firstNFA = nodes.size();
    nodes.emplace_back(NFANode());

    node.lastNFA = nodes.size();
    nodes.emplace_back(NFANode());

    nodes[node.firstNFA].edges.emplace_back(edge(node.lastNFA, node.value));
}

void NFA::addConcat(RegexNode &node) {
    for (auto & e : nodes[parseTrees[0][node.right].firstNFA].edges) {
        nodes[parseTrees[0][node.left].lastNFA].edges.emplace_back( edge(e.transNode, e.transChar) );
    }

    nodes[parseTrees[0][node.right].firstNFA].isNull = true;

    node.firstNFA = parseTrees[0][node.left].firstNFA;
    node.lastNFA = parseTrees[0][node.right].lastNFA;



    /*parseTrees[0][node.left].lastNFA = newLast;
    parseTrees[0][node.right].firstNFA = newFirst;*/
}

