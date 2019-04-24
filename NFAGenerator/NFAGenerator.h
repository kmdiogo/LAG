//
// Created by Kenny on 4/19/2019.
//

#ifndef LAG_NFAGENERATOR_H
#define LAG_NFAGENERATOR_H

#include <vector>
#include <string>
#include <map>
#include "../NFANode/NFANode.h"
#include "../ParseTreeNode/ParseTreeNode.h"
using namespace std;

class NFAGenerator {
public:
    void printNFA();
    vector<NFANode> getNFA() {return NFA;}
    NFAGenerator(vector< vector<ParseTreeNode> > parseTrees, map<string, vector<char>> classLookupTable);
private:
    void processNode(ParseTreeNode &node, int treeNumber);
    void addUnion(ParseTreeNode &node, int treeNumber);
    void addStarClosure(ParseTreeNode &node, int treeNumber);
    void addCharacter(ParseTreeNode &node, int treeNumber);
    void addConcat(ParseTreeNode &node, int treeNumber);
    void addId(ParseTreeNode &node, int treeNumber);

    vector<vector<ParseTreeNode>> parseTrees;
    vector<NFANode> NFA;
    map<string, vector<char>> classLookupTable;

};


#endif //LAG_NFAGENERATOR_H
