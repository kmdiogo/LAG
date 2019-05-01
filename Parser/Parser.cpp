//
// Created by Kenny on 4/12/2019.
//

#include "Parser.h"
// TODO: Build parse tree

ParseTreeNode lastNode;
string currentClass;

pair<Tokens, string> Parser::peekNextToken(bool aggregrate) {
    int startPos = file.tellg();

    pair<Tokens, string> p = getNextToken(file, aggregrate);
    file.seekg(startPos, file.beg);

    return p;
}

void Parser::printParseTrees() {
    for (int i =0; i < parseTrees.size(); i++) {
        cout << "------- Parse Tree " << i << " ---------" << endl;
        for (auto & j : parseTrees[i]) {
            j.printNode();
        }
    }
    cout << "--------- END -----------" << endl;
}

vector<char> Parser::handleCharRange(char begin, char end) {
    vector<char> classChars;
    if (begin > end) {
        cout << "Given character range: [" << begin << " - " << end << "] is invalid" << endl;
        exit(0);
    }
    for (int i=begin; i <= end; i++) {
        classChars.emplace_back(char(i));
    }
    return classChars;
}


void Parser::parse() {
    if (matchStmtList())
        cout << "Parse Successful" << endl;
    else {
        cout << "Parse Unsuccessful" << endl;
        cout << "Last Consumed Token: ";
        printPair(cur);

        cout << "Lookahead Token: ";
        printPair(peekNextToken(false));
        exit(0);
    }
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
    currentClass = cur.second;
    classLookupTable[currentClass] = vector<char>();

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

    classLookupTable[currentClass];
    if (peekNextToken(false).first == Dash) {
        // Save the first character in the range
        char begin = cur.second[0];

        cur = getNextToken(file, false);

        if (peekNextToken(false).first != Character) {
            return false;
        }

        cur = getNextToken(file, false);

        // Save the last character in the range
        char end = cur.second[0];
        for (auto & ch : handleCharRange(begin, end)) {
            classLookupTable[currentClass].emplace_back(ch);
        }
        //classLookupTable[currentClass].emplace_back(handleCharRange(begin, end));
        return true;
    }
    else {
        classLookupTable[currentClass].emplace_back(cur.second[0]);
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
    tokenNames.emplace_back(cur.second);

    if (peekNextToken(false).first != Slash) {
        return false;
    }
    cur = getNextToken(file, false);

    parseTrees.emplace_back(vector<ParseTreeNode>());
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

    parseTrees.emplace_back(vector<ParseTreeNode>());
    tokenNames.emplace_back("ignore");
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

    while (peekNextToken(false).first == Pipe) {
        ParseTreeNode node = ParseTreeNode(UnionNode);
        node.left = lastNode.index;

        cur = getNextToken(file, false);
        if (!matchRTerm()) {
            return false;
        }

        node.right = lastNode.index;
        node.index = parseTrees.back().size();
        parseTrees.back().emplace_back(node);
        lastNode = node;
    }

    return true;
}

bool Parser::matchRTerm() {
    if (!matchRClosure()) {
        return false;
    }
    ParseTreeNode leftNode = lastNode;

    while(matchRClosure()) {
        ParseTreeNode node = ParseTreeNode(ConcatNode);
        node.index = parseTrees.back().size();
        node.left = leftNode.index;
        node.right = lastNode.index;
        parseTrees.back().emplace_back(node);
        lastNode = node;
        leftNode = lastNode;
    }

    return true;
}

bool Parser::matchRClosure() {
    if (!matchRFactor()) {
        return false;
    }

    if (peekNextToken(false).first == Star) {
        cur = getNextToken(file, false);
        ParseTreeNode node = ParseTreeNode(StarNode);
        node.index = parseTrees.back().size();
        node.left = lastNode.index;
        parseTrees.back().emplace_back(node);
        lastNode = node;
    }
    else if (peekNextToken(false).first == Plus) {
        cur = getNextToken(file, false);
        ParseTreeNode node = ParseTreeNode(PlusNode);
        node.index = parseTrees.back().size();
        node.left = lastNode.index;
        parseTrees.back().emplace_back(node);
        lastNode = node;
    }
    else if (peekNextToken(false).first == Question) {
        cur = getNextToken(file, false);
        ParseTreeNode node = ParseTreeNode(QuestionNode);
        node.index = parseTrees.back().size();
        node.left = lastNode.index;
        parseTrees.back().emplace_back(node);
        lastNode = node;
    }

    return true;
}

bool Parser::matchRFactor() {
    if (peekNextToken(false).first == Character) {
        cur = getNextToken(file, false);

        lastNode = ParseTreeNode(CharacterNode, cur.second);
        lastNode.index = parseTrees.back().size();
        parseTrees.back().emplace_back(lastNode);

        return true;
    }
    else if (peekNextToken(false).first == SetStart) {
        cur = getNextToken(file, false);

        if (peekNextToken(true).first != Id) {
            return false;
        }
        cur = getNextToken(file, true);

        if (classLookupTable.find(cur.second) == classLookupTable.end()) {
            cout << "Error: class set: " << cur.second << " has not been defined" << endl;
            exit(0);
        }
        lastNode = ParseTreeNode(IdNode, cur.second);
        lastNode.index = parseTrees.back().size();
        parseTrees.back().emplace_back(lastNode);

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