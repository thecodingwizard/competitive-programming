/*
 * Also see: https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/COI/COCI%2020-putovanje.cpp
 *
 * If we're going from A -> B, we can split this up into two paths: A -> lca(A, B) and lca(A, B) -> B.
 *
 * We can add one to node A and node B and subtract two from node lca(A, B). Now,
 * the number of times an edge is traversed is simply the sum of all the nodes in
 * its subtree.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

int n; 
vector<pair<int, ii>> adj[200000];
int pa[200000][20];
int depth[200000];
int in[200000], out[200000], ctr = 0;

void dfs(int u, int p, int d) {
    in[u] = ctr++;
    pa[u][0] = p;
    depth[u] = d;
    for (auto v : adj[u]) {
        if (v.f != p) dfs(v.f, u, d+1);
    }
    out[u] = ctr-1;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) {
        if (depth[pa[a][i]] >= depth[b]) a = pa[a][i];
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i], b = pa[b][i];
        }
    }
    return pa[a][0];
}

int ft[200001];
void upd(int k, int v) {
    k++;
    while (k <= 200000) {
        ft[k] += v;
        k += k&-k;
    }
}
int qry(int k) {
    k++;
    int ans = 0;
    while(k) {
        ans += ft[k];
        k -= k&-k;
    }
    return ans;
}

ll ans = 0;
void dfs2(int u, int p) {
    for (auto v : adj[u]) {
        if (v.f == p) continue;
        assert(depth[v.f] = depth[u]+1);
        ll numTraversals = qry(out[v.f]) - qry(in[v.f]-1);
        //cout << u << "->" << v.f << ": " << min(numTraversals*v.s.f, (ll)v.s.s) << endl;
        ans += min(numTraversals*v.s.f, (ll)v.s.s);
        dfs2(v.f, u);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;

    for (int i = 0; i < n-1; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d; --a; --b;
        adj[a].push_back(mp(b, mp(c, d)));
        adj[b].push_back(mp(a, mp(c, d)));
    }

    dfs(0, 0, 0);

    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n; i++) {
            pa[i][j] = pa[pa[i][j-1]][j-1];
        }
    }

    for (int i = 0; i < n-1; i++) {
        int x = lca(i, i+1);
        assert(depth[i] >= depth[x]);
        assert(depth[i+1] >= depth[x]);
        upd(in[i], 1);
        upd(in[i+1], 1);
        upd(in[x], -2);
    }

    dfs2(0, 0);
    cout << ans << endl;

    return 0;
}
