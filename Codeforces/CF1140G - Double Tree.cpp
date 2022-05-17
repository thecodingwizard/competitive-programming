#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define f first
#define ii pair<int, int>
#define s second
#define pll pair<ll, ll>
#define pb push_back
#define mp make_pair
#define inf (1LL<<59)
#define all(x) x.begin(), x.end()
#define sz(x) x.size()

const int maxn = 300000;

int n, q; 
ll crossDist[maxn];
vector<pair<int, pll>> adj[maxn];

void setMinDist() {
    vector<ll> d(n, inf);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for (int i = 0; i < n; i++) {
        d[i] = crossDist[i];
        pq.push(mp(d[i], i));
    }
    while (!pq.empty()) {
        pair<ll, int> u = pq.top(); pq.pop();
        if (d[u.s] < u.f) continue;
        for (auto x : adj[u.s]) {
            if (d[x.f] > u.f + x.s.f + x.s.s) {
                d[x.f] = u.f + x.s.f + x.s.s;
                pq.push(mp(d[x.f], x.f));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        crossDist[i] = d[i];
    }
}

int s[maxn]; // size of subtree
bool r[maxn]; // removed
int parent[maxn], depth[maxn]; // parent and depth of lca tree
vector<int> nodesInCentroid[maxn];
vector<array<ll, 2>> dist[maxn][2];
void dfs(int u, int p) {
    s[u] = 1;
    for (auto v : adj[u]) {
        if (v.f != p && !r[v.f]) {
            dfs(v.f, u);
            s[u] += s[v.f];
        }
    }
}

int getI(int node, int centroid) {
    auto it = lower_bound(all(nodesInCentroid[centroid]), node);
    assert(it != nodesInCentroid[centroid].end());
    return it - nodesInCentroid[centroid].begin();
}

void calcDistances(int centroid, int isRight) {
    vector<array<ll, 2>> &d = dist[centroid][isRight];
    d.resize(sz(nodesInCentroid[centroid]));
    for (int i = 0; i < sz(nodesInCentroid[centroid]); i++) {
        d[i][0] = d[i][1] = inf;
    }
    priority_queue<pair<ll, ii>, vector<pair<ll, ii>>, greater<pair<ll, ii>>> pq;
    d[getI(centroid, centroid)][isRight] = 0;

    pq.push(mp(0, mp(centroid, isRight)));
    while (!pq.empty()) {
        pair<ll, ii> u = pq.top(); pq.pop();
        int idx = getI(u.s.f, centroid);
        if (d[idx][u.s.s] < u.f) continue;

        // any adjacent elements + go across
        if (d[idx][!u.s.s] > d[idx][u.s.s] + crossDist[u.s.f]) {
            d[idx][!u.s.s] = d[idx][u.s.s] + crossDist[u.s.f];
            pq.push(mp(d[idx][!u.s.s], mp(u.s.f, !u.s.s)));
        }
        for (auto v : adj[u.s.f]) {
            if (r[v.f]) continue;
            ll edgeDist;
            if (u.s.s == 0) {
                // left
                edgeDist = v.s.f;
            } else {
                // right
                edgeDist = v.s.s;
            }
            int idx2 = getI(v.f, centroid);
            if (d[idx2][u.s.s] > d[idx][u.s.s] + edgeDist) {
                d[idx2][u.s.s] = d[idx][u.s.s] + edgeDist;
                pq.push(mp(d[idx2][u.s.s], mp(v.f, u.s.s)));
            }
        }
    }
}

int getCentroid(int u, int p, int totSz) {
    for (auto v : adj[u]) {
        if (!r[v.f] && v.f != p) {
            if (s[v.f] * 2 > totSz) return getCentroid(v.f, u, totSz);
        }
    }
    return u;
}

void dfsNodesList(int u, int p, int root) {
    nodesInCentroid[root].pb(u);
    for (auto v : adj[u]) {
        if (v.f != p && !r[v.f]) dfsNodesList(v.f, u, root);
    }
}

void centroid(int u, int p, int d) {
    dfs(u, -1);

    u = getCentroid(u, u, s[u]);
    dfsNodesList(u, u, u);
    parent[u] = p;
    depth[u] = d;

    // from every centroid, find distance from every node to that centroid
    // (and the corresponding centroid on the other side)
    sort(all(nodesInCentroid[u]));
    calcDistances(u, 0);
    calcDistances(u, 1);
    
    r[u] = 1;
    for (auto v : adj[u]) {
        if (!r[v.f]) centroid(v.f, u, d+1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> crossDist[i];
    }
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x; --y;
        ll w1, w2; cin >> w1 >> w2;
        adj[x].pb(mp(y, mp(w1, w2)));
        adj[y].pb(mp(x, mp(w1, w2)));
    }

    cin >> q;

    // step 1: update min dist to cross over
    setMinDist();

    // step 2: run centroid decomposition.
    // from every centroid, find distance from every node to that centroid
    // (and the corresponding centroid on the other side)
    centroid(0, 0, 0);


    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        int isURight = u % 2 == 0;
        int isVRight = v % 2 == 0;
        --u; --v; u /= 2; v /= 2;

        if (depth[u] > depth[v]) {
            swap(u, v);
            swap(isURight, isVRight);
        }

        int v2 = v;
        while (depth[v2] > depth[u]) v2 = parent[v2];

        int u2 = u;
        while (u2 != v2) u2 = parent[u2], v2 = parent[v2];

        int centroid = u2;
        int ui = getI(u, centroid);
        int vi = getI(v, centroid);
        ll uToC1 = dist[centroid][0][ui][isURight];
        ll uToC2 = dist[centroid][1][ui][isURight];
        ll vToC1 = dist[centroid][0][vi][isVRight];
        ll vToC2 = dist[centroid][1][vi][isVRight];

        cout << min(uToC1 + vToC1, uToC2 + vToC2) << "\n";
    }

    return 0;
}

