//
//  BDD.hpp
//  Created 6/3/18.
//

#ifndef BDD_hpp
#define BDD_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    size_t id;
    size_t var;
    int value;
    Node* hi;
    Node* lo;
    bool operator ==(const Node & n) const {
        size_t v_lo = n.lo != NULL ? (n.lo)->var : -1;
        size_t v_hi = n.hi != NULL ? (n.hi)->var : -1;
        size_t me_lo = lo ? lo->var : -1;
        size_t me_hi = hi ? hi->var : -1;
        return (var == n.var && me_lo == v_lo && me_hi == v_hi);
    }
    
    Node(): id(0), var(0), value(0), hi(NULL), lo(NULL) {}
};

//define std::hash on Nodes
template<>
struct hash<Node>
{
    size_t
    operator()(const Node & n) const
    {
        size_t v1 = n.lo != NULL ? (n.lo)->var : -1;
        size_t v2 = n.hi != NULL ? (n.hi)->var : -1;
        size_t v3 = n.var;
        int p = (v1+v2)*(v1+v2+1)/2 + v1;
        return hash<int>()(v3+p)*(v3+p+1)/2 + v3;
    }
};


class BDD {
    friend ostream& operator<<(ostream& os, const BDD& bdd);
public:
    explicit BDD(int num);
    ~BDD();
    /* need to implement:
     - satisfy_one
     */
    int getSize();
    Node *conjunction(class BDD b);
    Node *disjunction(class BDD b);
    Node *eor(class BDD b);
    void negate();
    void setRoot(int num);
    
    
private:
    bool isNegated;
    vector<Node*> Tree; //Vector of tree nodes
    unordered_map<Node, size_t> H; //Hash map from node to node index in vector
    Node *mk(size_t var, Node* hi, Node *lo); //Inserts node while making sure there are no duplicates.
    Node *apply(int op, BDD b);
    Node *applyHelper(int op, Node u1, Node u2, vector<vector<Node *>>& table);
    Node getRoot();
};

#endif /* BDD_hpp */

