//
// Created by Kenny on 4/24/2019.
//

#include "DFAGenerator.h"

vector<int> DFAGenerator::eClosure(vector<int> state) {
    vector<int> transStates;
    for (auto & nodeNum : state) {
        transStates.emplace_back(nodeNum);
        for (auto & edge : NFA[nodeNum].edges) {
            if (edge.transChars.empty()) {
                vector<int> closureOfNextNode = eClosure(vector<int>{edge.transNode});
                transStates.insert(transStates.end(), closureOfNextNode.begin(), closureOfNextNode.end());
            }
        }
    }
    return transStates;
}

vector<int> DFAGenerator::move(vector<int> state, vector<char> input) {
    vector<int> moveStates;
    for (auto & nodeNum : state) {
        for (auto & edge : NFA[nodeNum].edges) {
            if (edge.transChars == input) {
                moveStates.emplace_back(edge.transNode);
            }
        }
    }
    return moveStates;
}

void DFAGenerator::generateDFA() {
    int numberOfStates = 0;
    vector<int> initialState = eClosure(vector<int>{0});
    startingState = initialState;
    DFATable[initialState];
    acceptingStates[initialState] = "Start";
    stateAliases[initialState] = numberOfStates;
    numberOfStates++;

    for (auto & statePair : DFATable) {
        for (auto & input : inputs) {
            vector<int> nextState = eClosure(move(statePair.first, input));
            DFATable[statePair.first][input] = nextState;
            if (DFATable.find(nextState) == DFATable.end() && !nextState.empty()) {
                string dfaStateAcceptingTokenName = IsDFAStateAccepting(nextState);
                if (dfaStateAcceptingTokenName != "") {
                    acceptingStates[nextState] = dfaStateAcceptingTokenName;
                }
                stateAliases[nextState] = numberOfStates;
                numberOfStates++;
                DFATable[nextState];
            }
        }
    }
}

void DFAGenerator::printDFA() {
    cout << "--- INPUTS ---" << endl;
    for (auto & input : inputs) {
        for (auto & ch : input) {
            cout << ch << " ";
        }
        cout << endl;
    }
    cout << "-------------" << endl;

    cout << "--- TRANSITION TABLE ---" << endl;


    for (auto & statePair : DFATable) {
        cout << "State: {";
        /*for (auto & ch : statePair.first) {
            cout << ch << ",";
        }*/
        cout << stateAliases[statePair.first];
        cout << "}" << "\t";


        for (auto & input : inputs) {
            cout << "Input [";
            for (auto & ch : input) {
                cout << ch << ",";
            }
            cout << "]: ";

            cout << "{";
            /*for (auto & stateNum : DFATable[statePair.first][input]) {
                cout << stateNum << ",";
            }*/
            cout << stateAliases[DFATable[statePair.first][input]];
            cout << "} | ";

        }

        cout << endl << endl;
    }

    cout << "----------------" << endl;
}

string DFAGenerator::IsDFAStateAccepting(vector<int> DFAState) {
    for (auto & stateNum : DFAState) {
        if (NFA[stateNum].isAccepting)
            return NFA[stateNum].tokenName;
    }
    return "";
}

void DFAGenerator::simulateDFA(string input) {
    vector<int> currentState = startingState;
    for (auto & ch : input) {
        // Check if character in any transitions
        for (auto & inputEdge : DFATable[currentState]) {
            for (auto & inputChar : inputEdge.first) {
                if (ch == inputChar) {
                    if (inputEdge.second.empty()) {
                        goto afterLoop;
                    }
                    currentState = inputEdge.second;
                    break;
                }
            }
        }
    }
    afterLoop:
    cout << "{";
    for (auto & x : currentState) {
        cout << x << ",";
    }
    cout << "}" << endl;
    if (acceptingStates.find(currentState) != acceptingStates.end()) {
        cout << "Token: " << acceptingStates[currentState] << endl;
    } else {
        cout << "Invalid input string" << endl;
    }
}