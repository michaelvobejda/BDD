#include "BDD.hpp"
#include <iostream>

using namespace std;

void and_same_variable() {
    BDD x;
    x.addVariable(2);
    cout << x;
    BDD y;
    y.addVariable(2);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

int main() {
    // Rule 1: Every square has exactly one digit in it
    String variableName = "";
    BDD rule1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            variableName = str(i) + str(j);
            // For a given spot (i, j), 1 variable per value of k
            bdds = BDD[9];
            for (int k = 0; k < 9; k++) {
                variableName += str(k)
                bdds[i].addVariable(variableName);
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
            }

            // And it with the others
            if (rule1 == null) {
                rule1 = bdds[0];
            } else {
                rule1.conjunction(bdds[0]);
            }
        }
    }

    

}
