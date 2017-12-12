#ifndef LinkCutTree_H
#define LinkCutTree_H

#include <vector>

class LinkCutTree {
    private:
        std::vector<int> f, c[2], p;
        bool d(int x);
        bool r(int x);
        void push(int x);
        void rot(int x);
        void splay(int x);
        void access(int x);
        void reroot(int x);

    public:
        int size;

        LinkCutTree(int N) {
            size = N;
            f.resize(N + 10, 0);
            c[0].resize(N + 10, 0);
            c[1].resize(N + 10, 0);
            p.resize(N + 10, 0);
        }
        // void add(int x);
        void link(int x, int y);
        void cut(int x, int y);
        bool conn(int x, int y);
};

#endif
