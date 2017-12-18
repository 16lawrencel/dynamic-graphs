#ifndef EulerTourTree_H
#define EulerTourTree_H

#include "splayTree.h"
#include <unordered_map>
#include <set>
#include <utility>

class EulerTourTree {
    private:
        std::unordered_map<int, std::set<Node*> > node_map;

        //https://stackoverflow.com/questions/32685540/c-unordered-map-with-pair-as-key-not-compiling
        struct pair_hash {
            template <class T1, class T2>
                std::size_t operator() (const std::pair<T1, T2> &p) const {
                    auto h1 = std::hash<T1>{}(p.first);
                    auto h2 = std::hash<T2>{}(p.second);

                    return int(((long long)(1e9 + 7)) * h1 + h2);
                }
        };

        std::unordered_map<std::pair<int, int>, Node*, pair_hash> edge_map;

        std::unordered_map<int, int> num_map;

        Node * get_node(int x);
        Node * get_edge(int x, int y);
        void add_node(int x, Node * node);
        void add_edge(int x, int y, Node * node);
        void remove_node(int x, Node * node);
        void remove_edge(int x, int y);

        void shift_to_front(Node * node);

    public:
        void add(int x);
        bool link(int x, int y);
        bool cut(int x, int y);
        bool conn(int x, int y);

        // used for fully dynamic connectivity and shouldn't be used for 
        // normal purposes
        int get_size(int x);
        int get_positive_num(int x);
        void update_num(int x, int d_num);
};

#endif
