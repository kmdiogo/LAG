#include <iostream>
#include <fstream>
#include <windows.h>
#include <unordered_set>
#include <map>
#include <vector>

#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include "NFAGenerator/NFAGenerator.h"
#include "DFAGenerator/DFAGenerator.h"
#include "FileGenerator/FileGenerator.h"




#define PATH "../input.txt"
using namespace std;

int main() {
    Parser parser = Parser(PATH);

    NFAGenerator nfaGen = NFAGenerator(parser.getParseTrees(), parser.getLookupTable(), parser.getTokenNames());
    //nfaGen.printNFA();
    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());

    FileGenerator fileGen = FileGenerator(dfaGen.DFATableSimplified,
            dfaGen.acceptingStateSimplified,
            parser.getTokenNames(),
            nfaGen.getInputs(),
            parser.getLookupTable());

    return 0;
}




