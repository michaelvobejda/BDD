#include "BDD.hpp"
#include <iostream>

using namespace std;

int main() {
    BDD x;
    cout << x;
    x.addVariable(1);
    cout << x;
    BDD y;
    y.addVariable(2);
    cout << y;
    x.conjunction(y);
    cout << x;
}
