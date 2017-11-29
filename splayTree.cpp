// generalized splay trees
// structure can support forest of trees
// in particular, can have multiple roots
#include "splayTree.h"
#include <iostream>
#include <cassert>

#define ST SplayTree

Node::Node() {
    left_child = right_child = parent = NULL;
    key = value = 0;
    size = 1;
}

void Node::push() {
}

void Node::update() {
    size = 1;
    if (left_child) size += left_child->size;
    if (right_child) size += right_child->size;
}

void ST::remove(Node * node) {
    splay(node);

    Node * left = node->left_child;
    Node * right = node->right_child;

    if (!left && !right) {}
    else if (!left) {
        disown(right);
    } else if (!right) {
        disown(left);
    } else {
        disown(left);
        disown(right);

        Node * x = get_front(right);
        // x should be at root
        assert(!x->parent);
        assert(!x->left_child);
        x->left_child = left;
        x->update();
    }

    free(node);
}

/* RR(Y rotates to the right):
    par                 node
   /  \                 /  \
 node  Z     ==>       X   par
 / \                      /  \
X   Y                    Y    Z
*/
void ST::rotate_right(Node* node) {
    Node * parent = node->parent;
    Node * gparent = node->parent;
    Node * right_child = node->right_child;

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
    right_child->parent = parent;

    parent->update();
    node->update();
}

/* LL(Y rotates to the left):
        par                     node
       /  \                     /  \
      X   node         ==>    par   Z
          /  \                /  \
         Y    Z              X    Y
*/
void ST::rotate_left(Node * node) {
    Node * parent = node->parent;
    Node * gparent = node->parent;
    Node * left_child = node->left_child;

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
    left_child->parent = parent;

    parent->update();
    node->update();
}

void ST::rotate(Node * node) {
    Node * parent = node->parent;
    if (!parent) return;
    if (node == parent->left_child) rotate_right(node);
    else rotate_left(node);
}

/*
    Splay a node given by the node pointer
*/
void ST::splay(Node* node) {
    if (!node) return;

    // keep rotating up until node has no parent, i.e. node is root
    while (node->parent) {
        Node * parent = node->parent;
        Node * gparent = parent->parent;

        if (!gparent) { // Zig
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
            rotate(parent);
        }
    }
}

/*
   Removes the connection between node and its parent.
   node becomes a root after this.
*/
void ST::disown(Node * node) {
    Node * parent = node->parent;
    if (!parent) return;

    if (node == parent->left_child) parent->left_child = NULL;
    else parent->right_child = NULL;
    node->parent = NULL;
    parent->update();
}

/*
   Gets the first node in node's tree.
*/
Node * ST::get_front(Node * node) {
    splay(node);
    while (node->left_child) node = node->left_child;
    splay(node);
    return node;
}

/*
   Inserts a node to the back of node's tree
*/
Node * ST::insert_back(Node * node) {
    splay(node);
    while (node->right_child) node = node->right_child;

    Node * new_node = new Node();
    new_node->parent = node;
    node->right_child = new_node;
    node->update();
    splay(new_node);
    return new_node;
}

