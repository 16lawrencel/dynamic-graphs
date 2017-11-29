#ifndef FullDynamic_H
#define FullDynamic_H

#include "eulerTourTree.h"

#include <unordered_map>
#include <vector>
#include <set>
#include <utility>

class FullDynamic {
    private:
        std::set<int> nodes;
        std::vector<EulerTourTree> ett;
        std::vector<std::unordered_map<int, std::set<int> > > adj; // adjacency list

        struct pair_hash {
            template <class T1, class T2>
                std::size_t operator() (const std::pair<T1, T2> &p) const {
                    auto h1 = std::hash<T1>{}(p.first);
                    auto h2 = std::hash<T2>{}(p.second);

                    return int(1e9 + 7) * h1 + h2;
                }
        };

        std::unordered_map<std::pair<int, int>, int, pair_hash> edge_levels;

        void add_edge_level(int x, int y, int level);
        void remove_edge_level(int x, int y);
        int get_edge_level(int x, int y);

    public:
        void add(int x);
        void link(int x, int y);
        void cut(int x, int y);
        bool conn(int x, int y);
};

#endif
