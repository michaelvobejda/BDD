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

void and_five_variables() {
  /*  BDD v;
    BDD w;
    BDD x;
    BDD y;
    BDD z;
    v.addVariable(1);
    w.addVariable(2);
    x.addVariable(3);
    y.addVariable(4);
    z.addVariable(5);*/
    BDD bdds[5];
    for(size_t i = 0; i < 5; i++) {
        bdds[i].addVariable(i);
    }
    for(size_t i = 0; i < 4; i++) {
        bdds[0].conjunction(bdds[i+1]);
    }
    cout << bdds[0];
}

int main() {
    //and_same_variable();
//    and_different_variables();
    and_five_variables();
    
}
