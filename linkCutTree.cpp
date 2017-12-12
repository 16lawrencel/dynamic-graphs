#include "linkCutTree.h"
#include <iostream>
#include <algorithm>
#include <cassert>

bool LinkCutTree::d(int x) {
    return x == c[1][p[x]];
}

bool LinkCutTree::r(int x) {
    return !p[x] || x != c[d(x)][p[x]];
}

void LinkCutTree::push(int x) {
    if (f[x]) {
        std::swap(c[0][x], c[1][x]);

        f[c[0][x]] ^= 1;
        f[c[1][x]] ^= 1;
        f[x] = 0;
    }
}

void LinkCutTree::rot(int x) {
    bool b = d(x);
    int ch = c[!b][x], pa = p[x], gp = p[pa];
    if (!r(pa)) c[d(pa)][gp] = x;
    c[!b][x] = pa, c[b][pa] = ch;
    p[ch] = pa, p[pa] = x, p[x] = gp;
}

void LinkCutTree::splay(int x) {
    while (!r(x)) {
        int pa = p[x], gp = p[pa];
        if (!r(pa)) push(gp); push(pa); push(x);
        if (!r(pa)) {
            if (d(x) == d(pa)) rot(pa);
            else rot(x);
        } rot(x);
    } push(x);
}

void LinkCutTree::access(int x) {
    int y = x, last = 0;
    while (y) {
        splay(y);
        c[1][y] = last;
        last = y;
        y = p[y];
    } splay(x);
}

void LinkCutTree::reroot(int x) {
    access(x);
    f[x] ^= 1;
}

void LinkCutTree::link(int a, int b) {
    assert(!conn(a, b));
    reroot(a);
    p[a] = b;
}

void LinkCutTree::cut(int a, int b) {
    assert(conn(a, b));
    reroot(a);
    access(b);
    splay(a);
    c[1][a] = 0;
    p[b] = 0;
}

bool LinkCutTree::conn(int a, int b) {
    reroot(a);
    access(b);
    return p[a];
}
