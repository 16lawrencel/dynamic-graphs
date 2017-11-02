#include "ds.h"
#include <iostream>

//simple test for union find
int main() {
    UnionFind graph = UnionFind();
    graph.add(1);
    graph.add(2);
    std::cout << graph.conn(1, 2) << '\n';
    graph.merge(1, 2);
    std::cout << graph.conn(1, 2) << '\n';
}
