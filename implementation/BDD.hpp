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
    struct Node* hi;
    struct Node* lo;
    size_t var;
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
    int numVars;
    //Vector of tree nodes
    vector<Node> T;
    //Hash map from node to node index in vector
    unordered_map<int, Node> H;
};

#endif /* BDD_hpp */

