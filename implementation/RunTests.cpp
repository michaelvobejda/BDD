#include "BDD.hpp"
#include <iostream>
#include <fstream>
#include "cereal/archives/binary.hpp"
#include <sstream>

using namespace std;

void and_same_variable() {
    BDD x(2);
    cout << x;
    BDD y(2);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

void and_different_variables() {
    BDD x(2);
    cout << x;
    BDD y(3);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

void xor_same_variable() {
    BDD x(2);
    cout << x;
    BDD y(2);
    cout << y << "xor: " << endl;
    x.eor(y);
    cout << x;
}

void xor_different_variables() {
    BDD x(2);
    cout << x;
    BDD y(3);
    cout << y << "xor: " << endl;
    x.eor(y);
    cout << x;
}

void xor_five_variables() {
    vector<BDD> bdds;
    for(size_t i = 0; i < 5; i++) {
        bdds.push_back(BDD(i+2));
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].eor(bdds[i+1]);
    }
    cout << bdds[0];
}

void and_five_variables() {
    vector<BDD> bdds;
    for(size_t i = 0; i < 5; i++) {
        bdds.push_back(BDD(i+2));
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].conjunction(bdds[i+1]);
    }
//     cout << bdds[0];

    // Iterate over an unordered_map using range based for loop
    for (pair<size_t, bool> element : bdds[0].solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }

}

void or_same_variable() {
    BDD x(2);
    BDD y(2);
    x.disjunction(y);
    cout << x;
}



void or_different_variables() {
    BDD x(2);
    BDD y(3);
    x.disjunction(y);
    cout << x;
}

void or_five_variables() {
    vector<BDD> bdds;
    for(size_t i = 0; i < 5; i++) {
        bdds.push_back(BDD(i+2));
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].disjunction(bdds[i+1]);
    }
     cout << bdds[0];

    // Iterate over an unordered_map using range based for loop
  /*  for (pair<size_t, bool> element : bdds[0].solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }*/
}

void or_two_and_BDD() {
    BDD w(2);
    BDD x(3);
    w.conjunction(x);

    BDD y(4);
    BDD z(5);
    y.conjunction(z);
    w.disjunction(y);
     cout << w;

    // Iterate over an unordered_map using range based for loop
   /* for (pair<size_t, bool> element : w.solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }*/
}

/*void and_two_or_BDD() {
    BDD w;
    w.addVariable(2);
    BDD x;
    x.addVariable(3);
    w.disjunction(x);

    BDD y;
    y.addVariable(4);
    BDD z;
    z.addVariable(5);
    y.disjunction(z);

    w.conjunction(y);
    cout << w;
}*/

void and_time_test() {
    BDD x(111);
    BDD y(121);
    x.eor(y);
    cout << x << endl;
    
    BDD a(111);
    BDD b(112);
    a.eor(b);
    cout << a << endl;
}

bool bddComp (BDD i, BDD j) {
    return (i.root)->var < (j.root)->var; }

