//
// Created by Kenny on 4/12/2019.
//

#ifndef LAG_PARSER_H
#define LAG_PARSER_H

#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include "../utils/utils.h"
#include "../TokenReturner/TokenReturner.h"
using namespace std;

class Parser {
public:
    void parse();
    Parser(string path) {
        file.seekg(0);
        file.open(path);
        lookahead = getNextToken(file, true);
    }

private:
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

    pair<Tokens, string> cur;
    pair<Tokens, string> lookahead;
    ifstream file;
};


#endif //LAG_PARSER_H
