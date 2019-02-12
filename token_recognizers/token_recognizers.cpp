#include "token_recognizers.h"
using namespace std;

bool nextTokenIsClass(ifstream &file) {
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
        return nextTokenIsSet(file);
    }
}

bool nextTokenIsSet(ifstream &file) {
    int startPos = file.tellg();
    string lexeme;
    file >> lexeme;

    // Check for closing brackets
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

