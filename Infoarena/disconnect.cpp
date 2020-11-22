/*
 * Strategy to answering a query (a, b):
 * - Define goUp(x) = highest parent node of x that doesn't go through a deleted edge
 * - if goUp(a) == goUp(b) then a and b are connected
 *
 * To handle deleted edges, maintain a binary indexed tree from 1...n.
 * Do a euler tour of the tree.
 * To delete an edge (x, y) where x is the parent of y, we do:
 * - update(in[y], 1)
 * - update(out[y], -1)
 * Essentially every node in the subtree of y will have one added to it.
 *
 * To find goUp(x), we build an LCA table. We can jump from x to an ancestor of x
 * if qry(in[x]) == qry(in[ancestor of x]). In other words, if the value the node x
 * equals the value of the node of the ancestor, then there's a valid path between them.
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

#define maxn 100000
int n, m; 
vector<int> adj[maxn];

int timer = 0;
int tin[maxn], tout[maxn];
int pa[maxn][20];
void dfs(int u, int p) {
    tin[u] = timer++;
    pa[u][0] = p;
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
    tout[u] = timer;
}

int bit[maxn+10];
int qry(int k) {
    int s = 0;
    while (k) {
        s += bit[k];
        k -= k&-k;
    }
    return s;
}
void upd(int k, int v) {
    while (k <= maxn) {
        bit[k] += v;
        k += k&-k;
    }
}

int goUp(int x) {
    for (int i = 19; ~i; i--) {
        if (qry(tin[x]) == qry(tin[pa[x][i]])) {
            x = pa[x][i];
        }
    }
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("disconnect.in", "r", stdin);
    freopen("disconnect.out", "w", stdout);

    cin >> n >> m;
    F0R(i, n-1) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }

    dfs(0, 0);
    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < n; j++) {
            pa[j][i] = pa[pa[j][i-1]][i-1];
        }
    }

    int V = 0;
    F0R(i, m) {
        int t, x, y; cin >> t >> x >> y;
        x ^= V, y ^= V;
        if (t == 1) {
            // remove edge (x, y)
            --x; --y;
            if (pa[x][0] == y) swap(x, y);
            assert(pa[y][0] == x);
            upd(tin[y], 1); upd(tout[y], -1);
        } else {
            if (goUp(x-1) == goUp(y-1)) {
                cout << "YES\n";
                V = x;
            } else {
                cout << "NO\n";
                V = y;
            }
        }
    }

    return 0;
}
