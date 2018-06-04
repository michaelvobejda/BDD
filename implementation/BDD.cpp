//
//  BDD.cpp
//  
//
//  Created 6/3/18.
//

#include "BDD.hpp"

using namespace std;

BDD::BDD() {
    numVars = 0;
    //Add 0 and 1 terminal nodes
    Node terminal;
    terminal.var = 0;
    terminal.hi = NULL;
    terminal.lo = NULL;
    T.push_back(terminal);
    terminal.var = 1;
    T.push_back(terminal);
}
