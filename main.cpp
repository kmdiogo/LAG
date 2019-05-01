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

#define PATH "../test3.dat"
using namespace std;

int main() {
    cout << "Parsing..." << endl;
    Parser parser = Parser(PATH);
    cout << "...Parse successful!" << endl << endl;

    cout << "Generating NFA..." << endl;
    NFAGenerator nfaGen = NFAGenerator(parser.getParseTrees(), parser.getLookupTable(), parser.getTokenNames());
    cout << "...NFA successfully generated!" << endl << endl;

    cout << "Generating DFA..." << endl;
    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());
    cout << "...DFA succesfully generated!" << endl << endl;

    cout << "Generating files..." << endl;
    const string fileLocation = "../../LAG_Driver/";
    const string fileName = "LexicalAnalyzer";
    FileGenerator fileGen = FileGenerator(dfaGen.DFATableSimplified,
            dfaGen.acceptingStateSimplified,
            parser.getTokenNames(),
            nfaGen.getInputs(),
            parser.getLookupTable(),
            fileLocation,
            fileName);
    cout << "...Files successfully generated!" << endl;

    return 0;
}




