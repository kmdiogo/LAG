//
// Created by Kenny on 2/13/2019.
//

#ifndef LAG_TOKENRECOGNIZER_H
#define LAG_TOKENRECOGNIZER_H

#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
using namespace std;

enum Tokens {Class, Token, Identifier, SetStart, SetStartNegate, SetEnd, SetEndDash, Character, Dash};

class TokenRecognizer {
public:
    pair<Tokens, string> getNextToken(istream &file, bool);

private:
    pair<Tokens, string> matchIdentifier(istream &file);

};


#endif //LAG_TOKENRECOGNIZER_H
