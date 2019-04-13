//
// Created by Kenny on 2/13/2019.
//
#include "TokenReturner.h"
using namespace std;

pair<Tokens, string> getNextToken(ifstream &file, bool aggregrate) {
    char cur, lookahead;
    while (file >> cur) {
        lookahead = file.peek();
        if (!aggregrate) {
            if (cur == '[' && lookahead == '^') {
                file.get();
                return make_pair(SetStartNegate, "[^");
            }
            else if (cur == '[')
                return make_pair(SetStart, string() + cur);
            else if (cur == '-' && lookahead == ']') {
                file.get();
                return make_pair(DashSetEnd, "-]");
            }
            else if (cur == ']') {
                return make_pair(SetEnd, "]");
            }
            else if (cur == '*') {
                return make_pair(Star, "*");
            }
            else if (cur == '+') {
                return make_pair(Plus, "+");
            }
            else if (cur == '?') {
                return make_pair(Question, "?");
            }
            else if (cur == '-') {
                return make_pair(Dash, string() + cur);
            }
            else if (cur == '$') {
                return make_pair(EOI, "$");
            }
            else {
                return make_pair(Character, string() + cur);
            }
        }
        else {
            if ( (isalpha(cur) || cur == '_'))
                return getCTII(file, cur);
        }
    }
    return make_pair(EOI, "$");
}


pair<Tokens, string> getCTII(ifstream &file, char cur) {
    string temp;
    file >> temp;
    string lexeme = cur + temp;
    if (lexeme == "class")
        return make_pair(Class, lexeme);
    else if (lexeme == "token")
        return make_pair(Token, lexeme);
    else if (lexeme == "ignore")
        return make_pair(Ignore, lexeme);
    else {
        for (int i=1; i < lexeme.length(); i++) {
            if (!isalpha(lexeme[i])) {
                cout << "Invalid identifier: " << lexeme << endl;
                exit(0);
            }
        }
        return make_pair(Id, lexeme);
    }

}