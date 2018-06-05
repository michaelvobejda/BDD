//
//  BDD.cpp
//  Created 6/3/18.
//

#include "BDD.hpp"

using namespace std;

#define ADD 1
#define OR 2

BDD::BDD() {
    numVars = 0;
    //Initialize the BDD by inserting the 0 and 1 terminal nodes.
    Node terminal = {0, 1, 0, NULL, NULL}; //id = 0, var = numVars = 1
    Tree.push_back(terminal);
    terminal.id = 1;
    Tree.push_back(terminal);
}

/* BDD:mk
 Creates a new node. Checks hash table to make sure node doesn't already exist.
 */
Node BDD::mk(size_t var, Node *hi, Node* lo) {
    Node n = {Tree.size(), var, -1, hi , lo, false};
    if(hi == lo) {
        return *lo;
    }
    auto found = H.find(n);
    if(found != H.end()) {
        return found->first;
    }
    Tree.push_back(n);
    H.insert(pair<Node, size_t>(n, Tree.size()));
    return n;
}

int BDD::getSize() {
    return Tree.size();
}

Node BDD::getRoot() {
    Node n;
    return n;
}

int operate(int op, int v1, int v2) {
    /* computes the result of v1 (op) v2 with the rules of three-valued algebra */
    if(op == ADD) { //if op is AND ** to do: add constant for 1
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

Node *BDD::applyHelper(int op, Node u1, Node u2, vector<vector<Node *>>& table) {
    Node *cached = table[u1.id][u2.id];
    if(cached !=  NULL) return cached;
    Node *u = new Node;
    u->marked = false;
    u->value = operate(op, u1.value, u2.value);
    if(u->value != -1) {
        numVars++;
        u->var = numVars;
        u->lo = NULL;
        u->hi = NULL;
        u->id = Tree.size();
        Tree.push_back(*u);
    } else {
        if(u1.var == u2.var) {
            *u = mk(u1.var, applyHelper(op, *(u1.lo), *(u2.lo), table), applyHelper(op, *(u1.hi), *(u2.hi), table));
        } else if(u1.var < u2.var) {
            *u = mk(u1.var, applyHelper(op, *(u1.lo), u2, table), applyHelper(op, *(u1.hi), u2, table));
        } else {
            *u = mk(u2.var, applyHelper(op, u1, *(u2.lo), table), applyHelper(op, u1, *(u2.hi), table));
        }
    }
    table[u1.id][u2.id] = u;
    return u;
}

Node *BDD::apply(int op, BDD b) {
    vector<vector<Node *>> table(getSize(), vector<Node *>(b.getSize(), NULL));
    Node u1 = getRoot();
    Node u2 = b.getRoot();
    //don't forget to free memory from table
    return applyHelper(op, u1, u2, table);
}
