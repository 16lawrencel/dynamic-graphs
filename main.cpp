#include "ds.h"
#include <iostream>
#include <cassert>

//simple test for union find

void testUnionFind() {
    UnionFind graph = UnionFind();
    graph.add(1);
    graph.add(2);
    
    assert(!graph.conn(1, 2));
    graph.merge(1, 2);
    assert(graph.conn(1, 2));
}

void testSplayTree() {
    SplayTree* tree = new SplayTree();
    //todo
}

void testAll() {
    testUnionFind();
    testSplayTree();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testAll();
    return 0;
}

