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

    for (auto & p : dfaGen.getDFAStateTokenNames()) {
        cout << "{";
        for (auto & x : p.first) {
            cout << x << ",";
        }
        cout << "} " << p.second << endl;
    }


    dfaGen.simulateDFA("guccitwotimesMotherFucker69");


    return 0;
}




