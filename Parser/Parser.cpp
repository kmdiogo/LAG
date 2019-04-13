//
// Created by Kenny on 4/12/2019.
//

#include "Parser.h"

void Parser::parse() {
    if (matchStmtList())
        cout << "Parse Successful" << endl;
    else
        cout << "Parse Unsuccessful" << endl;

}

bool Parser::matchStmtList(){
    if (cur.first == EOI)
        return true;
    else {
        // TODO: Fix repetition with grammar rules
        if (!matchStmt()) {
            printError(cur, "Stmt not matched in stmtList");
        }
        while (matchStmt());
        return true;
    }
}

bool Parser::matchStmt() {
    if (!matchClassStmt()) {
        if (!matchTokenStmt()) {
            if (!matchIgnoreStmt()) {
                return false;
            }
        }
    }
    return true;
}

bool Parser::matchClassStmt() {
    cur = getNextToken(file, true);

    if (cur.first != Class) {
        return false;
    }

    cur = getNextToken(file, true);

    if (cur.first != Id) {
        printError(cur);
    }

    cur = getNextToken(file, false);

    if (cur.first != SetStart && cur.first != SetStartNegate) {
        printError(cur);
    }

    cur = getNextToken(file, false);

    if (!matchCItemList()) {
        printError(cur);
    }

    //cur = getNextToken(file, false);

    if (cur.first != SetEnd && cur.first != DashSetEnd) {
        printError(cur);
    }
    return true;
}

bool Parser::matchCItemList() {
    if (cur.first == EOI)
        return true;
    else {
        // TODO: fix repetition with grammar rules
        if (!matchCItem()) {
            printError(cur, "cItem not matched in cItemList");
        }
        while (matchCItem());
        return true;
    }
}

bool Parser::matchCItem() {
    if (cur.first != Character) {
        //printError(cur);
        return false;
    }

    cur = getNextToken(file, false);

    if (cur.first == Dash) {
        cur = getNextToken(file, false);
        if (cur.first != Character) {
            printError(cur);
        }
        return true;
    }
    else {
        return true;
    }
}

bool Parser::matchTokenStmt() {
    if (cur.first != Token) {
        return false;
    }

    cur = getNextToken(file, true);

    if (cur.first != Id) {
        printError(cur);
    }

    cur = getNextToken(file, false);

    if (cur.second != "/") {
        printError(cur);
    }

    if (!matchRegex()) {
        printError(cur);
        return false;
    }

    cur = getNextToken(file, false);

    if (cur.second != "/") {
        printError(cur);
    }

    return true;
}

bool Parser::matchIgnoreStmt(){
    if (cur.first != Ignore) {
        return false;
    }

    cur = getNextToken(file, false);

    if (cur.second != "/") {
        printError(cur);
    }

    cur = getNextToken(file, false);

    if (!matchRegex()) {
        printError(cur);
    }

    cur = getNextToken(file, false);

    if (cur.second != "/") {
        printError(cur);
    }

    return true;
}

bool Parser::matchRegex() {
    if (!matchRTerm()) {
        return false;
    }

    while (matchRTerm());

    return true;
}

bool Parser::matchRTerm() {
    if (!matchRClosure()) {
        return false;
    }

    while(matchRClosure());

    return true;
}

bool Parser::matchRClosure() {
    if (!matchRFactor()) {
        printError(cur);
        return false;
    }


    cur = getNextToken(file, false);
    if (cur.first == EOI) {
        return true;
    }
    if (cur.first != Star && cur.first != Plus && cur.first != Question) {
        printError(cur);
        return false;
    }
}

bool Parser::matchRFactor() {
    if (cur.first == SetStart) {
        cur = getNextToken(file, true);
        if (cur.first != Id) {
            printError(cur);
            return false;
        }
        cur = getNextToken(file, false);
        if (cur.first != SetEnd) {
            printError(cur);
            return false;
        }
        return true;
    }
    if (cur.second == "(") {
        cur = getNextToken(file, true);
        if (!matchRegex()) {
            printError(cur);
            return false;
        }
        cur = getNextToken(file, false);
        if (cur.second != ")") {
            printError(cur);
            return false;
        }
        return true;
    }
}