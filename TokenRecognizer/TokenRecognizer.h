//
// Created by Kenny on 2/13/2019.
//

#ifndef LAG_TOKENRECOGNIZER_H
#define LAG_TOKENRECOGNIZER_H

#include <iostream>
#include <fstream>
#include <utility>
using namespace std;
enum Tokens {Class, Token, Identifier, SetStart, SetStartNegate, SetBody, SetEnd, SetEndDash};

class TokenRecognizer {
public:
    pair<Tokens, string> getNextToken(istream &file);

private:
    pair<Tokens, string> matchClass(istream &file);
    pair<Tokens, string> matchToken(istream &file);
    pair<Tokens, string> matchIdentifier(istream &file);

};


#endif //LAG_TOKENRECOGNIZER_H
