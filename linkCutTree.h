#ifndef LinkCutTree_H
#define LinkCutTree_H

class LinkCutTree {
    public:
        void add(int x);
        void link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);
};

#endif
