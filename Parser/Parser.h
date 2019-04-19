//
// Created by Kenny on 4/12/2019.
//

#ifndef LAG_PARSER_H
#define LAG_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../utils/utils.h"
#include "../TokenReturner/TokenReturner.h"
#include "../RegexNode/RegexNode.h"

using namespace std;

class Parser {
public:
    void parse();
    void printParseTrees();  // Debug function to view all parse trees
    vector<vector<RegexNode>> getParseTrees() {return parseTrees;}
    explicit Parser(const string &inputFilePath) {
        // Opening in binary mode necessary for input stream backtrack
        file.open(inputFilePath, ios::binary);
        if (!file) {
            cout << "Unable to open file: " << inputFilePath << endl;
            exit(0);
        }
    }

private:
    // Grammar rule subroutines
    bool matchStmtList();
    bool matchStmt();
    bool matchClassStmt();
    bool matchCItemList();
    bool matchCItem();
    bool matchTokenStmt();
    bool matchIgnoreStmt();
    bool matchRegex();
    bool matchRTerm();
    bool matchRClosure();
    bool matchRFactor();

    // Other Methods
    pair<Tokens, string> peekNextToken(bool aggregrate);    // Calls getNextToken() from TokenReturner but backtracks after done

    // Attributes
    ifstream file;
    pair<Tokens, string> cur;
    vector< vector<RegexNode> > parseTrees;
};


#endif //LAG_PARSER_H
