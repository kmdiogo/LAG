#include <iostream>
#include <fstream>
#include <windows.h>

#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include "NFAGenerator/NFAGenerator.h"
#include "DFAGenerator/DFAGenerator.h"
#include "FileGenerator/FileGenerator.h"

#include <map>
#include <vector>


#define PATH "../input.txt"
using namespace std;

int main() {
    Parser parser = Parser(PATH);
    parser.parse();
    for (auto & x : parser.getTokenNames()) {
        cout << x << endl;
    }

    NFAGenerator nfaGen = NFAGenerator(parser.getParseTrees(), parser.getLookupTable(), parser.getTokenNames());
    //nfaGen.printNFA();
    //nfaGen.printInputs();

    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());
    dfaGen.printDFA();
    dfaGen.printSimpleDFA();

    for (auto & p : dfaGen.acceptingStateSimplified) {
        cout << "{";
        cout << p.first;
        cout << "} " << p.second << endl;
    }
    FileGenerator fileGen = FileGenerator(dfaGen.DFATableSimplified,
            dfaGen.acceptingStateSimplified,
            dfaGen.stateAliases,
            dfaGen.startingState,
            parser.getTokenNames(),
            nfaGen.getInputs());




    return 0;
}




