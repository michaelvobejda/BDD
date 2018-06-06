//
//  BDD.cpp
//  Created 6/3/18.
//

// TODO:
// - remove numVars as a variable

#include "BDD.hpp"
#include <iostream>
#include <climits>

using namespace std;

#define AND 1
#define OR 2
#define XOR 3

BDD::BDD() {
    
}
BDD::BDD(int num) {
    isNegated = 0;
    //Initialize the BDD by inserting the 0 and 1 terminal nodes.
    Node *terminal0 = new Node;
    terminal0->var = INT_MAX;
    Tree.push_back(terminal0);
    Node *terminal1 = new Node;
    terminal1->id = 1;
    terminal1->value = 1;
    terminal1->var = INT_MAX;
    Tree.push_back(terminal1);
    H.insert(pair<Node, size_t>(*terminal0, 0));
    H.insert(pair<Node, size_t>(*terminal1, 1));
    root = mk(num, Tree[isNegated], Tree[!isNegated]);
}



//to do: implement deconstructor to free all allocated memory
BDD::~BDD() {
    
}

ostream& operator<<(ostream& os, const BDD& bdd) {
 /*   for(size_t i = 0; i < Tree.size(); i++) {
        Node n = *bdd.Tree[i];
        os << n->id << " " << n->value << " " << n->var << " " << (n->hi)->id << " " << (n->lo)->id << " ";
    }
//    os << bdd.Tree.toString() << " ";
    os << bdd.root << " ";
    return os;
    
    for(size_t i = 0; i < bdd.Tree.size(); i++) {
        int hi = bdd.Tree[i]->hi ? (bdd.Tree[i]->hi)->var : -1;
        int lo = bdd.Tree[i]->lo ? (bdd.Tree[i]->lo)->var : -1;
        if (hi == INT_MAX) hi = (bdd.Tree[i]->hi)->value;
        if (lo == INT_MAX) lo = (bdd.Tree[i]->lo)->value;
        os << "Var: " << bdd.Tree[i]->var <<  ", Value: " << bdd.Tree[i]->value <<
        ", hi: " << hi << ", low: " << lo << '\n';
    }*/
    return os;
}

/*istream& operator<<(istream& is, const BDD& bdd) {
    Node n;
    is >> bdd.Tree;
    is >> bdd.root;
    return is;
}*/

/*
 * Public Functions
 */
Node* BDD::conjunction(class BDD b) {
    return apply(AND, b);
}

Node* BDD::disjunction(class BDD b) {
    return apply(OR, b);
}

Node* BDD::eor(class BDD b) {
    return apply(XOR, b);
}

void BDD::negate() {
    isNegated = !isNegated;
}

/*
 * Private functions
 */

/* BDD:mk
 Creates a new node. Checks hash table to make sure node doesn't already exist.
 */
Node *BDD::mk(size_t var, Node *lo, Node* hi) {
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
        return Tree[found->second];
    }
    Tree.push_back(n);
    H.insert(pair<Node, size_t>(*n, Tree.size()-1));

    return n;
}

int BDD::getSize() {
    return Tree.size();
}

Node *BDD::getRoot() {
    return root;
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
    } else if(op == XOR) {
        if(v1 == -1 || v2 == -1) {
            return -1;
        } else {
            return (v1+v2)%2;
        }
    }
    return -1;
}

/* Applies a binary operation to two BDDs using dynamic programming */
Node *BDD::apply(int op, BDD b) {
    vector<vector<Node *>> table(getSize(), vector<Node *>(b.getSize(), NULL));
    Node u1 = *getRoot();
    Node u2 = *(b.getRoot());
    Node* returnVal = applyHelper(op, u1, u2, table);
    root = returnVal;
    return returnVal;
}

Node *BDD::applyHelper(int op, Node u1, Node u2, vector<vector<Node *>>& table) {
    try {
    Node *memo = table.at(u1.id).at(u2.id);
    if(memo) return memo;
    } catch(exception e) {
        
    }
    Node * u;
    int result = operate(op, u1.value, u2.value);
    if (result != -1) { // result is a terminal
        if(!isNegated) {
            u = Tree[result];
        } else {
            u = Tree[1-result];
        }
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

bool BDD::solveOneHelper(Node *cur) {
    if (!cur) {
        return false;
    }
    cout << "root var: " << cur->var << endl;
    cout << "assignments: " << endl;
    for (pair<size_t, bool> element : assignments) {
        cout << element.first << " :: " << element.second << endl;
    }

    if (!cur->lo && !cur->hi) {
        return cur->value; // if terminal, return value (0 or 1)
    }
    if (solveOneHelper(cur->lo)) {
        cout << "lo returned true" << endl;
        assignments[(cur->var)] = false;
        return true;
    }
    if (solveOneHelper(cur->hi)) {
        cout << "hi returned true" << endl;
        assignments[(cur->var)] = true;
        return true;
    } 
    return false;
}

unordered_map<size_t, bool> BDD::solveOne() {
    Node * root = getRoot();
    solveOneHelper(root);
    return assignments;
}
