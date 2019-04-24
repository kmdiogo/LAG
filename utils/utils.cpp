#include "utils.h"
using namespace std;

string TokensStr[] = {"Class", "Token", "Id", "Ignore",
                      "SetStart", "SetStartNegate", "SetEnd", "DashSetEnd",
                      "OpenParen", "Close Paren", "Slash", "Pipe",
                      "Character", "Dash", "Star", "Plus", "Question", "EOI"};

void printPair(const pair<Tokens, string> & p) {
    cout << "( " << TokensStr[p.first] << ", " << p.second << " )" << endl;
}

