/*
 * Note that if there are no cycles, then we are simply left with a forest of trees.
 * It must be a tree because there can only be one path from one node to another.
 * We can then use tree DP to easily find the number of nodes a particular node can reach.
 *
 * To deal with cycles, we compress all the strongly connected components into one node.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair

int n, m; 
vector<int> adj[50000];
vector<int> radj[50000];
vector<int> sccAdj[50000];
int memo[50000];
int scc[50000], sccSz[50000];

int dfs(int u) {
    if (memo[u] != -1) return memo[u];
    int tot = sccSz[u]-1;
    for (int v : sccAdj[u]) {
        tot += dfs(v) + 1;
    }
    return memo[u] = tot;
}

bool vis[50000];
vector<int> todo;
void dfs1(int x) {
    vis[x] = true;
    for (int y : adj[x]) {
        if (!vis[y]) dfs1(y);
    }
    todo.pb(x);
}

void dfs2(int x, int v) {
    scc[x] = v;
    sccSz[v]++;
    for (int y : radj[x]) {
        if (scc[y] == -1) dfs2(y, v);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        radj[b].pb(a);
    }

    for (int i = 0; i < n; i++) {
        scc[i] = -1;
        if (!vis[i]) {
            dfs1(i);
        }
    }
    reverse(todo.begin(), todo.end());
    for (int x : todo) {
        if (scc[x] == -1) {
            dfs2(x, x);
        }
    }
    for (int i = 0; i < n; i++) {
        int x = scc[i];
        for (int y : adj[i]) {
            if (scc[y] != scc[i]) sccAdj[x].pb(scc[y]);
        }
        sort(sccAdj[x].begin(), sccAdj[x].end());
        sccAdj[x].erase(unique(sccAdj[x].begin(), sccAdj[x].end()), sccAdj[x].end());
    }

    for (int i = 0; i < n; i++) {
        memo[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        cout << dfs(scc[i]) << endl;
    }

    return 0;
}
