#include "BDD.hpp"
#include <iostream>

using namespace std;

void and_same_variable() {
    BDD x;
    x.addVariable(1);
    cout << x;
    BDD y;
    y.addVariable(1);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

void and_different_variables() {
    BDD x;
    x.addVariable(1);
    cout << x;
    BDD y;
    y.addVariable(2);
    cout << y << "conjunction: " << endl;
    x.conjunction(y);
    cout << x;
}

int main() {
    //and_same_variable();
    and_different_variables();
}
