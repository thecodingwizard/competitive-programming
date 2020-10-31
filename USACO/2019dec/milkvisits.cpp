/*
 * Same sol as official editorial: http://www.usaco.org/current/data/sol_milkvisits_gold_dec19.html
 *
 * Also see milkvisits_2.cpp for a different impl that uses euler tour + compressed BIT
 */

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int n, m; 
int A[100000];
vector<int> adj[100000];
bool ans[100000];
vector<pair<int, ii>> queries[100000];

// [in, out)
int in[100000], out[100000], depth[100000];
int timer = 0;
void dfs2(int u, int p, int d = 0) {
    in[u] = timer++;
    depth[u] = d;
    for (int v : adj[u]) {
        if (v != p) dfs2(v, u, d+1);
    }
    out[u] = timer;
}

stack<int> nodes[100000];
vector<int> s;
void dfs(int u, int p) {
    s.pb(u);
    nodes[A[u]].push(u);
    for (auto q : queries[u]) {
        int y = q.f, c = q.s.f;
        if (nodes[c].size() == 0) continue;
        int tgt = nodes[c].top();

        // check if tgt is on the path from u to y
        bool good = false;
        if (!(in[tgt] <= in[y] && out[tgt] > in[y])) good = true;
        else if (depth[tgt]+1 < (int)s.size()) {
            int nextChild = s[depth[tgt]+1];
            if (!(in[nextChild] <= in[y] && out[nextChild] > in[y])) good = true;
        }
        if (tgt == y || tgt == u) good = true;

        if (good) ans[q.s.s] = true;
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    nodes[A[u]].pop();
    s.pop_back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        --A[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; --a; --b; --c;
        queries[a].pb(mp(b, mp(c, i)));
        queries[b].pb(mp(a, mp(c, i)));
    }

    dfs2(0, 0);
    dfs(0, 0);

    for (int i = 0; i < m; i++) {
        cout << ans[i];
    }
    cout << endl;

    return 0;
}
