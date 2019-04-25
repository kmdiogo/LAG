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