#include "ds.h"

class DSU::Node {
    DSU::Node * par;
    int rank;

    Node() {
        par = NULL;
        rank = 0;
    }
};

void DSU::add(int x) {
    node_map[x] = new Node();
}

