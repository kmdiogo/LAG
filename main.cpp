#include <iostream>
#include <fstream>
#include <windows.h>

#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include "NFA/NFA.h"


#define PATH "../input.txt"
using namespace std;

int main() {
    Parser p = Parser(PATH);
    p.parse();

    vector<vector<RegexNode>> regexTrees = p.getParseTrees();
    map<string, vector<char>> classLookupTable = p.getLookupTable();
    //p.printParseTrees();

    NFA n = NFA(regexTrees, classLookupTable);
    n.printNFA();

    return 0;
}




