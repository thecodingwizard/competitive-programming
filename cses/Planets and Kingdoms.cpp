#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000;

#define pb push_back

vector<int> adj[maxn], radj[maxn];
vector<bool> vis(maxn, 0);

vector<int> S;
void dfs1(int u) {
    if (vis[u]) return; vis[u] = 1;
    for (int v : adj[u]) {
        dfs1(v);
    }
    S.pb(u);
}

vector<int> scc(maxn, 0);
void dfs2(int u, int r) {
    if (scc[u] > 0) return;
    scc[u] = r;
    for (int v : radj[u]) {
        dfs2(v, r);
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b); radj[b].pb(a);
    }

    for (int i = 0; i < n; i++) dfs1(i);
    reverse(S.begin(), S.end());
    int ctr = 0;
    for (int x : S) {
        if (scc[x] == 0) dfs2(x, ++ctr);
    }
    cout << ctr << endl;
    for (int i = 0; i < n; i++) cout << scc[i] << " \n"[i == n-1];

    return 0;
}
