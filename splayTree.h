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
};

#endif
