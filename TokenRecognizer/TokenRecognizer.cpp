//
// Created by Kenny on 2/13/2019.
//

#include "TokenRecognizer.h"
using namespace std;

pair<Tokens, string> TokenRecognizer::getNextToken(istream &file) {
    char cur, lookahead;
    while (file >> cur) {
        lookahead = file.peek();
        if (cur == 'c')
            return matchClass(file);
        else if (cur == 't')
            return matchToken(file);
        else if (isalpha(cur) || cur == '_')
            return matchIdentifier(file);
        else if (cur == '[' && lookahead == '^')
            return make_pair(SetStartNegate, string() + cur + lookahead);
        else if (cur == '[')
            return make_pair(SetStart, "[");
        else if (cur == '-' && lookahead == ']')
            return make_pair(SetStartNegate, string() + cur + lookahead);

    }
    cout << "No recognized tokens in remainder of the file" << endl;
    exit(0);
}

pair<Tokens, string> TokenRecognizer::matchClass(istream &file) {
    file.unget();
    string lexeme;
    file >> lexeme;
    if (lexeme == "class")
        return make_pair(Class, lexeme);
    cout << "Invalid class identifier: " << lexeme << endl;
    exit(0);
}

pair<Tokens, string> TokenRecognizer::matchToken(istream &file) {
    file.unget();
    string lexeme;
    file >> lexeme;
    if (lexeme == "token")
        return make_pair(Token, lexeme);
    cout << "Invalid token identifier: " << lexeme << endl;
    exit(0);
}

pair<Tokens, string> TokenRecognizer::matchIdentifier(istream &file) {
    file.unget();
    char ch = file.get();
    string lexeme;
    lexeme += ch;
    while (true) {
        ch = file.get();
        if (isspace(ch))
            break;
        lexeme += ch;
        if (!isalnum(ch)) {
            cout << "Invalid identifier: " << lexeme << endl;
            exit(0);
        }
    }
    return make_pair(Identifier, lexeme);
}
