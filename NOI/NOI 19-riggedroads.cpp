/*
 * Loop through the edges in order; if the edge (a, b) is part of R, just assign the next
 * available number. Otherwise, all edges on the path from node a to node b in R need to have numbers less than the number of the edge (a, b).
 *
 * Using LCA we can split the path into two parts, then we can use DSU-like find function to efficiently move up the tree.
 *
 * See https://github.com/stefdasca/CompetitiveProgramming/blob/master/NOI-Singapore/NOI%2019-RiggedRoads.cpp for a more detailed explanation (or look at code)
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 300000

int n, e; 
vector<ii> adj[maxn];
vector<ii> edges;

int depth[maxn], pa[20][maxn];
int parentEdge[maxn];
void dfs(int u, int p, int d, int pEdge = -1) {
    depth[u] = d;
    pa[0][u] = p;
    parentEdge[u] = pEdge;
    for (auto x : adj[u]) {
        if (x.f != p) dfs(x.f, u, d+1, x.s);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) {
        if (depth[pa[i][a]] >= depth[b]) a = pa[i][a];
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (pa[i][a] != pa[i][b]) {
            a = pa[i][a];
            b = pa[i][b];
        }
    }
    return pa[0][a];
}

int val[maxn];
int ctr = 1;
vector<int> process;
int nxt[maxn];
int getNext(int x) {
    return parentEdge[nxt[x]] == -1 || val[parentEdge[nxt[x]]] == -1 ? nxt[x] : nxt[x] = getNext(nxt[x]);
}
void assign(int u, int stop) {
    while (depth[u] > depth[stop]) {
        if (val[parentEdge[u]] == -1) process.pb(parentEdge[u]);
        u = getNext(u);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> e;
    F0R(i, e) {
        int a, b; cin >> a >> b;
        --a; --b;
        edges.pb(mp(a, b));
    }
    for (int i = 0; i < n-1; i++) {
        int x; cin >> x; --x;
        adj[edges[x].f].pb(mp(edges[x].s, x));
        adj[edges[x].s].pb(mp(edges[x].f, x));
    }
    dfs(0, 0, 0);
    for (int i = 1; i < 20; i++) {
        F0R(j, n) {
            pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }

    fill(val, val+e, -1);
    F0R(i, e) {
        nxt[i] = pa[0][i];
    }
    F0R(i, e) {
        auto edge = edges[i];
        if (val[i] != -1) continue;
        int tgt = lca(edge.f, edge.s);
        assign(edge.f, tgt);
        assign(edge.s, tgt);
        sort(all(process));
        process.erase(unique(all(process)), process.end());
        for (int x : process) val[x] = ctr++;
        process.clear();
        if (val[i] == -1) val[i] = ctr++;
    }
    assert(ctr == e+1);
    F0R(i, e) cout << val[i] << " \n"[i == e-1];

    return 0;
}
