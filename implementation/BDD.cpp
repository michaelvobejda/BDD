//
//  BDD.cpp
//  
//
//  Created 6/3/18.
//

#include "BDD.hpp"

using namespace std;

BDD::BDD() {
    //Initialize the BDD by inserting the 0 and 1 terminal nodes.
    numVars = 1;
    Node terminal = {numVars, NULL, NULL};
    T.push_back(terminal);
    T.push_back(terminal);
}

Node BDD::mk(size_t var, Node *hi, Node* lo) {
    Node n = {var, hi , lo};
    if(hi == lo) {
        return *lo;
//    } else if(H.find(n) == H.end()) {
        
    } else {
   
    }
    return n;
}
