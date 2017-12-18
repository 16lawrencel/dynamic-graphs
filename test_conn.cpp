// simple random test
#include "ds.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

std::vector<std::multiset<int> > adj;
std::vector<std::pair<int, int> > edges;
std::vector<bool> vis;

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int y : adj[x]) dfs(y);
}

bool check_conn(int a, int b) {
    int n = adj.size() - 1;
    for (int i = 1; i <= n; i++) vis[i] = false;

    dfs(a);
    return vis[b];
}

int main() {
    std::srand(0);

    int n = 500;
    int m = 10000;

    adj.resize(n + 1);
    vis.resize(n + 1);

    FullDynamic ds = FullDynamic();
    for (int i = 1; i <= n; i++) ds.add(i);

    for (int i = 0; i < m; i++) {
        if (edges.empty() || rand() % 3 <= 1) {
            int a, b;
            do {
                a = rand() % n + 1, b = rand() % n + 1;
            } while (a == b);

            printf("Linking %d %d\n", a, b);

            ds.link(a, b);
            adj[a].insert(b);
            adj[b].insert(a);
            edges.push_back(std::make_pair(a, b));
            
        } else {
            int ind = rand() % edges.size();
            int a = edges[ind].first, b = edges[ind].second;

            printf("Deleting %d %d\n", a, b);

            ds.cut(a, b);
            adj[a].erase(adj[a].find(b));
            adj[b].erase(adj[b].find(a));
            edges.erase(edges.begin() + ind);
        }

        for (int j = 0; j < 10; j++) {
            int a = rand() % n + 1, b = rand() % n + 1;
            bool ds_res = ds.conn(a, b);
            bool dfs_res = check_conn(a, b);

            printf("  Query %d %d\n", a, b);
            printf("    Got: %s\n", ds_res ? "true" : "false");
            printf("    Expected: %s\n", dfs_res ? "true" : "false");
            assert(ds_res == dfs_res);
        }
    }
}
