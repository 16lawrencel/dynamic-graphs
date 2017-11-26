#include "splayTree.h"
#include <iostream>
#include <cassert>

void SplayTree::splay(long long key) {
    SplayTree::splay(key, tree_root);
}
void SplayTree::insert(long long key, long long value) {
    SplayTree::insert(key, value, tree_root);
}
bool SplayTree::remove(long long key) {
    return SplayTree::remove(key, tree_root);
}
long long SplayTree::find(long long key) {
    return SplayTree::find(key, tree_root);
}

long long SplayTree::size() {
    if(!tree_root) return 0;
    return tree_root->size;
}

void SplayTree::printInorder() {
    std::cout << SplayTree::size() << '\n';
    SplayTree::printInorder(tree_root);
    std::cout << '\n';
}

/* RR(Y rotates to the right):
    node                 lc
   /  \                 /  \
  lc   Z     ==>       X   node
 / \                      /  \
X   Y                    Y    Z
*/
void SplayTree::rotate_right(SplayTree::Node* node) {
    SplayTree::Node* nodeParent = node->parent;
    SplayTree::Node* leftChild = node->left_child;
    SplayTree::Node* rightOfLeft = leftChild->right_child;

    leftChild->parent = nodeParent;
    if(nodeParent) {
        // Node is not root
        if(nodeParent->right_child == node) {
            nodeParent->right_child = leftChild;
        } else {
            nodeParent->left_child = leftChild;
        }
    } else {
        // leftChild is now root
        tree_root = leftChild;
    }

    node->left_child = rightOfLeft;
    if (rightOfLeft) {
        rightOfLeft->parent = node;
    }

    leftChild->right_child = node;
    node->parent = leftChild;

    // now fix the sizes
    long long lcsize = leftChild->size;
    leftChild->size = node->size;
    node->size = node->size - lcsize;
    if(rightOfLeft) {
        node->size += rightOfLeft->size;
    }
}

/* LL(Y rotates to the left):
        node                     rc
       /  \                     /  \
      X    rc         ==>     node  Z
          /  \                /  \
         Y    Z              X    Y
*/
void SplayTree::rotate_left(SplayTree::Node* node) {
    SplayTree::Node* nodeParent = node->parent;
    SplayTree::Node* rightChild = node->right_child;
    SplayTree::Node* leftOfRight = rightChild->left_child;

    rightChild->parent = nodeParent;
    if(nodeParent) {
        if(nodeParent->right_child == node) {
            nodeParent->right_child = rightChild;
        } else {
            nodeParent->left_child = rightChild;
        }
    } else {
        tree_root = rightChild;
    }

    node->right_child = leftOfRight;
    if(leftOfRight) {
        leftOfRight->parent = node;
    }

    rightChild->left_child = node;
    node->parent = rightChild;

    // now fix the sizes
    long long rcsize = rightChild->size;
    rightChild->size = node->size;
    node->size = node->size - rcsize;
    if(leftOfRight) {
        node->size += leftOfRight->size;
    }
}

/*
    Splay a node given by the node pointer
*/
void SplayTree::splay(SplayTree::Node* node, SplayTree::Node* root) {
    if(!root || !node) return;
    while(true) {
        // We continue until node isn't root
        if((node == root) || !(node->parent)) {
            break;
        }
        SplayTree::Node* parentOfParent = node->parent->parent;
        if(!parentOfParent) { // Zig
            if(node == node->parent->left_child)
                rotate_right(node->parent);
            else
                rotate_left(node->parent);
            break;
        }
        if(node->parent == parentOfParent->left_child) {
            if(node == node->parent->left_child) { // ZigZig
                rotate_right(parentOfParent);
                rotate_right(node->parent);
            }
            else { // ZigZag
                rotate_left(node->parent);
                rotate_right(parentOfParent);
            }
        } else { // Now parent is a right child
            if(node == node->parent->right_child) { // ZigZig
                rotate_left(parentOfParent);
                rotate_left(node->parent);
            }
            else { // ZigZag
                rotate_right(node->parent);
                rotate_left(parentOfParent);
            }
        }
    }
    tree_root = node;
}

