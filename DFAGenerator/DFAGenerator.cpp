//
// Created by Kenny on 4/24/2019.
//

#include "DFAGenerator.h"

vector<int> DFAGenerator::eClosure(vector<int> state) {
    vector<int> transStates;
    for (auto & nodeNum : state) {
        transStates.emplace_back(nodeNum);
        if (NFA[nodeNum].edges.empty()) {
            for (auto & nodeNum2 : eClosure(vector<int>{nodeNum})) {
                transStates.emplace_back(nodeNum2);
            }
        }
    }
    return transStates;
}

void DFAGenerator::move(vector<int> state, vector<char> input) {

}