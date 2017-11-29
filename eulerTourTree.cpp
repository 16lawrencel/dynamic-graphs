// actually stores a forest of euler tour trees
// there can be multiple occurences of a node
// node_map stores an arbitrary occurence
#include "eulerTourTree.h"
#include <cassert>

#define ETT EulerTourTree
#define ST SplayTree

Node * ETT::get_node(int x) {
    auto it = node_map.find(x);

    // no set related to x
    if (it == node_map.end()) return NULL;

    auto st = it->second;
    if (st.empty()) return NULL;
    return *st.begin();
}

Node * ETT::get_edge(int x, int y) {
    std::pair<int, int> p = std::make_pair(x, y);
    auto it = edge_map.find(p);
    if (it == edge_map.end()) return NULL;
    return it->second;
}

void ETT::add(int x) {
    Node * node = new Node();
    node->value = x;
    add_node(x, node);
}

void ETT::add_node(int x, Node * node) {
    node_map[x].insert(node);
}

void ETT::add_edge(int x, int y, Node * node) {
    std::pair<int, int> p = std::make_pair(x, y);
    edge_map[p] = node;
}

void ETT::remove_node(int x, Node * node) {
    node_map[x].erase(node);
}

void ETT::remove_edge(int x, int y) {
    std::pair<int, int> p = std::make_pair(x, y);
    edge_map.erase(p);
}

/*
   Performs a cyclic shift on the ordering of the tree
   that node is in such that node is in the front.
*/
void ETT::shift_to_front(Node * node) {
    ST::splay(node);

    // if no left child, node is already in front
    if (!node->left_child) return;

    Node * left_child = node->left_child;
    ST::disown(left_child);

    Node * front = ST::get_front(left_child);
    assert(!front->parent);
    assert(!front->left_child);

    // insert node back under front
    // this performs the desired cyclical shift

    front->left_child = node;
    node->parent = front;
    front->update();

    ST::splay(node);
}

void ETT::link(int x, int y) {
    if (conn(x, y)) return;

    Node * a = get_node(x);
    Node * b = get_node(y);

    if (!a || !b) return;

    // shift a and b to front of their respective trees
    shift_to_front(a);
    shift_to_front(b);

    // insert additional nodes for linking
    Node * a2 = ST::insert_back(a);
    Node * b2 = ST::insert_back(b);
    a2->value = x;
    b2->value = y;
    add_node(x, a2);
    add_node(y, b2);

    // a2 should already be at top, but splay for lols
    // we link (a...a2)<->(b...b2)
    ST::splay(a2);
    assert(!a2->right_child);

    ST::splay(b);
    a2->right_child = b;
    a2->update();

    // add respective edges (a2, b) and (b2, a)
    add_edge(x, y, a2);
    add_edge(y, x, b2);
}

bool ETT::cut(int x, int y) {
    Node * a = get_edge(x, y);
    if (!a) return false;

    Node * b = get_edge(y, x);
    assert(b);

    assert(a->value == x);
    assert(b->value == y);

    shift_to_front(a);
    // a should now be the root

    assert(!a->parent);
    assert(!a->left_child);

    ST::splay(b);
    // guaranteed that a and b within distance 2
    // bad zig zig edge case, so have to rotate a as necessary
    while (a->parent != b) ST::rotate(a);

    assert(b->left_child == a);

    // cut a from b
    ST::disown(a);

    // remove a and b
    remove_node(x, a);
    remove_node(y, b);
    remove_edge(x, y);
    remove_edge(y, x);

    ST::remove(a);
    ST::remove(b);

    return true;
}

bool ETT::conn(int x, int y) {
    Node * a = get_node(x);
    Node * b = get_node(y);
    
    if (!a || !b) return false;

    ST::splay(a);
    ST::splay(b);

    // if a and b not connected, a will rotate to root
    // otherwise, a will rotate to be child of b
    while (a->parent && a->parent != b)
        ST::rotate(a);

    return (a->parent == b);
}

