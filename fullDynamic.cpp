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

    int capacity = 1;
    for (int i = 0; i < ett.size(); i++) capacity <<= 1;
    if (capacity <= nodes.size()) {
        ett.push_back(EulerTourTree());
        adj.push_back(std::unordered_map<int, std::unordered_set<int> >());
    }
}

void FullDynamic::add_edge_level(int x, int y, int level, bool ins_adj) {
    if (x > y) std::swap(x, y);
    edge_levels[std::make_pair(x, y)] = level;

    if (ins_adj) {
        adj[level][x].insert(y);
        adj[level][y].insert(x);
        ett[level].update_num(x, 1);
        ett[level].update_num(y, 1);
    }
}

void FullDynamic::remove_edge_level(int x, int y) {
    if (x > y) std::swap(x, y);
    std::pair<int, int> p = std::make_pair(x, y);
    auto it = edge_levels.find(p);
    if (it == edge_levels.end()) return;

    int level = it->second;
    edge_levels.erase(it);

    adj[level][x].erase(y);
    adj[level][y].erase(x);

    ett[level].update_num(x, -1);
    ett[level].update_num(y, -1);
}

int FullDynamic::get_edge_level(int x, int y) {
    if (x > y) std::swap(x, y);
    auto it = edge_levels.find(std::make_pair(x, y));
    if (it == edge_levels.end()) return -1;
    return it->second;
}

/*
   Only allowed to link x and y if x and y already exist
*/
void FullDynamic::link(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return;

    if (!ett[0].conn(x, y)) {
        ett[0].link(x, y);
        add_edge_level(x, y, 0, false);
    } else add_edge_level(x, y, 0, true);
}

void FullDynamic::cut(int x, int y) {
    int level = get_edge_level(x, y);
    assert(level == 0);

    // (x, y) doesn't exist
    if (level == -1) return;

    remove_edge_level(x, y);

    // continue only if (x, y) removed
    if (!ett[level].cut(x, y)) return;
    for (int i = level - 1; i >= 0; i--) {
        assert(ett[i].cut(x, y));
    }

    for (int i = level; i >= 0; i--) {
        int size_x = ett[i].get_size(x);
        int size_y = ett[i].get_size(y);

        if (size_x > size_y) std::swap(x, y);

        bool found = false;
        while (!found) {
            int a = ett[i].get_positive_num(x);

            assert(a == -1);

            // looped through all such numbers
            if (a == -1) return;

            assert(!adj[i][a].empty());

            std::vector<int> rem;

            auto it = adj[i][a].begin();
            for (; it != adj[i][a].end(); it++) {
                int b = *it;
                if (ett[i].conn(b, y)) {
                    for (int j = 0; j <= i; j++)
                        ett[j].link(a, b);
                    found = true;
                    adj[i][a].erase(b);
                    adj[i][b].erase(a);
                    break;
                } else {
                    rem.push_back(b);
                    remove_edge_level(a, b);
                    add_edge_level(a, b, i + 1, true);
                }
            }
        }

        if (found) break;
    }
}

bool FullDynamic::conn(int x, int y) {
    if (!nodes.count(x) || !nodes.count(y)) return false;
    return ett[0].conn(x, y);
}

