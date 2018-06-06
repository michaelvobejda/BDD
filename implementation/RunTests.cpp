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

void and_different_variables() {
    BDD x;
    x.addVariable(2);
    cout << x;
    BDD y;
    y.addVariable(2);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

void and_five_variables() {
    BDD bdds[5];
    for(size_t i = 0; i < 5; i++) {
        bdds[i].addVariable(i+2);
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].conjunction(bdds[i+1]);
    }
    // cout << bdds[2];

    // Iterate over an unordered_map using range based for loop
    for (pair<size_t, bool> element : bdds[0].solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }

}

void or_same_variable() {
    BDD x;
    x.addVariable(2);
    BDD y;
    y.addVariable(2);
    x.disjunction(y);
    cout << x;
}

void or_different_variables() {
    BDD x;
    x.addVariable(2);
    BDD y;
    y.addVariable(3);
    x.disjunction(y);
    cout << x;
}

void or_five_variables() {
    BDD bdds[5];
    for(size_t i = 0; i < 5; i++) {
        bdds[i].addVariable(i+2);
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].disjunction(bdds[i+1]);
    }
    // cout << bdds[2];

    // Iterate over an unordered_map using range based for loop
    for (pair<size_t, bool> element : bdds[0].solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }
}

void or_two_and_BDD() {
    BDD w;
    w.addVariable(2);
    BDD x;
    x.addVariable(3);
    w.conjunction(x);

    BDD y;
    y.addVariable(4);
    BDD z;
    z.addVariable(5);
    y.conjunction(z);

    w.disjunction(y);
    // cout << w;

    // Iterate over an unordered_map using range based for loop
    for (pair<size_t, bool> element : w.solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }
}

void and_two_or_BDD() {
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
    // cout << w;

    // Iterate over an unordered_map using range based for loop
    for (pair<size_t, bool> element : w.solveOne()) {
        cout << element.first << " :: " << element.second << endl;
    }


}

int main() {
    // and_same_variable();
    // and_different_variables();
    and_five_variables();
    // or_same_variable();
    // or_different_variables();
    // or_five_variables();
    // or_two_and_BDD();
    // and_two_or_BDD();
}
