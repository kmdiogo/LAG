#include <iostream>
#include <fstream>
#include <windows.h>

#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include "NFAGenerator/NFAGenerator.h"
#include "DFAGenerator/DFAGenerator.h"

#include <map>
#include <vector>


#define PATH "../input.txt"
using namespace std;

int main() {
    Parser p = Parser(PATH);
    p.parse();

    NFAGenerator nfaGen = NFAGenerator(p.getParseTrees(), p.getLookupTable());
    nfaGen.printNFA();
    //nfaGen.printInputs();

    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());


    return 0;
}




