/*
 * Same solution as editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/JOI/official/JOIOC/2018/catdog.pdf
 */

#include <bits/stdc++.h>
#include "catdog.h"

using namespace std;

#define vi vector<int>
#define pb push_back

#define maxn 100000

int n;
vi adj[maxn], rpos;
int par[maxn], root[maxn], depth[maxn], sz[maxn], ti;
int hlLen[maxn];
int hlPos[maxn];
int pos[maxn];
int state[maxn+1];

struct node {
    int catcat, catdog = maxn, dogcat = maxn, dogdog;
};

struct SegTree {
    int catcat, catdog, dogcat, dogdog;
    vector<node> nodes;
    int n;
    void init(int sz) {
        n = sz;
        nodes.resize(4*sz);
    }
    void upd(int p, int i, int j, int u, int cc, int cd, int dc, int dd) {
        if (i > u || j < u) return;
        if (i == j && i == u) {
            nodes[p].catcat += cc;
            nodes[p].catdog += cd;
            nodes[p].dogcat += dc;
            nodes[p].dogdog += dd;
            return;
        }
        upd(p*2, i, (i+j)/2, u, cc, cd, dc, dd);
        upd(p*2+1, (i+j)/2+1, j, u, cc, cd, dc, dd);
        nodes[p].catcat = min(min(nodes[p*2].catcat, nodes[p*2].catdog+1) + nodes[p*2+1].catcat, min(nodes[p*2].catcat+1, nodes[p*2].catdog) + nodes[p*2+1].dogcat);
        nodes[p].catdog = min(min(nodes[p*2].catcat, nodes[p*2].catdog+1) + nodes[p*2+1].catdog, min(nodes[p*2].catcat+1, nodes[p*2].catdog) + nodes[p*2+1].dogdog);
        nodes[p].dogdog = min(min(nodes[p*2].dogcat, nodes[p*2].dogdog+1) + nodes[p*2+1].catdog, min(nodes[p*2].dogcat+1, nodes[p*2].dogdog) + nodes[p*2+1].dogdog);
        nodes[p].dogcat = min(min(nodes[p*2].dogcat, nodes[p*2].dogdog+1) + nodes[p*2+1].catcat, min(nodes[p*2].dogcat+1, nodes[p*2].dogdog) + nodes[p*2+1].dogcat);
    }
    void upd(int u, int cc, int cd, int dc, int dd) {
        upd(1, 0, n-1, u, cc, cd, dc, dd);
        catcat = nodes[1].catcat;
        catdog = nodes[1].catdog;
        dogcat = nodes[1].dogcat;
        dogdog = nodes[1].dogdog;
    }
};

SegTree st[maxn];

void dfsSz(int x) {
    sz[x] = 1;
    for (int &v : adj[x]) {
        par[v] = x; depth[v] = depth[x] + 1;
        adj[v].erase(find(adj[v].begin(), adj[v].end(), x));
        dfsSz(v); sz[x] += sz[v];
        if (sz[v] > sz[adj[x][0]]) swap(v, adj[x][0]);
    }
}

void dfsHld(int x) {
    hlPos[x] = hlLen[root[x]]++;
    pos[x] = ti++; rpos.pb(x);
    for (int v : adj[x]) {
        root[v] = (v == adj[x][0] ? root[x] : v);
        dfsHld(v);
    }
}

void process(int x, int catcat, int catdog, int dogcat, int dogdog) {
    for (; ; x = par[root[x]]) {
        int prevcatcat = min(st[root[x]].catcat, min(st[root[x]].catdog, min(st[root[x]].dogcat+1, st[root[x]].dogdog+1)));
        int prevdogdog = min(st[root[x]].catcat+1, min(st[root[x]].catdog+1, min(st[root[x]].dogcat, st[root[x]].dogdog)));
        st[root[x]].upd(hlPos[x], catcat, catdog, dogcat, dogdog);
        catcat = min(st[root[x]].catcat, min(st[root[x]].catdog, min(st[root[x]].dogcat+1, st[root[x]].dogdog+1)));
        dogdog = min(st[root[x]].catcat+1, min(st[root[x]].catdog+1, min(st[root[x]].dogcat, st[root[x]].dogdog)));
        catcat -= prevcatcat;
        dogdog -= prevdogdog;
        if (root[x] == 0) return;
    }
}

void initialize(int N, vi A, vi B) {
    n = N;
    for (int i = 0; i < n-1; i++) {
        adj[A[i]-1].pb(B[i]-1);
        adj[B[i]-1].pb(A[i]-1);
    }
    par[0] = depth[0] = ti = 0; dfsSz(0);
    root[0] = 0; dfsHld(0);
    for (int i = 0; i < n; i++) {
        if (root[i] == i) {
            st[i].init(hlLen[i]);
        }
    }
}

int cat(int v) {
    state[v] = 1;
    process(v-1, 0, 0, 0, maxn);
    return min(st[0].catcat, min(st[0].catdog, min(st[0].dogdog, st[0].dogcat)));
}

int dog(int v) {
    state[v] = 2;
    process(v-1, maxn, 0, 0, 0);
    return min(st[0].catcat, min(st[0].catdog, min(st[0].dogdog, st[0].dogcat)));
}

int neighbor(int v) {
    process(v-1, state[v] == 2 ? -maxn : 0, 0, 0, state[v] == 1 ? -maxn : 0);
    state[v] = 0;
    return min(st[0].catcat, min(st[0].catdog, min(st[0].dogdog, st[0].dogcat)));
}
