#include "BDD.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Rule 1: Every square has exactly one digit in it
    String variableName = "";
    BDD rule1;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            variableName = int(str(i) + str(j));
            // For a given spot (i, j), 1 variable per value of k
            //bdds = BDD[10]; // 0th index will be empty
            Vector<BDD> bdds;
            for (int k = 1; k <= 9; k++) {
                variableName = int(str(variableName) + str(k))
                bdds.push_back(BDD(variableName));
                //bdds[i].addVariable(variableName);
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

    // Rule 2: Every row contains 1-9 exactly once
    BDD rule2;
    for (int i = 1; i <= 9; i++) {
        for (int k = 1; k <= 9; k++) {
            variableName = int(str(i));
            // For a given row i and digit k, one variable per row entry
            //bdds = BDD[10]; // 0th index will be empty
            Vector<BDD> bdds;
            for (int j = 1; j <= 9; j++) {
                variableName = int(str(variableName) + str(j) + str(k));
                //bdds[i].addVariable(variableName);
                bdds.push_back(BDD(variableName));
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
            }

            // And it with the others
            if (rule2 == null) {
                rule2 = bdds[0];
            } else {
                rule2.conjunction(bdds[0]);
            }
        }
    }

    // Rule 3: Every column contains 1-9 exactly once
    BDD rule3;
    for (int j = 1; j <= 9; j++) {
        for (int k = 1; k <= 9; k++) {
            // variableName = int(str(i));
            // For a given row i and digit k, one variable per row entry
            //bdds = BDD[10]; // 0th index will be empty
            Vector<BDD> bdds;
            for (int i = 1; i <= 9; i++) {
                variableName = int(str(i) + str(j) + str(k));
                bdds.push_back(BDD(variableName));
                //bdds[i].addVariable(variableName);
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
            }

            // And it with the others
            if (rule3 == null) {
                rule3 = bdds[0];
            } else {
                rule3.conjunction(bdds[0]);
            }
        }
    }

    // Rule 4: 3x3 grid contains 1-9 exactly once
    BDD rule4;
    for (int start_row = 1; start_row <= 7; start_row += 3) { // 1, 4, 7
        for (int start_col = 1; start_col <= 7; start_col += 3) { // 1, 4, 7
            // Iterate along 3x3 grid starting at (start_row, start_col)
            for (int i = start_row; i < start_row + 3; i++) {
                for (int j = start_col; j < start_col + 3; j++) {
                    // For a given spot (i, j), one variable per digit k
                    //bdds = BDD[10]; // 0th index will be empty
                    Vector<BDD> bdds;
                    for (int k = 1; k <= 9; k++) {
                        variableName = int(str(i) + str(j) + str(k));
                        bdds.push_back(BDD(variableName));
                        //bdds[i].addVariable(variableName);
                    }
                    // XOR all 9 variables
                    for (int c = 1; c < 9; c++) {
                        bdds[0].eor(bdds[c]);
                    }

                    // And it with the others
                    if (rule4 == null) {
                        rule4 = bdds[0];
                    } else {
                        rule4.conjunction(bdds[0]);
                    }
                }
            }
        }
    }

    // And together the 4 rules
    BDD allRules = rule1;
    allRules.conjunction(rule2);
    allRules.conjunction(rule3);
    allRules.conjunction(rule4);

    return allRules;
}
