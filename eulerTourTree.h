#ifndef EulerTourTree_H
#define EulerTourTree_H

class EulerTourTree {
    public:
        void add(int x);
        void link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);
};

#endif
