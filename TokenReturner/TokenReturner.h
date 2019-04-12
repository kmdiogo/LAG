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

enum Tokens {Class, Token, Id, Ignore,
        SetStart, SetStartNegate, SetEnd, DashSetEnd,
        Character, Dash, Star, Plus, Question, EOI};

/*string TokensStr[] = {"Class", "Token", "Id", "Ignore",
                      "SetStart", "SetStartNegate", "SetEnd", "DashSetEnd",
                      "Character", "Dash", "Star", "Plus", "Question", "EOI"};*/

pair<Tokens, string> getNextToken(ifstream &file, bool);

pair<Tokens, string> getCTII(ifstream &file);


#endif //LAG_TOKENRECOGNIZER_H
