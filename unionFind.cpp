#include "unionFind.h"
#include <cstdio>
#include <algorithm>

class UnionFind::Node {
    public:
        Node * parent;
        int rank;

        Node() {
            parent = this;
            rank = 0;
        }
};

       
/**
    Returns the node represented by x. If x is not in the 
    structure, returns NULL.
**/
UnionFind::Node * UnionFind::get_node(int x) {
    auto it = node_map.find(x);
    if (it == node_map.end()) return NULL; // not in structure
    return it->second;
}

/**
    Returns representative element of x in the union find 
    structure.
**/
UnionFind::Node * UnionFind::find(Node * x) {
    if (x->parent == x) return x;
    Node * y = UnionFind::find(x->parent);
    x->parent = y;
    return y;
}

/**
    Adds x to the union find structure (initially, there 
    are no elements in union find, so we have to insert 
    them one by one).
**/
void UnionFind::add(int x) {
    node_map[x] = new UnionFind::Node();
}

/**
    Merges x and y, so that they are in the same connected 
    component. If either x or y don't exist in the structure, 
    prints an error statement and returns. If x and y are 
    already connected, does nothing.
**/
void UnionFind::merge(int x, int y) {
    UnionFind::Node * node_x = UnionFind::get_node(x);
    UnionFind::Node * node_y = UnionFind::get_node(y);
    if (node_x == NULL || node_y == NULL) {
        printf("Merge called nonexisting elements");
        return;
    }

    //get representative elements
    node_x = UnionFind::find(node_x);
    node_y = UnionFind::find(node_y);

    if (node_x == node_y) return;

    if (node_x->rank > node_y->rank) std::swap(node_x, node_y);
    node_x->parent = node_y;
    if (node_x->rank == node_y->rank) ++node_y->rank; //gotta do that low level optimization
}

/**
    Returns whether x and y are in the same connected 
    component. If either x or y don't exist in the structure, 
    prints an error statement and returns false.
**/
bool UnionFind::conn(int x, int y) {
    UnionFind::Node * node_x = UnionFind::get_node(x);
    UnionFind::Node * node_y = UnionFind::get_node(y);
    if (node_x == NULL || node_y == NULL) {
        printf("Conn called nonexisting elements");
        return false;
    }

    //get representative elements
    node_x = UnionFind::find(node_x);
    node_y = UnionFind::find(node_y);

    return (node_x == node_y);
}

