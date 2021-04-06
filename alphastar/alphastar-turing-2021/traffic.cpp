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

int n; 
ll P[1000000];
vector<int> adj[1000000];
ll sz[1000000];

ll dfs1(int u, int p = 0) {
    sz[u] = P[u];
    for (int v : adj[u]) {
        if (v != p) sz[u] += dfs1(v, u);
    }
    return sz[u];
}

ll best = 1e18;
int bestAns = -1;
void dfs2(int u, int p = 0, ll par = 0) {
    ll childrenSum = 0;
    ll mxChild = 0;
    for (auto v : adj[u]) {
        if (v != p) {
            childrenSum += sz[v];
            mxChild = max(mxChild, sz[v]);
        }
    }
    if (best > max(par, mxChild)) {
        best = max(par, mxChild);
        bestAns = u;
    }
    for (auto v : adj[u]) {
        if (v != p) {
            dfs2(v, u, par+childrenSum-sz[v]+P[u]);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    F0R(i, n) cin >> P[i];
    F0R(i, n-1) {
        int s, d; cin >> s >> d;
        adj[s].pb(d);
        adj[d].pb(s);
    }

    dfs1(0);
    dfs2(0);
    cout << bestAns << endl;

    return 0;
}
