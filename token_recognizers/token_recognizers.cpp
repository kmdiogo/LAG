#include "token_recognizers.h"
using namespace std;

bool matchClass(ifstream &file) {
    int startPos = file.tellg();

    string lexeme;
    file >> lexeme;

    if (lexeme != "class") {
        file.seekg(startPos);
        return false;
    }
    else {
        file >> lexeme;
        // Throw error, since 'class' followed by an invalid identifier is a syntax error
        if (!isValidIdentifier(lexeme)) {
            cout << "Invalid Class Identifier: " << lexeme;
            exit(0);
        }
        return matchSet(file);
    }
}

bool matchSet(ifstream &file) {
    int startPos = file.tellg();
    string lexeme;
    file >> lexeme;

    // Check for closing brackets
    // TODO: Ask Kramer about what nextToken should return
    if (lexeme[0] == '\\' && lexeme[1] == '[') {
        if (lexeme[lexeme.length()-2] == '\\' && lexeme[lexeme.length()-1] == ']') {
            return true;
        }
        cout << "Error, unclosed set of brackets: " << lexeme << endl;
        exit(0);
    }
    file.seekg(startPos);
    return false;
}

