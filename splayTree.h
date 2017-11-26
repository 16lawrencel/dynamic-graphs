#ifndef SplayTree_H
#define SplayTree_H

class SplayTree {
    public:
        void splay(long long key);
        void insert(long long key, long long value);
        bool remove(long long key);
        long long find(long long key);
        long long size();
        void printInorder();

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
        };
        Node* tree_root;
        void rotate_right(Node* node);
        void rotate_left(Node* node);
        void splay(Node* node, Node* root);
        void splay(long long key, Node* root);
        Node* predecessor(long long key, Node* node);
        Node* successor(long long key, Node* node);
        Node* insert(long long key, long long value, Node* root);
        void printInorder(Node* node);
        bool remove(long long key, Node* node);
        long long find(long long key, Node* node);
};

#endif
