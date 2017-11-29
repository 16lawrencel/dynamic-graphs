#ifndef SplayTree_H
#define SplayTree_H

class Node {
    public:
        Node();

        Node * left_child;
        Node * right_child;
        Node * parent;
        int key;
        int value;
        int size;

        void push(); // lazy propagation
        void update(); // update values, e.g. subtree size
};

class SplayTree {
    public:
        static Node * insert(int key);
        static void remove(Node * node);
        static Node * find(int key);
        static void rotate(Node * node);
        static void splay(Node * node);

        static void disown(Node * node);
        static Node * get_front(Node * node);
        static Node * insert_back(Node * node);

    private:
        static void rotate_right(Node * node);
        static void rotate_left(Node * node);
        static Node * predecessor(int key, Node * node);
        static Node * successor(int key, Node * node);
};

#endif