int main() {
//     and_same_variable();
//    xor_same_variable();
//    xor_different_variables();
//    xor_five_variables();
//     and_different_variables();
//     and_five_variables();
//     or_same_variable();
//     or_different_variables();
//     or_five_variables();
//    or_two_and_BDD();
    // cout << w;
    //and_time_test();
    
    // ******* Sudoku equations ********
    int variableName;
    int variableNameBase;
    // Rule 1: Every square has exactly one digit in it
    BDD rule1;
    bool first = true;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            variableNameBase = 100*i + 10*j;
            // For a given spot (i, j), 1 variable per value of k
            //bdds = BDD[10]; // 0th index will be empty
            vector<BDD> bdds;
            for (int k = 1; k <= 9; k++) {
                variableName = variableNameBase + k;
                bdds.push_back(BDD(variableName));
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
            }

            // And it with the others
            if (first) {
                rule1 = bdds[0];
                first = false;
            } else {
                rule1.conjunction(bdds[0]);
            }
        }
    }
    cout << "Rule 1: done" << endl;
    
    // Rule 2: Every row contains 1-9 exactly once
    BDD rule2;
    first = true;
    vector<BDD> rows;
    for (int i = 1; i <= 9; i++) {
        for (int k = 1; k <= 9; k++) {
            variableNameBase = 100*i + k;
            // For a given row i and digit k, one variable per row entry
            vector<BDD> bdds;
            variableName = variableNameBase;
            for (int j = 1; j <= 9; j++) {
                variableName += 10;
                bdds.push_back(BDD(variableName));
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
                
            }
            rows.push_back(bdds[0]);
            // And it with the others
//            if (first) {
//                rule2 = bdds[0];
//                first = false;
//            } else {
//                rule2.conjunction(bdds[0]);
//            }
        }
    }
    
    sort(rows.begin(), rows.end(), bddComp);
    for(size_t i = 0; i < rows.size(); i++) {
        rule2.conjunction(rows[i]);
    }
    cout << "Rule 2: done" << endl;
    
    // Rule 3: Every column contains 1-9 exactly once
    BDD rule3;
    first = true;
    for (int j = 1; j <= 9; j++) {
        for (int k = 1; k <= 9; k++) {
            // variableName = int(to_string(i));
            // For a given row i and digit k, one variable per row entry
            //bdds = BDD[10]; // 0th index will be empty
            vector<BDD> bdds;
            for (int i = 1; i <= 9; i++) {
                variableName = 100*i + 10*j + k;
                bdds.push_back(BDD(variableName));
                //bdds[i].addVariable(variableName);
            }
            // XOR all 9 variables
            for (int c = 1; c < 9; c++) {
                bdds[0].eor(bdds[c]);
            }
            
            // And it with the others
            if (first) {
                rule3 = bdds[0];
                first = false;
            } else {
                rule3.conjunction(bdds[0]);
            }
        }
    }
    
    cout << "Rule 3: done" << endl;
    
    // Rule 4: 3x3 grid contains 1-9 exactly once
    BDD rule4;
    first = true;
    for (int start_row = 1; start_row <= 7; start_row += 3) { // 1, 4, 7
        for (int start_col = 1; start_col <= 7; start_col += 3) { // 1, 4, 7
            // Iterate along 3x3 grid starting at (start_row, start_col)
            for (int i = start_row; i < start_row + 3; i++) {
                for (int j = start_col; j < start_col + 3; j++) {
                    // For a given spot (i, j), one variable per digit k
                    //bdds = BDD[10]; // 0th index will be empty
                    vector<BDD> bdds;
                    for (int k = 1; k <= 9; k++) {
                        variableName = 100*i + 10*j + k;
                        bdds.push_back(BDD(variableName));
                        //bdds[i].addVariable(variableName);
                    }
                    // XOR all 9 variables
                    for (int c = 1; c < 9; c++) {
                        bdds[0].eor(bdds[c]);
                    }
                    
                    // And it with the others
                    if (first) {
                        rule4 = bdds[0];
                        first = false;
                    } else {
                        rule4.conjunction(bdds[0]);
                    }
                }
            }
        }
    }
    cout << "Rule 4: done" << endl;
    
    
    
    // And together the 4 rules
    BDD allRules = rule1;
    allRules.conjunction(rule2);
    allRules.conjunction(rule3);
    allRules.conjunction(rule4);
    
    cout << "Enter sudoku string." << endl;
    string sudoku;
    getline(cin, sudoku);
    
    for(size_t i = 0; i < sudoku.length(); i++) {
        if(sudoku[i] != '.') {
            int row = i/10;
            int col = i%10;
            int val = sudoku[i];
            int variableName = 100*row + 10*col + val;
            allRules.conjunction(BDD(variableName));
        }
    }
    
    unordered_map<size_t, bool> assignments = allRules.solveOne();

    string boardString = "";
    vector<int> board(81);
    for (pair<size_t, bool> element : assignments) {
        int var = element.first;
        int row = var / 100;
        int col = (var / 10) % 10;
        int val = var % 10;
        board[row * 9 + col] = val;
    }
        
    for (int i = 0; i < 81; i++) {
        boardString += to_string(board[i]);
        if ( ((i+1)%9) == 0) {
            boardString += "|";
        }
    }
    cout << boardString;
}


