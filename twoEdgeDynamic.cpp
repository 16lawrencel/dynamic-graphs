#include "twoEdgeDynamic.h"
#include <algorithm>
#include <cassert>

void TwoEdgeDynamic::add(int x) {
    nodes.insert(x);
    lct.add(x);
}

bool TwoEdgeDynamic::link(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return false;

    if (!lct.conn(x, y)) {
        lct.link(x, y);
    } else {
        lct.cover(x, y, 0);
    }

    return true;
}

bool TwoEdgeDynamic::two_edge_conn(int x, int y) {
    if (x == y) return true;
    return lct.conn(x, y) && lct.get_min(x, y) >= 0;
}