/*
    Splay the predecessor (or successor, if this is smaller than all) of
    this key if this key doesn't exist, else splay the key
*/
void SplayTree::splay(long long key, SplayTree::Node* root) {
    if(!root) return;
    if(root->size == 0) return;
    SplayTree::Node* pred = predecessor(key, root);
    if(pred) {
        splay(pred, root);
    } else {
        splay(successor(key, root), root);
    }
}
/*
    Given a key, find a node which has the largest key smaller than (or
    equal to) key
    Returns NULL if this key is smaller than everything on the tree
*/
SplayTree::Node* SplayTree::predecessor(long long key, SplayTree::Node* node) {
    long long node_val = node->key;
    if(node_val == key) {
        return node;
    } else {
        if(key < node_val) {
            if(node->left_child) {
                return predecessor(key, node->left_child);
            } else {
                return NULL;
            }
        } else {
            if(node->right_child) {
                return predecessor(key, node->right_child);
            } else {
                // on this subtree, we have no key bigger than node
                // So, node is the largest key smaller than key
                return node;
            }
        }
    }
}


/*
    Given a key, find a node which has the smallest key larger (or equal
    to) than key
    Returns NULL if this key is larger than everything on the tree
*/
SplayTree::Node* SplayTree::successor(long long key, SplayTree::Node* node) {
    long long node_val = node->key;
    if(node_val == key) {
        return node;
    } else {
        if(key < node_val) {
            if(node->left_child) {
                return successor(key, node->left_child);
            } else {
                // on this subtree, we have no key bigger than node
                // So, node is the largest key smaller than key
                return node;
            }
        } else {
            if(node->right_child) {
                return successor(key, node->right_child);
            } else {
                return NULL;
            }
        }
    }
}

SplayTree::Node* SplayTree::insert(long long key, long long value, SplayTree::Node* root) {
    if(!root) {
        root = new Node();
        root->left_child = root->right_child = root->parent = NULL;
        root->key = key;
        root->value = value;
        root->size = 1;
        tree_root = root;
        return root;
    } else {
        SplayTree::Node* now = root;
        while(now) {
            if(now->key == key) {
                // No multiset, only update
                now->value = value;
                splay(now, root);
                return now;
            } else {
                if(key < now->key) {
                    if(now->left_child) {
                        now = now->left_child;
                    } else {
                        SplayTree::Node* new_node = new Node();
                        new_node->left_child = new_node->right_child = NULL;
                        new_node->parent = now;
                        new_node->key = key;
                        new_node->value = value;
                        new_node->size = 1;
                        now->left_child = new_node;
                        now->size += 1;
                        splay(new_node, root);
                        return new_node;
                    }
                } else {
                    if(now->right_child) {
                        now = now->right_child;
                    } else {
                        SplayTree::Node* new_node = new Node();
                        new_node->left_child = new_node->right_child = NULL;
                        new_node->parent = now;
                        new_node->key = key;
                        new_node->value = value;
                        new_node->size = 1;
                        now->right_child = new_node;
                        now->size += 1;
                        splay(new_node, root);
                        return new_node;
                    }
                }
            }
        }
    }
    assert(false && "Shouldn't reach here!");
    return NULL;
}

void SplayTree::printInorder(SplayTree::Node* node) {
    if(!node) return;
    std::cout << "( ";
    printInorder(node->left_child);
    std::cout << " ) ( " << node->key << ',' << node->value << " ) ( ";
    printInorder(node->right_child);
    std::cout << " )";
}

/*
    IMPORTANT: Returns null if the key is not found there.
*/
long long SplayTree::find(long long key, SplayTree::Node* node) {
    SplayTree::Node* pred = SplayTree::predecessor(key, tree_root);
    if(pred) {
        if(pred->key == key)
            return pred->value;
    }
    return NULL;
}

bool SplayTree::remove(long long key, SplayTree::Node* node) {
    SplayTree::Node* pred = SplayTree::predecessor(key, tree_root);
    if(pred->key == key) {
        SplayTree::splay(pred, tree_root);
        if(!pred->left_child) {
            tree_root = pred->right_child;
            tree_root->parent = NULL;
            free(pred);
            return true;
        } else {
            SplayTree::Node* P = pred->left_child;
            while(P->right_child)
                P = P->right_child;
            pred->left_child->parent = NULL;
            SplayTree::splay(P, pred->left_child);
            assert (P->right_child == NULL);
            P->right_child = pred->right_child;
            if(pred->right_child) {
                P->size += pred->right_child->size;
                pred->right_child->parent = P;
            }
            tree_root = P;
            tree_root->parent = NULL;
            free(pred);
            return true;
        }
    }
    return false;
}
