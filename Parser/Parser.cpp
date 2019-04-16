//
// Created by Kenny on 4/12/2019.
//

#include "Parser.h"
// TODO: Build parse tree


pair<Tokens, string> Parser::peekNextToken(bool aggregrate) {
    int startPos = file.tellg();

    pair<Tokens, string> p = getNextToken(file, aggregrate);
    file.seekg(startPos, file.beg);

    return p;
}

void Parser::parse() {
    if (matchStmtList())
        cout << "Parse Successful" << endl;
    else
        cout << "Parse Unsuccessful" << endl;
}

bool Parser::matchStmtList(){
    if (peekNextToken(true).first == EOI)
        return true;
    else {
        // TODO: Check to see if this is the correct way to check epsilon
        if (!matchStmt()) {
            return false;
        }
        return matchStmtList();
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
    if (peekNextToken(true).first != Class) {
        return false;
    }
    cur = getNextToken(file, true);

    if (peekNextToken(true).first != Id) {
        return false;
    }
    cur = getNextToken(file, true);

    if (peekNextToken(false).first != SetStart && peekNextToken(false).first != SetStartNegate) {
        return false;
    }
    cur = getNextToken(file, false);

    if (!matchCItemList()) {
        return false;
    }

    //cur = getNextToken(file, false);

    if (peekNextToken(false).first != SetEnd && peekNextToken(false).first != DashSetEnd) {
        return false;
    }

    cur = getNextToken(file, false);
    return true;
}

bool Parser::matchCItemList() {
    // TODO: Check to see if this is the correct way to accept epsilon
    if (!matchCItem()) {
        //return false;
        return true;
    }
    return matchCItemList();
}

bool Parser::matchCItem() {
    if (peekNextToken(false).first != Character) {
        return false;
    }
    cur = getNextToken(file, false);

    if (peekNextToken(false).first == Dash) {
        cur = getNextToken(file, false);

        if (peekNextToken(false).first != Character) {
            return false;
        }

        cur = getNextToken(file, false);
        return true;
    }
    else {
        return true;
    }
}

bool Parser::matchTokenStmt() {
    if (peekNextToken(true).first != Token) {
        return false;
    }
    cur = getNextToken(file, true);

    if (peekNextToken(true).first != Id) {
        return false;
    }
    cur = getNextToken(file, true);

    if (peekNextToken(false).first != Slash) {
        return false;
    }
    cur = getNextToken(file, false);

    if (!matchRegex()) {
        return false;
    }

    if (peekNextToken(false).first != Slash) {
        return false;
    }
    cur = getNextToken(file, false);

    return true;
}

bool Parser::matchIgnoreStmt(){
    if (peekNextToken(true).first != Ignore) {
        return false;
    }
    cur = getNextToken(file, true);

    if (peekNextToken(false).first != Slash) {
        return false;
    }
    cur = getNextToken(file, false);

    if (!matchRegex()) {
        return false;
    }

    if (peekNextToken(false).first != Slash) {
        return false;
    }
    cur = getNextToken(file, false);

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
        return false;
    }

    if (peekNextToken(false).first == Star || peekNextToken(false).first == Plus || peekNextToken(false).first == Question) {
        cur = getNextToken(file, false);
    }

    return true;
}

bool Parser::matchRFactor() {
    if (peekNextToken(false).first == Character) {
        cur = getNextToken(file, false);
        return true;
    }
    else if (peekNextToken(false).first == SetStart) {
        cur = getNextToken(file, false);

        if (peekNextToken(true).first != Id) {
            return false;
        }
        cur = getNextToken(file, true);

        if (peekNextToken(false).first != SetEnd) {
            return false;
        }
        cur = getNextToken(file, false);

        return true;
    }
    else if (peekNextToken(false).first == OpenParen) {
        cur = getNextToken(file, false);

        if (!matchRegex()) {
            return false;
        }

        if (peekNextToken(false).first != CloseParen) {
            return false;
        }
        cur = getNextToken(file, false);

        return true;
    }
    else {
        return false;
    }
}