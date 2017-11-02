#ifndef UnionFind_H
#define UnionFind_H

#include <unordered_map>

class UnionFind {
    private:
        class Node;
        std::unordered_map<int, Node*> node_map;
        Node * get_node(int x);
        Node * find(Node * x);

    public:
        void add(int x);
        void merge(int x, int y);
        bool conn(int x, int y);
};

#endif
