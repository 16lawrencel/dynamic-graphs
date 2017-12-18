#include "fullDynamic.h"
#include <algorithm>
#include <cassert>

// we implement levels in reverse
// in particular, each edge starts at level 0, then
// increases in level
// this is for ease of implementation (and to allow insertion of nodes)
// this is also what the original paper did

void FullDynamic::add(int x) {
    nodes.insert(x);

    unsigned int capacity = 1;
    for (unsigned int i = 0; i < ett.size(); i++) capacity <<= 1;
    if (capacity <= nodes.size()) {
        ett.push_back(EulerTourTree());
        adj.push_back(std::unordered_map<int, std::unordered_multiset<int> >());
        tadj.push_back(std::unordered_map<int, std::unordered_multiset<int> >());
    }
}

void FullDynamic::add_edge_level(int x, int y, int level, bool tree_edge) {
    if (x > y) std::swap(x, y);
    edge_levels[std::make_pair(x, y)].insert(level);

    if (tree_edge) {
        tadj[level][x].insert(y);
        tadj[level][y].insert(x);
    } else {
        adj[level][x].insert(y);
        adj[level][y].insert(x);
    }

    ett[level].update_num(x, 1, tree_edge);
    ett[level].update_num(y, 1, tree_edge);
}

void FullDynamic::remove_edge_level(int x, int y, int level, bool tree_edge) {
    if (x > y) std::swap(x, y);
    std::pair<int, int> p = std::make_pair(x, y);
    edge_levels[p].erase(edge_levels[p].find(level));

    if (tree_edge) {
        tadj[level][x].erase(tadj[level][x].find(y));
        tadj[level][y].erase(tadj[level][y].find(x));
    } else {
        adj[level][x].erase(adj[level][x].find(y));
        adj[level][y].erase(adj[level][y].find(x));
    }

    ett[level].update_num(x, -1, tree_edge);
    ett[level].update_num(y, -1, tree_edge);

}

int FullDynamic::get_edge_level(int x, int y) {
    if (x > y) std::swap(x, y);
    auto it = edge_levels.find(std::make_pair(x, y));
    if (it == edge_levels.end()) return -1;
    return *it->second.rbegin();
}

/*
   Only allowed to link x and y if x and y already exist
*/
bool FullDynamic::link(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return false;
    
    if (!ett[0].conn(x, y)) {
        ett[0].link(x, y);
        add_edge_level(x, y, 0, true);
    } else add_edge_level(x, y, 0, false);

    return true;
}

bool FullDynamic::cut(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return false;

    int level = get_edge_level(x, y);

    // (x, y) doesn't exist
    if (level == -1) return false;

    // continue only if (x, y) removed
    if (!ett[0].cut(x, y)) {
        remove_edge_level(x, y, level, false);
        return true;
    }

    for (int i = level; i > 0; i--) {
        assert(ett[i].cut(x, y));
    }

    remove_edge_level(x, y, level, true);

    for (int i = level; i >= 0; i--) {
        int size_x = ett[i].get_size(x);
        int size_y = ett[i].get_size(y);

        if (size_x > size_y) std::swap(x, y);

        // push tree edges in x's tree to level i + 1
        while (true) {
            int a = ett[i].get_positive_num(x, true);

            if (a == -1) break;

            assert(!tadj[i][a].empty());
            
            while (!tadj[i][a].empty()) {
                int b = *tadj[i][a].begin();
                remove_edge_level(a, b, i, true);
                add_edge_level(a, b, i + 1, true);
                ett[i + 1].link(a, b);
            }
        }

        bool found = false;
        // we'll iterate over all non-tree edges (a, b) where 
        // a is in x's tree and b is in y's tree
        while (!found) {
            int a = ett[i].get_positive_num(x, false);

            // looped through all such numbers
            if (a == -1) {
                for (int b : nodes)
                    if (ett[i].conn(a, b))
                        assert(adj[i][b].empty());
                break;
            }

            assert(!adj[i][a].empty());

            while (!adj[i][a].empty()) {
                int b = *adj[i][a].begin();
                // if b is in y's tree, then we can add (a, b) as tree edge
                if (ett[i].conn(b, y)) {
                    for (int j = 0; j <= i; j++)
                        ett[j].link(a, b);
                    found = true;
                    remove_edge_level(a, b, i, false);
                    add_edge_level(a, b, i, true);
                    break;
                } else {
                    remove_edge_level(a, b, i, false);
                    add_edge_level(a, b, i + 1, false);
                }
            }
        }

        if (found) break;
    }

    return true;
}

bool FullDynamic::conn(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return false;
    if (x == y) return true;
    return ett[0].conn(x, y);
}
