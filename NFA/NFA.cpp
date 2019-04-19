//
// Created by Kenny on 4/19/2019.
//

#include "NFA.h"

int first, last;
void NFA::printNFA() {
    cout << nodes.size() << endl;
    for (int i = 0; i < nodes.size(); i++) {
        cout << "----- Node " << i << " -----" << endl;
        cout << "  Edges" << endl;
        for (auto & edge : nodes[i].edges) {
            cout << "\t" << edge.transNode << " " << edge.transChar << endl;
        }
        cout << endl;
    }
}

NFA::NFA(vector<vector<RegexNode>> parseTrees) {
    this->parseTrees = parseTrees;
    vector<RegexNode> tree = parseTrees[0];
    curNode = tree.back();

    if (tree.back().nodeType == StarNode) {
        nodes.emplace_back(NFANode());
        nodes.emplace_back(NFANode());
        nodes.emplace_back(NFANode());
        nodes.emplace_back(NFANode());
        nodes[0].edges.emplace_back(edge(1, "%"));
        nodes[0].edges.emplace_back(edge(3, "%"));
        nodes[2].edges.emplace_back(edge(1, "%"));
        first = 1;
        last = 2;
        processNode(tree[tree.back().left]);
    }
}

void NFA::processNode(RegexNode node){
    switch(node.nodeType) {
        case StarNode:
            break;
        case UnionNode:
            addUnion(first, last);
            break;
    }

    if (node.left != -1) {
        processNode(parseTrees[0][node.left]);
    }

    if (node.right != -1) {
        processNode(parseTrees[0][node.right]);
    }
    else {
        return;
    }
}



void NFA::addStarClosure(int start, int end) {

}


void NFA::addUnion(int start, int end) {
    int topStart = nodes.size();
    nodes.emplace_back(NFANode());
    int topEnd = nodes.size();
    nodes.emplace_back(NFANode());

    int bottomStart = nodes.size();
    nodes.emplace_back(NFANode());
    int bottomEnd = nodes.size();
    nodes.emplace_back(NFANode());

    nodes[start].edges.emplace_back(edge(topStart, "%"));
    nodes[start].edges.emplace_back(edge(topEnd, "%"));
    nodes[start].edges.emplace_back(edge(bottomStart, "%"));
    nodes[start].edges.emplace_back(edge(bottomEnd, "%"));
}

void NFA::addCharacter(int start, int end) {

}

