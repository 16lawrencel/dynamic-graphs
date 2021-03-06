// generalized splay trees
// structure can support forest of trees
// in particular, can have multiple roots
#include "splayTree.h"
#include <cassert>
#include <algorithm>


Node::Node() {
    left_child = right_child = parent = NULL;
    value = 0;
    num[0] = sum_num[0] = num[1] = sum_num[1] = 0;
    size = 1;
}

void Node::print() {
    int x = value;
    int p = parent ? parent->value : 0;
    int lc = left_child ? left_child->value : 0;
    int rc = right_child ? right_child->value : 0;

    printf("Node: %d; parent: %d; left child: %d; right child: %d\n", x, p, lc, rc);
}

void Node::update() {
    size = 1;
    sum_num[0] = num[0];
    sum_num[1] = num[1];

    if (left_child) {
        size += left_child->size;
        sum_num[0] += left_child->sum_num[0];
        sum_num[1] += left_child->sum_num[1];
    }

    if (right_child) {
        size += right_child->size;
        sum_num[0] += right_child->sum_num[0];
        sum_num[1] += right_child->sum_num[1];

    }
}

void SplayTree::print(Node * node) {
    if (!node) return;
    //node->print();
    print(node->left_child);
    node->print();
    print(node->right_child);
}

void SplayTree::remove(Node * node) {
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
}

/* RR(Y rotates to the right):
    par                 node
   /  \                 /  \
 node  Z     ==>       X   par
 / \                      /  \
X   Y                    Y    Z
*/
void SplayTree::rotate_right(Node* node) {
    Node * parent = node->parent;
    Node * gparent = parent->parent;
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
    if (right_child) right_child->parent = parent;

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
void SplayTree::rotate_left(Node * node) {
    Node * parent = node->parent;
    Node * gparent = parent->parent;
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
    if (left_child) left_child->parent = parent;

    parent->update();
    node->update();
}

void SplayTree::rotate(Node * node) {
    Node * parent = node->parent;
    if (!parent) return;
    if (node == parent->left_child) rotate_right(node);
    else rotate_left(node);
}

/*
    Splay a node given by the node pointer
*/
void SplayTree::splay(Node* node) {
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
            rotate(node);
        }
    }
}

/*
   Removes the connection between node and its parent.
   node becomes a root after this.
*/
void SplayTree::disown(Node * node) {
    Node * parent = node->parent;
    if (!parent) return;

    if (node == parent->left_child) parent->left_child = NULL;
    else parent->right_child = NULL;
    node->parent = NULL;
    parent->update();
}

Node * SplayTree::successor(Node * node) {
    splay(node);
    node = node->right_child;
    if (!node) return NULL;
    while (node->left_child) node = node->left_child;
    splay(node);
    return node;
}


/*
   Gets the first node in node's tree.
*/
Node * SplayTree::get_front(Node * node) {
    splay(node);
    while (node->left_child) node = node->left_child;
    splay(node);
    return node;
}

Node * SplayTree::get_back(Node * node) {
    splay(node);
    while (node->right_child) node = node->right_child;
    splay(node);
    return node;
}

/*
   Inserts a node to the back of node's tree
*/
Node * SplayTree::insert_back(Node * node) {
    if (!node) return new Node();

    splay(node);
    while (node->right_child) node = node->right_child;

    Node * new_node = new Node();
    new_node->parent = node;
    node->right_child = new_node;
    node->update();
    splay(new_node);
    return new_node;
}

/*
   Finds a node in node's tree with num > 0
   If no such nodes exist, returns NULL
*/
Node * SplayTree::find_positive_num(Node * node) {
    splay(node);
    if (node->sum_num <= 0) return NULL;

    while (node->num <= 0) {
        Node * left_child = node->left_child;
        Node * right_child = node->right_child;

        if (left_child && left_child->sum_num > 0)
            node = left_child;
        else if (right_child && right_child->sum_num > 0)
            node = right_child;
        else assert(false);
    }

    splay(node);
    return node;
}

