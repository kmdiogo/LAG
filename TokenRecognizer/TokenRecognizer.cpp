//
// Created by Kenny on 2/13/2019.
//
#include "TokenRecognizer.h"
using namespace std;

pair<Tokens, string> TokenRecognizer::getNextToken(istream &file, bool set) {
    char cur, lookahead;
    while (file >> cur) {
        lookahead = file.peek();
        if (!set) {
            if ( (isalpha(cur) || cur == '_'))
                return matchIdentifier(file);
            else if (cur == '[' && lookahead == '^')
                return make_pair(SetStartNegate, "[^");
            else if (cur == '[')
                return make_pair(SetStart, string() + cur);
            else if (cur == '-' && lookahead == ']')
                return make_pair(SetEndDash, "-]");
            else {
                cout << "No recognized token with character/lookahead: " << cur << " / " << lookahead << endl;
                exit(0);
            }
        }
        else {
            // TODO: handle all characters, not just alphabet
            if (isalpha(cur))
                return make_pair(Character, string() + cur);
            else if (cur == '-')
                return make_pair(Dash, string() + cur);
            else {
                cout << "Not a valid set character: " << cur << endl;
                exit(0);
            }
        }
    }
    cout << "No recognized tokens in given file" << endl;
    exit(0);
}


pair<Tokens, string> TokenRecognizer::matchIdentifier(istream &file) {
    file.seekg(-2, ios::cur);
    string lexeme;
    file >> lexeme;
    if (lexeme == "class")
        return make_pair(Class, lexeme);
    else if (lexeme == "token")
        return make_pair(Token, lexeme);
    else {
        for (int i=1; i < lexeme.length(); i++) {
            if (!isalpha(lexeme[i])) {
                cout << "Invalid identifier: " << lexeme << endl;
                exit(0);
            }
        }
        return make_pair(Identifier, lexeme);
    }

}
