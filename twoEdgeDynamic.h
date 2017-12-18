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
        LinkCutTree lct;

    public:
        void add(int x);
        bool link(int x, int y);
        bool two_edge_conn(int x, int y);
};

#endif
