#include "linkCutTree.h"
#include <iostream>
#include <algorithm>
#include <cassert>

const int INF = (1 << 31) - 1;

LCTNode::LCTNode() {
    left_child = right_child = parent = NULL;
    value = 0;
    flip = false;
    cover = -1;
    c_pred = c_succ = c_min = INF;
}

void LCTNode::update_cover(int i) {
    cover = std::max(cover, i);
    c_min = std::max(c_min, cover);
}

void LCTNode::push() {
    if (flip) {
        std::swap(left_child, right_child);
        std::swap(c_pred, c_succ);

        if (left_child) left_child->flip = !left_child->flip;
        if (right_child) right_child->flip = !right_child->flip;
        flip = false;
    }

    if (cover != -1) {
        if (c_pred < cover) c_pred = cover;
        if (c_succ < cover) c_succ = cover;
        c_min = std::max(c_min, cover);

        if (left_child) left_child->update_cover(cover);
        if (right_child) right_child->update_cover(cover);
        cover = -1;
    }
}

void LCTNode::update() {
    c_min = std::min(c_pred, c_succ);
    if (left_child) c_min = std::min(c_min, left_child->c_min);
    if (right_child) c_min = std::min(c_min, right_child->c_min);
}

void LCTNode::print() {
    int x = value;
    int p = parent ? parent->value : 0;
    int lc = left_child ? left_child->value : 0;
    int rc = right_child ? right_child->value : 0;

    printf("Node: %d; parent: %d; left child: %d; right child: %d; c_pred: %d; c_succ: %d; c_min: %d; flip: %d; cover: %d\n", x, p, lc, rc, c_pred, c_succ, c_min, flip, cover);
}

LCTNode * LinkCutTree::get_node(int x) {
    return node_map[x];
}

bool LinkCutTree::is_root(LCTNode * node) {
    LCTNode * parent = node->parent;
    return !parent || (node != parent->left_child && node != parent->right_child);
}

void LinkCutTree::rotate_right(LCTNode* node) {
    LCTNode * parent = node->parent;
    LCTNode * gparent = parent->parent;
    LCTNode * right_child = node->right_child;

    node->parent = gparent;
    if (!is_root(parent)) {
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
    if (!is_root(parent)) {
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
        if (last) {
            if (last->c_pred == INF) {
                printf("BAD\n");
                printf("%d %d\n", last->value, node->value);
            }
            assert(last->c_pred != INF);
        }
        node->c_succ = last ? last->c_pred : INF;
        node->update();
        node = get_front(node);
        last = node;
        node = node->parent;
    }

    splay(orig_node);
}

LCTNode * LinkCutTree::get_front(LCTNode * node) {
    splay(node);
    while (node->left_child) {
        node = node->left_child;
        node->push();
    }
    splay(node);
    return node;
}

void LinkCutTree::reroot(LCTNode * node) {
    access(node);
    node->flip = !node->flip;
    node->push();
}

void LinkCutTree::add(int x) {
    LCTNode * node = new LCTNode();
    node->value = x;
    node_map[x] = node;
}

bool LinkCutTree::link(int x, int y) {
    assert(!conn(x, y));
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    if (!a || !b) return false;

    reroot(b);
    b->parent = a;
    b->c_pred = -1;
    b->update();
    
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

    assert(a->right_child == b);
    assert(!b->left_child);
    assert(!b->right_child);
    assert(!a->flip);
    assert(!b->flip);

    a->right_child = NULL;
    b->parent = NULL;
    a->c_succ = INF;
    b->c_pred = INF;

    a->update();
    b->update();

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

void LinkCutTree::set_edge_value(int x, int y, int v) {
    return;
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    assert(a && b);

    assert(!a->right_child);
    assert(!b->left_child);
    assert(!a->flip);
    assert(!b->flip);
    a->right_child = b;
    a->c_succ = v;
    b->c_pred = v;
    b->update();
    a->update();

    access(a);



    reroot(a);
    access(b);
    splay(a);

    assert(is_root(a));
    assert(!a->left_child);
    assert(a->right_child == b);
    assert(!b->left_child);
    assert(!b->right_child);
    assert(!a->flip);
    assert(!b->flip);

    a->c_succ = v;
    b->c_pred = v;
    b->update();
    a->update();
}

void LinkCutTree::cover(int x, int y, int i) {
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    assert(a && b);

    reroot(a);
    access(b);

    assert(is_root(b));
    assert(!b->right_child);
    assert(!a->left_child);
    assert(a->c_pred == INF);

    b->update_cover(i);
    b->push();
    printf("B: %d %d\n", b->value, b->c_min);
    printf("PRINTING2\n");
    print_path(x, y);
}

int LinkCutTree::dfs_min(LCTNode * x) {
    if (!x) return INF;
    x->push();
    return std::min(std::min(x->c_pred, x->c_succ), std::min(dfs_min(x->left_child), dfs_min(x->right_child)));
}

int LinkCutTree::get_min(int x, int y) {
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    assert(a && b);

    reroot(a);
    access(b);

    //return dfs_min(b);


    return b->c_min;
}

void LinkCutTree::print_dfs(LCTNode * node) {
    if (!node) return;
    node->print();
    print_dfs(node->left_child);
    print_dfs(node->right_child);
}

void LinkCutTree::print_path(int x, int y) {
    LCTNode * a = get_node(x);
    LCTNode * b = get_node(y);

    assert(a && b);

    printf("A and B: %d %d\n", a->value, b->value);

    reroot(a);
    access(b);
    printf("PRINTING\n");
    print_dfs(b);
    printf("PRINTING\n");
    access(a);

    print_dfs(a);
}

