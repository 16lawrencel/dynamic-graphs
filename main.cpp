#include "ds.h"
#include <iostream>

//simple test for union find
int main() {
    // UnionFind graph = UnionFind();
    // graph.add(1);
    // graph.add(2);
    // std::cout << graph.conn(1, 2) << '\n';
    // graph.merge(1, 2);
    // std::cout << graph.conn(1, 2) << '\n';

    // tests for splayTree
    SplayTree* tree = new SplayTree();
    tree->insert(1, 2);
    tree->insert(2, 3);
    tree->insert(3, 4);
    tree->printInorder();
    tree->remove(3);
    tree->remove(1);
    tree->printInorder();
    return 0;
}
