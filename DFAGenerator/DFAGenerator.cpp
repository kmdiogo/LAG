//
// Created by Kenny on 4/24/2019.
//

#include "DFAGenerator.h"

set<int> DFAGenerator::eClosure(set<int> state) {
    set<int> transStates;
    for (auto & nodeNum : state) {
        transStates.insert(nodeNum);
        for (auto & edge : NFA[nodeNum].edges) {
            if (edge.transChars.empty()) {
                set<int> closureOfNextNode = eClosure(set<int>{edge.transNode});
                transStates.insert(closureOfNextNode.begin(), closureOfNextNode.end());
            }
        }
    }
    return transStates;
}

set<int> DFAGenerator::move(set<int> state, vector<char> input) {
    set<int> moveStates;
    for (auto & nodeNum : state) {
        for (auto & edge : NFA[nodeNum].edges) {
            if (edge.transChars == input) {
                moveStates.insert(edge.transNode);
            }
        }

    }
    return moveStates;
}

void DFAGenerator::generateDFA() {
    int nextStateAlias = 0;
    set<int> initialState = eClosure(set<int>{0});
    startingState = initialState;
    DFATable[initialState];
    stateAliases[initialState] = nextStateAlias;
    nextStateAlias++;

    queue<set<int>> newStateQueue;
    newStateQueue.push(initialState);
    while (!newStateQueue.empty()){
        set<int> curState = newStateQueue.front();
        for (auto & input : inputs) {
            set<int> moveOnState = move(curState, input);
            set<int> nextState = eClosure(moveOnState);
            DFATable[curState][input] = nextState;
            if (DFATable.find(nextState) == DFATable.end() && !nextState.empty()) {
                string dfaStateAcceptingTokenName = IsDFAStateAccepting(nextState);
                if (!dfaStateAcceptingTokenName.empty()) {
                    acceptingStates[nextState] = dfaStateAcceptingTokenName;
                }
                stateAliases[nextState] = nextStateAlias;
                nextStateAlias++;
                DFATable[nextState];
                newStateQueue.push(nextState);
            }
        }
        newStateQueue.pop();
    }

    //}


    for (auto & statePair : DFATable) {
        DFATableSimplified.emplace_back(map<vector<char>,int>());
    }
    for (auto & statePair : DFATable) {
        map<vector<char>, int> stateMap;
        for (auto & edgePair : statePair.second) {
            if (!edgePair.second.empty())
                stateMap[edgePair.first] = stateAliases[edgePair.second];
            else
                stateMap[edgePair.first] = -1;
        }
        DFATableSimplified[stateAliases[statePair.first]] = stateMap;
    }


    for (auto & statePair : acceptingStates) {
        acceptingStateSimplified[stateAliases[statePair.first]] = statePair.second;
    }

}

void DFAGenerator::printDFA() {
    cout << "--- TRANSITION TABLE ---" << endl;


    for (auto & statePair : DFATable) {
        cout << "State: {";
        for (auto & ch : statePair.first) {
            cout << ch << ",";
        }
        cout << "}" << "\t";


        for (auto & input : inputs) {
            cout << "Input [";
            for (auto & ch : input) {
                cout << ch << ",";
            }
            cout << "]: ";

            cout << "{";
            for (auto & stateNum : DFATable[statePair.first][input]) {
                cout << stateNum << ",";
            }
            cout << "} | ";

        }

        cout << endl << endl;
    }

    cout << "----------------" << endl;
}

void DFAGenerator::printSimpleDFA() {
    cout << "--- TRANSITION TABLE ---" << endl;


    for (int i=0; i < DFATableSimplified.size(); i++) {
        cout << "State: {";
        cout << i;
        cout << "}" << "\t";


        for (auto & input : inputs) {
            cout << "Input [";
            for (auto & ch : input) {
                cout << ch << ",";
            }
            cout << "]: ";

            cout << "{";
            cout << DFATableSimplified[i][input];

            cout << "} | ";

        }

        cout << endl << endl;
    }

    cout << "----------------" << endl;
}

string DFAGenerator::IsDFAStateAccepting(set<int> DFAState) {
    for (auto & stateNum : DFAState) {
        if (NFA[stateNum].isAccepting)
            return NFA[stateNum].tokenName;
    }
    return "";
}

void DFAGenerator::simulateDFA(string input) {
    /*vector<int> currentState = startingState;
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
    }*/
}