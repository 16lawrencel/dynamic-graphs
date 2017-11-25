#include "splayTree.h"

class SplayTree {
    public:
        void splay(long long key) {
            splay(key, tree_root);
        }
        void insert(long long key, long long value) {
            insert(key, value, tree_root);
        }
        bool remove(long long key) {
            return remove(key, tree_root);
        }
        long long find(long long key) {
            return find(key, tree_root);
        }

        long long size() {
            if(!tree_root) return 0;
            return tree_root->size;
        }

        void printInorder() {
            printInorder(tree_root);
        }

    private:
        class Node {
        public:
            Node* left_child;
            Node* right_child;
            Node* parent;
            long long key;
            long long value;
            // maintain the sizes of the trees
            long long size;
        }

        Node* tree_root;

        /* RR(Y rotates to the right):
            node                 lc
           /  \                 /  \
          lc   Z     ==>       X   node
         / \                      /  \
        X   Y                    Y    Z
        */
        void rotate_right(Node* node) {
            Node* nodeParent = node->parent;
            Node* leftChild = node->left_child;
            Node* rightOfLeft = leftChild->right_child;

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
        void rotate_left(Node* node) {
            Node* nodeParent = node->parent;
            Node* rightChild = node->right_child;
            Node* leftOfRight = rightChild->left_child;

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
        void splay(Node* node, Node* root) {
            if(!root || !node) return;
            while(true) {
                // We continue until node isn't root
                if(node == root || !(node->parent)) {
                    break;
                }
                Node* parentOfParent = node->parent->parent;
                if(!parentOfParent) { // Zig
                    if(node == node->parent->left_child)
                        rotate_right(node);
                    else
                        rotate_left(node);
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
        void splay(long long key, Node* root) {
            if(!root) return;
            if(root->size == 0) return;
            Node* pred = predecessor(key, root);
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
        void predecessor(long long key, Node* node) {
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
                } else if(key > node_val) {
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
        void successor(int key, Node* node) {
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
                } else if(key > node_val) {
                    if(node->right_child) {
                        return successor(key, node->right_child);
                    } else {
                        return NULL;
                    }
                }
            }
        }

        Node* insert(long long key, long long value, Node* root) {
            if(!root) {
                root = new Node();
                root->left_child = root->right_child = root->parent = NULL;
                root->key = key;
                root->value = value;
                root->size = 1;
            } else {
                Node* now = root;
                while(!now) {
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
                                Node* new_node = new Node();
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
                                Node* new_node = new Node();
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
        }

        void printInorder(Node* node) {
            if(!node) return;
            std::cout << "( ";
            printInorder(node->left_child);
            std::cout << " ) ( " << node->key << ' ' << node->value << " ) ( ";
            printInorder(node->right_child);
            std::cout << " )";
        }
};
