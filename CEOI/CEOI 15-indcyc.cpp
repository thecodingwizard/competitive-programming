/*
 * See: https://github.com/luciocf/Problems/blob/master/CEOI/CEOI%202015/potemkin.cpp
 *
 * Basically, convert each edge (u, v) into two nodes, one representing (u, v) and
 * the other representing (v, u).
 *
 * Then, if in the original graph edges (u, v) and (v, w) exist and u is not
 * connected to w, then connect nodes (u, v) and (v, w) in the new graph with an edge.
 *
 * The resulting graph will not have any length 3 cycles. All that remains is to
 * check for a cycle in the new graph.
 */

#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define ii pair<int, int>
#define f first
#define s second
#define vii vector<ii>

vii adj[1000];
bool conn[1000][1000];
ii edges[200000];
vi adj2[200000];
bool vis[200000], active[200000];

vector<int> S;
void dfs(int u, int p) {
    if (active[u]) {
        while (true) {
            int x = S.back(); S.pop_back();
            cout << edges[x].s+1 << " ";
            if (x == u) break;
        }
        cout << endl;
        exit(0);
    }
    if (vis[u]) return;
    vis[u] = true;
    active[u] = true;
    S.push_back(u);
    for (auto v : adj2[u]) {
        if (v != p) dfs(v, u);
    }
    S.pop_back();
    active[u] = false;
}

int main() {
    int n, r; cin >> n >> r;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) conn[i][j] = false;

    for (int i = 0; i < r; i++) {
        int a, b; cin >> a >> b; --a; --b;
        conn[a][b] = true;
        conn[b][a] = true;
        edges[2*i] = {a,b};
        edges[2*i+1] = {b,a};
        adj[a].push_back({b,2*i});
        adj[b].push_back({a,2*i+1});
    }

    for (int i = 0; i < 2*r; i++) {
        vis[i] = active[i] = false;
        int a = edges[i].f, b = edges[i].s;
        for (auto v : adj[b]) {
            if (v.f == a || conn[a][v.f]) continue;
            adj2[i].push_back(v.s);
        }
    }

    for (int i = 0; i < 2*r; i++) {
        if (!vis[i]) dfs(i, i);
    }
    cout << "no" << endl;

    return 0;
}
