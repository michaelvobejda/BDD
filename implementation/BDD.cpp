//
//  BDD.cpp
//  Created 6/3/18.
//

#include "BDD.hpp"
#include <iostream>
#include <climits>

using namespace std;

#define AND 1
#define OR 2

BDD::BDD() {
    numVars = 0;
    //Initialize the BDD by inserting the 0 and 1 terminal nodes.
    Node *terminal0 = new Node;
    //terminal0->var = INT_MAX;
    Tree.push_back(terminal0);
    Node *terminal1 = new Node;
    terminal1->id = 1;
    terminal1->value = 1;
    //terminal1->var = INT_MAX;
    Tree.push_back(terminal1);
    H.insert(pair<Node, size_t>(*terminal0, 0));
    H.insert(pair<Node, size_t>(*terminal1, 1));
}

//to do: implement deconstructor to free all allocated memory
BDD::~BDD() {
    
}

ostream& operator<<(ostream& os, const BDD& bdd) {
    for(size_t i = 0; i < bdd.Tree.size(); i++) {
        os << "Var: " << bdd.Tree[i]->var <<  ", Value: " << bdd.Tree[i]->value << '\n';
    }
    os << "num vars " << bdd.numVars << '\n';
    return os;
}

/*
 * Public Functions
 */
Node* BDD::conjunction(class BDD b) {
    return apply(AND, b);
}

Node* BDD::disjunction(class BDD b) {
    return apply(OR, b);
}

void BDD::addVariable(int num) {
    //adds variable with index num. changes terminals to make sure they are last in variable ordering.
    mk(num, Tree[1], Tree[0]);
}


/*
 * Private functions
 */

/* BDD:mk
 Creates a new node. Checks hash table to make sure node doesn't already exist.
 */
Node *BDD::mk(size_t var, Node *hi, Node* lo) {
//    if(var > numVars) {
//        numVars = var + 1;
//        Tree[1]->var = numVars;
//        Tree[0]->var = numVars;
//    }
    Node *n = new Node;
    n->id = Tree.size();
    n->var = var;
    n->value = -1;
    n->hi = hi;
    n->lo = lo;
    if(hi == lo) {
        return lo;
    }
    auto found = H.find(*n);
    if(found != H.end()) {
        //free(n);
        return Tree[found->second];
    }
    Tree.push_back(n);
    H.insert(pair<Node, size_t>(*n, Tree.size()-1));

    return n;
}

int BDD::getSize() {
    return Tree.size();
}

Node BDD::getRoot() {
    return *Tree[Tree.size()-1];
}

int operate(int op, int v1, int v2) {
    /* computes the result of v1 (op) v2 with the rules of three-valued algebra */
    if(op == AND) { //if op is AND ** to do: add constant for 1
        if(v1 == -1 && v2 == -1) {
            return -1;
        } else if(v1 == -1) {
            if(v2 == 0) return 0;
            else return -1;
        } else if(v2 == -1) {
            if(v1 == 0) return 0;
            else return -1;
        } else {
            return v1 & v2;
        }
    } else if(op == OR) {
        if(v1 == -1 && v2 == -1) {
            return -1;
        } else if(v1 == -1) {
            if(v2 == 1) return 1;
            else return -1;
        } else if(v2 == -1) {
            if(v1 == 1) return 1;
            else return -1;
        } else {
            return v1 | v2;
        }
    }
    return -1;
}

/* Applies a binary operation to two BDDs using dynamic programming */
Node *BDD::apply(int op, BDD b) {
    vector<vector<Node *>> table(getSize(), vector<Node *>(b.getSize(), NULL));
    Node u1 = getRoot();
    Node u2 = b.getRoot();
    return applyHelper(op, u1, u2, table);
}

Node *BDD::applyHelper(int op, Node u1, Node u2, vector<vector<Node *>>& table) {
    Node *memo = table[u1.id][u2.id];
    if(memo) return memo;
//    Node *u;
//    int result = operate(op, u1.value, u2.value); //apply operation to node values to check if they're both terminal
//    if(result != -1) {
//        u = new Node;
////        numVars++; //make sure this step is correct
//        u->value = result;
//        u->id = result;
//        //free Tree[u->value];
//        Tree[result] = u;
//        Tree[0]->var = numVars + 1;
//        Tree[1]->var = numVars + 1;
    Node * u;
    if(u1.value >= 0 && u2.value >= 0) {
//        u = new Node;
        int result = operate(op, u1.value, u2.value);
//        Tree[result]->value = result;
        u = Tree[result];
//        u->value = result;
//        u->id = result;
//        u->var = numVars;
//        Tree[0]->var = numVars + 1;
//        Tree[1]->var = numVars + 1;
    } else {
        if(u1.var == u2.var) {
            u = mk(u1.var, applyHelper(op, *(u1.lo), *(u2.lo), table), applyHelper(op, *(u1.hi), *(u2.hi), table));
        } else if(u1.var < u2.var) {
            u = mk(u1.var, applyHelper(op, *(u1.lo), u2, table), applyHelper(op, *(u1.hi), u2, table));
        } else {
            u = mk(u2.var, applyHelper(op, u1, *(u2.lo), table), applyHelper(op, u1, *(u2.hi), table));
        }
    }
    table[u1.id][u2.id] = u;
    return u;
}
