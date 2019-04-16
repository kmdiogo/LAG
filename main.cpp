#include <iostream>
#include <fstream>
#include "TokenReturner/TokenReturner.h"
#include "Parser/Parser.h"
#include "utils/utils.h"
#include <windows.h>

#define PATH "../input.txt"
using namespace std;

int main() {
    Parser p = Parser(PATH);
    p.parse();
    return 0;
}




