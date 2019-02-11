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
        return true;
    }
}

bool nextTokenIsSet(ifstream &file) {

}

