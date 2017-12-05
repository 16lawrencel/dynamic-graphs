#include "eulerTourTree.h"
#include <cassert>

// actually stores a forest of euler tour trees
// there can be multiple occurences of a node
// node_map stores an arbitrary occurence


Node * EulerTourTree::get_node(int x) {
    auto it = node_map.find(x);

    // no set related to x
    if (it == node_map.end()) return NULL;

    auto st = it->second;
    if (st.empty()) return NULL;
    return *st.begin();
}

Node * EulerTourTree::get_edge(int x, int y) {
    std::pair<int, int> p = std::make_pair(x, y);
    auto it = edge_map.find(p);
    if (it == edge_map.end()) return NULL;
    return it->second;
}

void EulerTourTree::add(int x) {
    Node * node = new Node();
    node->value = x;
    add_node(x, node);
}

void EulerTourTree::add_node(int x, Node * node) {
    node_map[x].insert(node);
}

void EulerTourTree::add_edge(int x, int y, Node * node) {
    std::pair<int, int> p = std::make_pair(x, y);
    edge_map[p] = node;
}

void EulerTourTree::remove_node(int x, Node * node) {
    node_map[x].erase(node);
}

void EulerTourTree::remove_edge(int x, int y) {
    std::pair<int, int> p = std::make_pair(x, y);
    edge_map.erase(p);
}

/*
   Performs a cyclic shift on the ordering of the tree
   that node is in such that node is in the front.
*/
void EulerTourTree::shift_to_front(Node * node) {
    SplayTree::splay(node);

    // if no left child, node is already in front
    if (!node->left_child) return;

    Node * left_child = node->left_child;
    SplayTree::disown(left_child);

    Node * front = SplayTree::get_front(left_child);
    assert(!front->parent);
    assert(!front->left_child);

    // insert node back under front
    // this performs the desired cyclical shift

    front->left_child = node;
    node->parent = front;
    front->update();

    SplayTree::splay(node);
}

void EulerTourTree::link(int x, int y) {
    if (conn(x, y)) return;

    Node * a = get_node(x);
    Node * b = get_node(y);

    if (!a || !b) return;

    // shift a and b to front of their respective trees
    shift_to_front(a);
    shift_to_front(b);

    // insert additional nodes for linking
    Node * a2 = SplayTree::insert_back(a);
    Node * b2 = SplayTree::insert_back(b);
    a2->value = x;
    b2->value = y;
    add_node(x, a2);
    add_node(y, b2);

    // a2 should already be at top, but splay for lols
    // we link (a...a2)<->(b...b2)
    SplayTree::splay(a2);
    assert(!a2->right_child);

    SplayTree::splay(b);
    a2->right_child = b;
    a2->update();

    // add respective edges (a2, b) and (b2, a)
    add_edge(x, y, a2);
    add_edge(y, x, b2);
}

bool EulerTourTree::cut(int x, int y) {
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

    SplayTree::splay(b);
    // guaranteed that a and b within distance 2
    // bad zig zig edge case, so have to rotate a as necessary
    while (a->parent != b) SplayTree::rotate(a);

    assert(b->left_child == a);

    // cut a from b
    SplayTree::disown(a);

    // remove a and b
    remove_node(x, a);
    remove_node(y, b);
    remove_edge(x, y);
    remove_edge(y, x);

    SplayTree::remove(a);
    SplayTree::remove(b);

    return true;
}

bool EulerTourTree::conn(int x, int y) {
    Node * a = get_node(x);
    Node * b = get_node(y);
    
    if (!a || !b) return false;

    SplayTree::splay(a);
    SplayTree::splay(b);

    // if a and b not connected, a will rotate to root
    // otherwise, a will rotate to be child of b
    while (a->parent && a->parent != b)
        SplayTree::rotate(a);

    return (a->parent == b);
}

/*
   Gets size of x's connected component
*/
int EulerTourTree::get_size(int x) {
    Node * a = get_node(x);
    SplayTree::splay(a);
    return a->size;
}

int EulerTourTree::get_positive_num(int x) {
    Node * a = get_node(x);
    Node * res = SplayTree::find_positive_num(a);
    if (!res) return -1;
    return res->value;
}

void EulerTourTree::update_num(int x, int d_num) {
    Node * a = get_node(x);
    SplayTree::splay(a);
    a->num += d_num;
    a->update();
}

