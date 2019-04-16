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
    explicit Parser(const string &inputFilePath) {
        // TODO: Verify openining in binary mode or disabling buffering is legit

        //file.rdbuf()->pubsetbuf(nullptr, 0);
        file.open(inputFilePath, ios::binary);
        if (!file) {
            cout << "Unable to open file" << endl;
            exit(0);
        }
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

    pair<Tokens, string> peekNextToken(bool aggregrate);

    pair<Tokens, string> cur;
    ifstream file;
};


#endif //LAG_PARSER_H
