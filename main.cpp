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
    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());

    for (auto & p : dfaGen.acceptingStateSimplified) {
        cout << "{";
        cout << p.first;
        cout << "} " << p.second << endl;
    }
    FileGenerator fileGen = FileGenerator(dfaGen.DFATableSimplified,
            dfaGen.acceptingStateSimplified,
            parser.getTokenNames(),
            nfaGen.getInputs(),
            parser.getLookupTable());




    return 0;
}




