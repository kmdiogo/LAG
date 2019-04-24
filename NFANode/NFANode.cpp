#include "NFANode.h"
using namespace std;

void NFANode::printNode() {
    cout << "Edges" << endl;
    for (auto & edge : edges) {
        cout << "\tto: " << edge.transNode << " | " << "char(s): ";
        if (edge.transChars.empty())
            cout << "epsilon" << endl;
        else {
            for (auto & ch : edge.transChars) {
                cout << ch << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}
