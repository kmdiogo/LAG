#include <iostream>
#include <fstream>
#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"

#define PATH "C:\\Users\\Kenny\\Desktop\\LAG\\input.txt"
#define PATH2 "E:\\Programming\\YSU\\CSCI 5807 - Compiler Design\\LAG\\input.txt"
using namespace std;

int main() {
    ifstream file;
    file.open(PATH);
    if (!file) {
        cout << "Unable to open file" << endl;
        return 0;
    }
    /*printPair(getNextToken(file, true));
    printPair(getNextToken(file, true));
    printPair(getNextToken(file, false));
    printPair(getNextToken(file, false));
    printPair(getNextToken(file, false));
    printPair(getNextToken(file, false));
    printPair(getNextToken(file, false));
    printPair(getNextToken(file, false));*/

    Parser p = Parser(file);
    file.close();
    return 0;
}




