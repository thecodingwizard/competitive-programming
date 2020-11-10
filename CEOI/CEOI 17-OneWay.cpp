/*
 * See: https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/CEOI/17-OneWay.cpp
 *
 * Note that the graph can be disconnected.
 *
 * Union all nodes connected by an edge that's not a bridge
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
vector<ii> adj[maxn];
bool vis[maxn];
int pa[maxn];
int depth[maxn];
bool isBridge[maxn];

int dfs(int u, int parent, int parentEdge) {
    //cout << "DFS: " << u << " " << parent << endl;
    pa[u] = parent;
    if (parent != -1) {
        depth[u] = depth[parent]+1;
    }
    vis[u] = true;
    int numBackedges = 0;
    for (ii v : adj[u]) {
        if (v.s == parentEdge) continue;
        if (!vis[v.f]) {
            numBackedges += dfs(v.f, u, v.s);
        } else if (depth[v.f] > depth[u]) {
            numBackedges--;
        } else {
            assert(depth[v.f] < depth[u]);
            numBackedges++;
        }
    }
    assert(numBackedges >= 0);
    if (u == 0) assert(numBackedges == 0);
    isBridge[parentEdge] = numBackedges == 0;
    return numBackedges;
}

int ufpa[maxn];
int sz[maxn];
int get(int x) {
    return ufpa[x] == x ? x : ufpa[x] = get(ufpa[x]);
}
void unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    ufpa[a] = b;
    sz[b] += sz[a];
}

vector<ii> adj2[maxn];
int dir[maxn];
int val[maxn];

int dfs2(int u, int p, int paEdge = 0) {
    vis[u] = true;
    int score = val[u];
    for (ii v : adj2[u]) {
        if (v.f != p) score += dfs2(v.f, u, v.s);
    }
    if (paEdge == 0) {
        return 0;
    }
    if (score == 0) {
        if (paEdge != 0) dir[abs(paEdge)-1] = 0;
    } else if (score > 0) {
        // parent edge going down
        if (paEdge > 0) {
            dir[paEdge-1] = 1;
        } else if (paEdge < 0) {
            dir[-paEdge-1] = 2;
        } else {
            assert(false);
        }
    } else {
        // parent edge going up
        if (paEdge > 0) {
            dir[paEdge-1] = 2;
        } else if (paEdge < 0) {
            dir[-paEdge-1] = 1;
        } else {
            assert(false);
        }
    }
    return score;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    vector<ii> edges;
    F0R(i, m) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(mp(b, i));
        adj[b].pb(mp(a, i));
        edges.pb(mp(a, b));
    }

    F0R(i, n) {
        if (!vis[i]) {
            depth[i] = 0;
            dfs(i, -1, -1);
        }
    }

    F0R(i, n) {
        ufpa[i] = i;
        sz[i] = 1;
    }
    F0R(i,m) {
        if (!isBridge[i]) {
            unite(edges[i].f, edges[i].s);
            //cout << "UNITE " << edges[i].f << " " << edges[i].s << endl;
            dir[i] = 0;
        }
    }

    F0R(i, m) {
        ii newEdge = mp(get(edges[i].f), get(edges[i].s));
        if (newEdge.f == newEdge.s) {
            assert(!isBridge[i]);
            continue;
        }
        assert(isBridge[i]);
        adj2[newEdge.f].pb(mp(newEdge.s, i+1));
        adj2[newEdge.s].pb(mp(newEdge.f, -(i+1)));
    }

    int p; cin >> p;
    F0R(i, p) {
        int a, b; cin >> a >> b; --a; --b;
        a = get(a), b = get(b);
        if (a == b) continue;
        val[a]--; val[b]++;
    }

    fill(vis, vis+n, false);
    F0R(i, n) {
        if (!vis[get(i)]) dfs2(get(i), get(i));
    }

    F0R(i, m) {
        cout << "BRL"[dir[i]];
    }
    cout << endl;

    return 0;
}
