#include "utils.h"
using namespace std;

string TokensStr[] = {"Class", "Token", "Id", "Ignore",
                      "SetStart", "SetStartNegate", "SetEnd", "DashSetEnd",
                      "Character", "Dash", "Star", "Plus", "Question", "EOI"};

bool isValidIdentifier(string id) {
    // Return false if first character is not underscore or alphabet
    if (!isalpha(id[0]) && id[0] != '_')
        return false;
    // Ensure every other character is alphanumeric
    for (int i=1; i < id.length(); i++) {
        if (!isalnum(id[i]))
            return false;
    }
    return true;
}

void printPair(pair<Tokens, string> p) {
    cout << TokensStr[p.first] << ' ' << p.second << endl;
}

void printError(pair<Tokens, string> p, string msg) {
    cout << "Parse Error: " << endl;
    cout << "Token: ";
    printPair(p);
    cout << msg << endl;
    exit(0);
}

