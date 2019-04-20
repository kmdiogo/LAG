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
    //p.printParseTrees();
    NFA n = NFA(regexTrees);
    n.printNFA();
    return 0;
}




