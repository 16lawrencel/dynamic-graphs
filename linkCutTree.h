#ifndef LinkCutTree_H
#define LinkCutTree_H

#include <unordered_map>
#include <set>

class LCTNode {
    public:
        LCTNode();

        LCTNode * left_child;
        LCTNode * right_child;
        LCTNode * parent;
        int value;
        int size;
        bool flip;

        void push(); // lazy propagation
        void update(); // update values, e.g. subtree size

        void print();
};

class LinkCutTree {
    public:
        void add(int x);
        bool link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);

    private:
        std::unordered_map<int, LCTNode*> node_map;

        LCTNode * get_node(int x);
        bool is_root(LCTNode * node);
        void rotate_right(LCTNode * node);
        void rotate_left(LCTNode * node);
        void rotate(LCTNode * node);
        void splay(LCTNode * node);
        void access(LCTNode * node);
        void reroot(LCTNode * node);
};

#endif
