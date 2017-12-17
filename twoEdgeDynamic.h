// incremental only
#ifndef TwoEdgeDynamic_H
#define TwoEdgeDynamic_H

#include "linkCutTree.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <utility>

class TwoEdgeDynamic {
    private:
        std::set<int> nodes;
        //LinkCutTree lct;

        void init_tree_edge(int x, int y);
        void cover(int x, int y, int i);

    public:
        LinkCutTree lct;
        void add(int x);
        void link(int x, int y);
        bool two_edge_conn(int x, int y);
};

#endif
