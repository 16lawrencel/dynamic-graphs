// simple random test
// uses tarjan's two-edge connectivity algorithm as slow diff
#include "ds.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>

std::vector<std::vector<int> > adj;
std::vector<int> ind;
std::vector<int> lowlink;
std::vector<int> par;
int cnt;

void dfs(int x, int p = -1) {
    ind[x] = lowlink[x] = cnt++;
    par[x] = p;
    for (int y : adj[x]) {
        if (y == p) {
            p = -1;
            continue;
        }

        //if (ind[y] != -1) printf("%d %d\n", x, y);

        if (ind[y] == -1) {
            dfs(y, x);
            lowlink[x] = std::min(lowlink[x], lowlink[y]);
        } else {
            lowlink[x] = std::min(lowlink[x], ind[y]);
        }
    }
}

bool run_tarjan(int a, int b) {
    int n = adj.size() - 1;
    for (int i = 1; i <= n; i++) {
        ind[i] = lowlink[i] = -1;
    }
    cnt = 0;

    dfs(a);

    // not connected
    if (ind[b] == -1) return false;

    while (b != a) {
        // b->par[b] is a bridge
        if (lowlink[b] == ind[b]) return false;
        b = par[b];
    }

    return true;
}

int main() {
    std::srand(1);

    int n = 500;
    int m = 1000;

    adj.resize(n + 1);
    ind.resize(n + 1);
    lowlink.resize(n + 1);
    par.resize(n + 1);

    TwoEdgeDynamic ds = TwoEdgeDynamic();
    for (int i = 1; i <= n; i++) ds.add(i);

    for (int i = 0; i < m; i++) {
        int a, b;
        do {
            a = rand() % n + 1, b = rand() % n + 1;
        } while (a == b);

        printf("Updating %d %d\n", a, b);

        ds.link(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
        for (int j = 0; j < 100; j++) {
            int a = rand() % n + 1, b = rand() % n + 1;
            bool ds_res = ds.two_edge_conn(a, b);
            /*
            if (a == 16 && b == 8) {
                ds.lct.print_path(a, b);

                bool tarjan_res = run_tarjan(a, b);
                return 0;
            }
            */
            bool tarjan_res = run_tarjan(a, b);

            printf("  Query %d %d\n", a, b);
            printf("    Got: %s\n", ds_res ? "true" : "false");
            printf("    Expected: %s\n", tarjan_res ? "true" : "false");
            assert(ds_res == tarjan_res);
        }
    }
}

