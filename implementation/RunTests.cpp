#include "BDD.hpp"
#include <iostream>

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

/*void and_five_variables() {
    BDD bdds[5];
    for(size_t i = 2; i < 7; i++) {
        bdds[i](i);
    }
    for(size_t i = 2; i < 6; i++) {
        bdds[2].conjunction(bdds[i+1]);
    }
    cout << bdds[2];
}

void or_same_variable() {
    BDD x;
    x.addVariable(2);
    BDD y;
    y.addVariable(2);
    x.disjunction(y);
    cout << x;
}

void or_same_variable() {
    BDD x;
    x.addVariable(2);
    BDD y;
    y.addVariable(2);
    x.disjunction(y);
    cout << x;
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
    for(size_t i = 2; i < 7; i++) {
        bdds[i].addVariable(i);
    }
    for(size_t i = 2; i < 6; i++) {
        bdds[2].disjunction(bdds[i+1]);
    }
    cout << bdds[2];
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
    cout << w;
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
    cout << w;
}*/

int main() {
//     and_same_variable();
    xor_same_variable();
//     and_different_variables();
    // and_five_variables();
    // or_same_variable();
    // or_different_variables();
    // or_five_variables();
    //or_two_and_BDD();
    // and_two_or_BDD();
}
