#include "linkCutTree.h"
#include <iostream>
#include <algorithm>

bool LinkCutTree::d(int x) {
    return x == c[1][p[x]];
}

bool LinkCutTree::r(int x) {
    return !p[x] || x != c[LinkCutTree::d(x)][p[x]];
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
    bool b = LinkCutTree::d(x);
    int ch = c[!b][x], pa = p[x], gp = p[pa];
    if (!LinkCutTree::r(pa)) c[LinkCutTree::d(pa)][gp] = x;
    c[!b][x] = pa, c[b][pa] = ch;
    p[ch] = pa, p[pa] = x, p[x] = gp;
}

void LinkCutTree::splay(int x) {
    while (!LinkCutTree::r(x)) {
        int pa = p[x], gp = p[pa];
        if (!LinkCutTree::r(pa)) LinkCutTree::push(gp); LinkCutTree::push(pa); LinkCutTree::push(x);
        if (!LinkCutTree::r(pa)) {
            if (LinkCutTree::d(x) == LinkCutTree::d(pa)) LinkCutTree::rot(pa);
            else LinkCutTree::rot(x);
        } LinkCutTree::rot(x);
        std::cout << "Splay " << x << '\n';
        std::cout << "Parent " << p[x] << '\n';
        if (p[x]) std::cout << "Child'o parent " << c[LinkCutTree::d(x)][p[x]];
    } LinkCutTree::push(x);
}

void LinkCutTree::access(int x) {
    int y = x, last = 0;
    while (y) {
        std::cout << "access " << y << '\n';
        LinkCutTree::splay(y);
        c[1][y] = last;
        last = y;
        y = p[y];
    } LinkCutTree::splay(x);
}

void LinkCutTree::reroot(int x) {
    LinkCutTree::access(x);
    f[x] ^= 1;
}

void LinkCutTree::link(int a, int b) {
    LinkCutTree::reroot(a);
    p[a] = b;
}

void LinkCutTree::cut(int a, int b) {
    LinkCutTree::reroot(a);
    LinkCutTree::access(b);
    LinkCutTree::splay(a);
    c[1][a] = 0;
    p[b] = 0;
}

bool LinkCutTree::conn(int a, int b) {
    LinkCutTree::reroot(a);
    LinkCutTree::access(b);
    return p[a];
}
