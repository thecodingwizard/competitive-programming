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

vector<int> adj[800000];
int par[800000][20];
int depth[800000];
int minDepth[800000];

void dfs(int u, int p, int d = 0) {
    depth[u] = d;
    minDepth[u] = d;
    par[u][0] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d+1);
        }
    }
}

void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u);
            minDepth[u] = min(minDepth[u], minDepth[v]);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 19; ~i; i--) {
        if (depth[par[a][i]] >= depth[b]) {
            a = par[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 19; ~i; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    assert(par[a][0] == par[b][0]);
    return par[a][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";

        int n; cin >> n;
        for (int i = 0; i < n; i++) adj[i].clear();
        for (int i = 0; i < n-1; i++) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].pb(b); adj[b].pb(a);
        }

        dfs(0, 0);
        for (int d = 1; d < 20; d++) {
            for (int i = 0; i < n;i ++) {
                par[i][d] = par[par[i][d-1]][d-1];
            }
        }

        map<int, vector<int>> freqs;
        for (int i = 0; i < n; i++) {
            int f; cin >> f; freqs[f].pb(i);
        }
        for (auto &x : freqs) {
            for (int i = 1; i < x.s.size(); i++) {
                int a = x.s[0], b = x.s[i];
                assert(a != b);
                int y = lca(a, b);
                minDepth[a] = min(minDepth[a], depth[y]);
                minDepth[b] = min(minDepth[b], depth[y]);
            }
        }
        dfs2(0, 0);

        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (minDepth[i] == depth[i]) ans++;
        }
        cout << ans << endl;
    }

    return 0;
}
