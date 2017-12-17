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
    public:
        void add(int x);
        bool link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);

        // these are used for incremental two-edge connectivity
        void set_edge_value(int x, int y, int v);
        void cover(int x, int y, int i);
        int get_min(int x, int y);

        void print_path(int x, int y);

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
        int dfs_min(LCTNode * x);
        void print_dfs(LCTNode * node);
};

#endif
