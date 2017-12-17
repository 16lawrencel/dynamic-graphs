#include "twoEdgeDynamic.h"
#include <algorithm>
#include <cassert>

void TwoEdgeDynamic::add(int x) {
    nodes.insert(x);
    lct.add(x);
}

void TwoEdgeDynamic::init_tree_edge(int x, int y) {
    lct.set_edge_value(x, y, -1);
}

void TwoEdgeDynamic::cover(int x, int y, int i) {
    lct.cover(x, y, i);
}

void TwoEdgeDynamic::link(int x, int y) {
    if (!lct.conn(x, y)) {
        printf("Adding bridge: %d %d\n", x, y);
        lct.link(x, y);
        init_tree_edge(x, y);
    } else {
        printf("Covering: %d %d\n", x, y);
        cover(x, y, 0);
    }
}

bool TwoEdgeDynamic::two_edge_conn(int x, int y) {
    if (x == y) return true;
    return lct.conn(x, y) && lct.get_min(x, y) >= 0;
}

