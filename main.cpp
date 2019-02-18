#include <iostream>
#include <fstream>
#include "TokenRecognizer/TokenRecognizer.h"
#define PATH "C:\\Users\\Kenny\\Desktop\\LAG\\input.txt"
#define PATH2 "E:\\Programming\\YSU\\CSCI 5807 - Compiler Design\\LAG\\input.txt"
using namespace std;

string TokensStr[] = {"Class", "Token", "Identifier", "SetStart", "SetStartNegate", "SetEnd", "SetEndDash", "Character", "Dash"};

void printPair(pair<Tokens, string> p) {
    cout << TokensStr[p.first] << ' ' << p.second << endl;
}
int main() {
    ifstream file;
    file.open(PATH2);
    if (!file) {
        cout << "Unable to open file" << endl;
        return 0;
    }
    TokenRecognizer tr = TokenRecognizer();
    printPair(tr.getNextToken(file, false));
    printPair(tr.getNextToken(file, false));
    printPair(tr.getNextToken(file, false));
    file.close();
    return 0;
}




