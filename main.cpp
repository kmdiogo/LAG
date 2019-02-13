#include <iostream>
#include <fstream>
#include "TokenRecognizer/TokenRecognizer.h"
#define PATH "C:\\Users\\Kenny\\Desktop\\LAG\\input.txt"
#define PATH2 "E:\\Programming\\YSU\\CSCI 5807 - Compiler Design\\LAG\\input.txt"
using namespace std;

string TokensStr[] = {"Class", "Token", "Identifier", "Error"};

int main() {
    ifstream file;
    file.open(PATH);
    if (!file) {
        cout << "Unable to open file" << endl;
        return 0;
    }
    TokenRecognizer tr = TokenRecognizer();
    cout << tr.getNextToken(file).second << endl;
    cout << tr.getNextToken(file).second << endl;
    cout << tr.getNextToken(file).second << endl;
    file.close();
    return 0;
}




