#ifndef LAG_UTILS_H
#define LAG_UTILS_H

#include <iostream>
#include "../TokenReturner/TokenReturner.h"
#include<iostream>
#include<stack>
#include<string>
using namespace std;

void printError(pair<Tokens, string> p, string msg="");
void printPair(pair<Tokens, string> p);

// Function to convert Infix expression to postfix
string InfixToPostfix(string expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
bool IsOperand(char C);

#endif //LAG_UTILS_H
