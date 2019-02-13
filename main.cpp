#include <iostream>
#include <fstream>
#include "token_recognizers/token_recognizers.h"
#define PATH "C:\\Users\\Kenny\\Desktop\\LAG\\input.txt"
#define PATH2 "E:\\Programming\\YSU\\CSCI 5807 - Compiler Design\\LAG\\input.txt"
using namespace std;

enum Tokens {Class, Token, Identifier, Error};
string TokensStr[] = {"Class", "Token", "Identifier", "Error"};

Tokens getNextToken(ifstream& file) {
    if (matchClass(file))
        return Class;
    else
        return Error;
}

int main() {
    ifstream file;
    file.open(PATH2);
    if (!file) {
        cout << "Unable to open file" << endl;
        return 0;
    }
    char ch;
    cout << TokensStr[getNextToken(file)];
    file.close();
    return 0;
}




