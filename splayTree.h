#ifndef SplayTree_H
#define SplayTree_H

class SplayTree {
    public:
        void splay(int x);
        void insert(int x);
        bool remove(int x);
        int find(int x);
};

#endif
