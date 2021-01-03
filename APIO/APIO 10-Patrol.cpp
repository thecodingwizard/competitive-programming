/*
 * Adding one edge basically means you make one big cycle, and every edge
 * on the cycle only has to be traversed once instead of twice.
 *
 * Any solution for k = 2 with two disjoint cycles can be converted into
 * another equivalent solution with two intersecting cycles.
 *
 * So, we can just greedily make one cycle as big as possible, and then if k = 2,
 * we can do another dfs to find the next optimal cycle, taking into consideration
 * edges that were used as part of the other cycle (these edge weights should
 * change from +1, saving one traversal unit, to -1, costing one additional traversal unit).
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

#define maxn 1000000

int n, k; 
set<ii> adj[maxn];

ii dfs1(int u, int p) {
    ii mx = { 0, u };
    for (ii v : adj[u]) {
        if (v.f != p) {
            ii res = dfs1(v.f, u);
            if (mx.f < res.f+1) {
                mx.f = res.f+1;
                mx.s = res.s;
            }
        }
    }
    return mx;
}

int pa[maxn];
ii dfs2(int u, int p) {
    pa[u] = p;
    ii mx = mp(0, u);
    for (auto v : adj[u]) {
        if (v.f != p) {
            ii res = dfs2(v.f, u);
            if (mx.f < res.f+1) {
                mx.f = res.f+1;
                mx.s = res.s;
            }
        }
    }
    return mx;
}

int best = 0;
int dfs3(int u, int p) {
    vector<int> children;
    for (ii v : adj[u]) {
        if (v.f == p) continue;
        children.pb(dfs3(v.f, u) + v.s);
    }
    children.pb(0);
    children.pb(0);
    sort(all(children));
    reverse(all(children));

    best = max(best, children[0] + children[1]);

    return children[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    F0R(i, n-1) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].insert(mp(b, 1)); adj[b].insert(mp(a, 1));
    }
    ii res = dfs1(0, -1);
    ii res2 = dfs2(res.s, -1);
    int save = res2.f;

    if (k == 2) {
        int u = res2.s;
        while (pa[u] != -1) {
            adj[pa[u]].erase(mp(u, 1));
            adj[pa[u]].insert(mp(u, -1));
            u = pa[u];
        }
        dfs3(res.s, -1);
        save += best;
    }

    cout << 2*(n-1)-save+k << endl;

    return 0;
}
