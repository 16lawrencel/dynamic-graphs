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
        bool flip;
        int cover;

        int c_pred;
        int c_succ;
        int c_min;

        void push(); // lazy propagation
        void update(); // update values, e.g. subtree size
        void update_cover(int i);

        void print();
};

class LinkCutTree {
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
        LCTNode * get_front(LCTNode * node);
        void print_dfs(LCTNode * node);

    public:
        void add(int x);
        bool link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);

        // these are used for incremental two-edge connectivity
        // and shouldn't be accessed for normal LCT purposes
        void cover(int x, int y, int i);
        int get_min(int x, int y);

        void print_path(int x, int y);
};

#endif
