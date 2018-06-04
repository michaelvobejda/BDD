//
//  BDD.hpp
//  
//
//  Created 6/3/18.
//

#ifndef BDD_hpp
#define BDD_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    size_t var;
    Node* hi;
    Node* lo;
};

template<>
struct hash<Node>
{
    size_t
    operator()(const Node & n) const
    {
        size_t v1 = (n.lo)->var;
        size_t v2 = (n.hi)->var;
        return hash<int>()((v1+v2)*(v1+v2+1)/2 + v1);
    }
};

class BDD {
public:
    explicit BDD();
    
    /* need to implement:
     - build(t): constructs a BDD using given boolean expression
     - and(bdd): AND's two bdds
     - satisfy_one
     */
    
private:
    size_t numVars;
    vector<Node> T; //Vector of tree nodes
    unordered_map<Node, int> H; //Hash map from node to node index in vector
    Node mk(size_t var, Node* hi, Node *lo); //Inserts node while making sure there are no duplicates.
};

#endif /* BDD_hpp */

