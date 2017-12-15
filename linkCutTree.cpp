#include "linkCutTree.h"
#include <iostream>
#include <algorithm>
#include <cassert>


LCTNode::LCTNode() {
    left_child = right_child = parent = NULL;
    value = 0;
    flip = false;
}

bool LinkCutTree::is_root(LCTNode * node) {
    LCTNode * parent = node->parent;
    return !parent || (node != parent->left_child && node != parent->right_child);
}

void LCTNode::push() {
    if (flip) {
        std::swap(left_child, right_child);

        if (left_child) left_child->flip = !left_child->flip;
        if (right_child) right_child->flip = !right_child->flip;
        flip = false;
    }
}

void LCTNode::update() {}

void LCTNode::print() {}

LCTNode * LinkCutTree::get_node(int x) {
    return node_map[x];
}

void LinkCutTree::rotate_right(LCTNode* node) {
    LCTNode * parent = node->parent;
    LCTNode * gparent = parent->parent;
    LCTNode * right_child = node->right_child;

    node->parent = gparent;
    if (gparent) {
        if (parent == gparent->left_child)
            gparent->left_child = node;
        else
            gparent->right_child = node;
    }

    node->right_child = parent;
    parent->parent = node;

    parent->left_child = right_child;
    if (right_child) right_child->parent = parent;

    parent->update();
    node->update();
}

void LinkCutTree::rotate_left(LCTNode * node) {
    LCTNode * parent = node->parent;
    LCTNode * gparent = parent->parent;
    LCTNode * left_child = node->left_child;

    node->parent = gparent;
    if (gparent) {
        if (parent == gparent->left_child)
            gparent->left_child = node;
        else
            gparent->right_child = node;
    }

    node->left_child = parent;
    parent->parent = node;

    parent->right_child = left_child;
    if (left_child) left_child->parent = parent;

    parent->update();
    node->update();
}

void LinkCutTree::rotate(LCTNode * node) {
    if (is_root(node)) return;
    LCTNode * parent = node->parent;
    if (node == parent->left_child) rotate_right(node);
    else rotate_left(node);
}

void LinkCutTree::splay(LCTNode * node) {
    if (!node) return;

    while (!is_root(node)) {
        LCTNode * parent = node->parent;
        LCTNode * gparent = parent->parent;

        if (!is_root(parent)) gparent->push();
        parent->push();
        node->push();

        if (is_root(parent)) {
            rotate(node);
            break;
        }

        bool is_node_lc = (node == parent->left_child);
        bool is_parent_lc = (parent == gparent->left_child);

        if (is_node_lc == is_parent_lc) { // ZigZig
            rotate(parent);
            rotate(node);
        } else { // ZigZag
            rotate(node);
            rotate(node);
        }
    }
    node->push();
}

void LinkCutTree::access(LCTNode * node) {
    LCTNode * orig_node = node;
    LCTNode * last = NULL;

    while (node) {
        splay(node);
        node->right_child = last;
        last = node;
        node = node->parent;
    }

    splay(orig_node);
}

void LinkCutTree::reroot(LCTNode * node) {
    access(node);
    node->flip = !node->flip;
}

void LinkCutTree::add(int x) {
    node_map[x] = new LCTNode();
}

bool LinkCutTree::link(int x, int y) {
    assert(!conn(x, y));
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    if (!a || !b) return false;

    reroot(a);
    a->parent = b;
    return true;
}

bool LinkCutTree::cut(int x, int y) {
    assert(conn(x, y));
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    if (!a || !b) return false;

    reroot(a);
    access(b);
    splay(a);
    a->right_child = NULL;
    b->parent = NULL;
    return true;
}

bool LinkCutTree::conn(int x, int y) {
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    if (!a || !b) return false;

    reroot(a);
    access(b);
    return a->parent;
}

