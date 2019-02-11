#include <iostream>
#include <fstream>
#include "token_recognizers/token_recognizers.h"
#define PATH "C:\\Users\\Kenny\\Desktop\\LAG\\input.txt"
using namespace std;

enum Tokens {Class, Token, Identifier, Error};
string TokensStr[] = {"Class", "Token", "Identifier", "Error"};

Tokens getNextToken(ifstream& file) {
    if (nextTokenIsClass(file))
        return Class;
    else
        return Error;
}

int main() {
    ifstream file;
    file.open(PATH);
    if (!file) {
        cout << "Unable to open file" << endl;
        return 0;
    }
    char ch;
    cout << TokensStr[getNextToken(file)];
    file.close();
    return 0;
}




