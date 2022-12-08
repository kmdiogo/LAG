#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include <vector>

#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include "NFAGenerator/NFAGenerator.h"
#include "DFAGenerator/DFAGenerator.h"
#include "FileGenerator/FileGenerator.h"

using namespace std;

extern "C" {
    int run(char* inputFile, char* fileName, char* fileLocation);
}

int run(char* inputFile, char* fileName, char* fileLocation = "") {

    cout << "Parsing..." << endl;
    Parser parser = Parser(string(inputFile));
    cout << "...Parse successful!" << endl << endl;

    cout << "Generating NFA..." << endl;
    NFAGenerator nfaGen = NFAGenerator(parser.getParseTrees(), parser.getLookupTable(), parser.getTokenNames());
    cout << "...NFA successfully generated!" << endl << endl;

    cout << "Generating DFA..." << endl;
    DFAGenerator dfaGen = DFAGenerator(nfaGen.getNFA(), nfaGen.getInputs());
    cout << "...DFA succesfully generated!" << endl << endl;

    cout << "Generating files..." << endl;
    FileGenerator fileGen = FileGenerator(dfaGen.DFATableSimplified,
            dfaGen.acceptingStateSimplified,
            parser.getTokenNames(),
            nfaGen.getInputs(),
            parser.getLookupTable(),
            string(fileLocation),
            string(fileName));
    cout << "...Files successfully generated!" << endl;

    return 0;
}
