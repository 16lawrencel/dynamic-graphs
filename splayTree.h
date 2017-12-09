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
        int num; // number of adjacent nodes in graph for fully dynamic
        int max_num; // max value of num in subtree

        void push(); // lazy propagation
        void update(); // update values, e.g. subtree size

        void print();
};

class SplayTree {
    public:
        static void remove(Node * node);
        static Node * find(int key);
        static void rotate(Node * node);
        static void splay(Node * node);

        static void disown(Node * node);
        static Node * successor(Node * node);
        static Node * get_front(Node * node);
        static Node * get_back(Node * node);
        static Node * insert_back(Node * node);
        static Node * find_positive_num(Node * node);

        static void print(Node * node);

    private:
        static void rotate_right(Node * node);
        static void rotate_left(Node * node);
};

#endif
