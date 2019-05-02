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

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Error - please pass the following parameters:" << endl;
        if (argc == 1) {
            cout << "  1. Input file name" << endl;
            cout << "  2. Output file basename" << endl;
            cout << "  3. Output directory (optional)" << endl;
            return 0;
        }
        else {
            cout << "  2. Output file basename" << endl;
            cout << "  3. Output directory (optional)" << endl;
            return 0;
        }

    }
    cout << "Input file: " << argv[1] << endl;
    cout << "Output file basename: " << argv[2] << endl;
    if (argc >= 3)
        cout << "Output directory: " << argv[3] << endl;
    cout << endl;
    string inputFile = argv[1];
    string fileName = argv[2];
    string fileLocation = argc >= 4 ? argv[3] : "";

    cout << "Parsing..." << endl;
    Parser parser = Parser(inputFile);
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
            fileLocation,
            fileName);
    cout << "...Files successfully generated!" << endl;

    return 0;
}




