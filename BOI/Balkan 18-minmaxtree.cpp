/*
 * Same solution as editorial
 *
 * For each edge, we want to calculate the largest minimum value and the smallest maximum value out of
 * all the constraints; we can do this by sorting the constraints. Call the two values m and M.
 *
 * We can construct a bipartite graph where each edge is represented by a node, and each target value
 * is represented by a node. Draw an edge from an edge node to the node representing m, and another edge to the one representing M.
 *
 * We basically want to find the maximum matching w/ max flow (we need to match each value to one edge node).
 *
 * Used Dinic's for max flow, probably unnecessary :P
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
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 70000
vector<int> adj[maxn];
int pa[maxn][18];
int depth[maxn];
int m[maxn], M[maxn];

void dfs(int u, int p, int d) {
    pa[u][0] = p;
    depth[u] = d;
    for (int v : adj[u]) if (v != p) dfs(v, u, d+1);
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 17; ~i; i--) {
        if (depth[pa[a][i]] >= depth[b]) a = pa[a][i];
    }
    if (a == b) return a;
    for (int i = 17; ~i; i--) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    return pa[a][0];
}

struct FlowEdge {
    int to, rev;
    ll cap, flow;
};

struct Dinic {
    const ll flow_inf = 1e18;
    vector<vector<FlowEdge>> adj;
    int n;
    void init(int _n) {
        n = _n;
        adj.resize(n);
    }
    void add_edge(int u, int v, ll cap) {
        adj[u].pb(FlowEdge{v, sz(adj[v]), cap, 0LL});
        adj[v].pb(FlowEdge{u, sz(adj[u])-1, 0LL, 0LL});
    }
    vector<int> level, ptr;
    bool bfs(int s, int t) { // level = shortest distance from source
        level = ptr = vector<int>(n);
        level[s] = 1; queue<int> q({s});
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (auto e : adj[u]) {
                if (e.flow < e.cap && !level[e.to]) {
                    q.push(e.to); level[e.to] = level[u]+1;
                }
            }
        }
        return level[t];
    }
    ll dfs(int v, int t, ll flow) {
        if (v == t) return flow;
        for (int &i = ptr[v]; i < sz(adj[v]); i++) {
            FlowEdge &e = adj[v][i];
            ll diff = e.cap - e.flow;
            if (level[e.to] != level[v]+1 || !diff) continue;
            if (ll df = dfs(e.to, t, min(flow, diff))) {
                e.flow += df; adj[e.to][e.rev].flow -= df;
                return df;
            }
        }
        return 0;
    }
    ll maxFlow(int s, int t) {
        ll tot = 0;
        while (bfs(s, t)) {
            while (ll df = dfs(s, t, flow_inf)) tot += df;
        }
        return tot;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    F0R(i, n-1) {
        int x, y; cin >> x >> y; --x; --y;
        adj[x].pb(y); adj[y].pb(x);
    }
    dfs(0, 0, 0);
    FOR(i, 1, 18) {
        F0R(j, n) {
            pa[j][i] = pa[pa[j][i-1]][i-1];
        }
    }
    int k; cin >> k;
    vector<pair<int, ii>> minimum, maximum;
    F0R(i, k) {
        char c; cin >> c;
        int a, b, w; cin >> a >> b >> w; --a; --b;
        int l = lca(a, b);
        if (c == 'M') {
            maximum.pb(mp(w, mp(a, l)));
            maximum.pb(mp(w, mp(b, l)));
        } else {
            minimum.pb(mp(w, mp(a, l)));
            minimum.pb(mp(w, mp(b, l)));
        }
    }
    sort(all(maximum));
    sort(all(minimum));
    reverse(all(minimum));

    vector<int> nxt(n);
    F0R(i, n) nxt[i] = pa[i][0];
    F0R(i, n) M[i] = inf;
    for (auto event : maximum) {
        int v = event.f, a = event.s.f, b = event.s.s;
        vector<int> toUpd;
        while (depth[a] > depth[b]) {
            M[a] = min(M[a], v);
            toUpd.pb(a);
            a = nxt[a];
        }
        for (auto x : toUpd) {
            nxt[x] = a;
        }
    }
    F0R(i, n) nxt[i] = pa[i][0];
    F0R(i, n) m[i] = -1;
    for (auto event : minimum) {
        int v = event.f, a = event.s.f, b = event.s.s;
        vector<int> toUpd;
        while (depth[a] > depth[b]) {
            m[a] = max(m[a], v);
            toUpd.pb(a);
            a = nxt[a];
        }
        for (auto x : toUpd) {
            nxt[x] = a;
        }
    }
    set<int> values;
    FOR(i, 1, n) {
        values.insert(m[i]);
        values.insert(M[i]);
    }
    int ctr = 0;
    map<int, int> compress;
    map<int, int> compressRev;
    for (int x : values) {
        if (x >= 0 && x != inf) {
            compressRev[ctr] = x;
            compress[x] = ctr++;
        }
    }

    Dinic mf; mf.init(n+ctr+1);
    FOR(i, 1, n) {
        mf.add_edge(0, i, 1);
        // cout << i << "-->" << pa[i][0] << ": " << m[i] << " "<< M[i] << endl;
        if (compress.count(m[i])) mf.add_edge(i, n+compress[m[i]], 1);
        if (compress.count(M[i])) mf.add_edge(i, n+compress[M[i]], 1);
    }
    F0R(i, ctr) {
        mf.add_edge(n+i, n+ctr, 1);
    }
    mf.maxFlow(0, n+ctr);

    FOR(i, 1, n) {
        int numEdges = 0;
        for (auto e : mf.adj[i]) {
            if (e.flow <= 0) continue;
            cout << i+1 << " " << pa[i][0]+1 << " " << compressRev[e.to-n] << "\n";
            numEdges++;
        }
        assert(numEdges <= 1);
        if (numEdges == 0) {
            cout << i+1 << " " << pa[i][0]+1 << " " << m[i] << "\n";
        }
    }

    return 0;
}
