#include "utils.h"
using namespace std;

string TokensStr[] = {"Class", "Token", "Id", "Ignore",
                      "SetStart", "SetStartNegate", "SetEnd", "DashSetEnd",
                      "OpenParen", "Close Paren", "Slash",
                      "Character", "Dash", "Star", "Plus", "Question", "EOI"};

void printPair(pair<Tokens, string> p) {
    cout << "( " << TokensStr[p.first] << ", " << p.second << " )" << endl;
}

void printError(pair<Tokens, string> p, string msg) {
    cout << "Parse Error: " << endl;
    cout << "Token: ";
    printPair(p);
    cout << msg << endl;
    exit(0);
}

