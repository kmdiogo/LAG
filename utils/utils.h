#ifndef LAG_UTILS_H
#define LAG_UTILS_H

#include <iostream>
#include "../TokenReturner/TokenReturner.h"
bool isValidIdentifier(std::string);
void printError(pair<Tokens, string> p);
void printPair(pair<Tokens, string> p);

#endif //LAG_UTILS_H
