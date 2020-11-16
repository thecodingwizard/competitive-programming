/*
 * Same as editorial
 *
 * If the paths on the tree connecting two non-standard trails intersect, then we can form
 * a good route. So we just need to count the number of pairs of intersecting trails.
 *
 * We first split each trail into two paths by its LCA, so each path goes from a node
 * to an ancestor.
 *
 * Let's count the number of intersecting paths. Note that we will overcount -- we will
 * need to subtract one for each pair of trails that have the same LCA and go through
 * the same children. We can do this fairly easily.
 *
 * To count the number of intersecting paths, we can use a solution motivated by
 * counting the number of intersecting 1D line segments (see editorial).
 *
 * First, denote the "start" of each path as the node right below the LCA,
 * since we want paths that intersect at an edge, not just a node. Denote the "end"
 * of each path normally (the final node that we visit).
 *
 * Keep track of the number of paths that we have encountered so far.
 * - When we reach a node u, add all the paths that start at node u to the number of paths we encountered so far.
 * - For each path that starts at node u, subtract the number of paths we have encountered so far.
 * - For each path that ends at node u, add the number of paths we have encountered so far.
 * - For every pair of paths that start at node u, add one.
 *
 * See implementation below for more details
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 200000
int n, m; 
vector<int> adj[maxn];
// numStart[i] = number of paths that start at parent of i and go to i
int numStart[maxn];
// numEnding[i] = # of paths ending at i
int numEnding[maxn];
ll ans = 0;

int depth[maxn];
int pa[maxn][20];

void dfsLCA(int u, int p, int d) {
    pa[u][0] = p;
    depth[u] = d;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsLCA(v, u, d+1);
    }
}

// returns <lca, <lcaChildLeft, lcaChildRight>>
pair<int, ii> lca(int a, int b) {
    assert(a != b);
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 19; ~i; i--) {
        if (depth[pa[a][i]] > depth[b]) {
            a = pa[a][i];
        }
    }
    if (pa[a][0] == b) {
        return mp(pa[a][0], mp(a, a));
    }
    if (depth[a] != depth[b]) a = pa[a][0];
    assert(depth[a] == depth[b]);
    
    for (int i = 19; ~i; i--) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i], b = pa[b][i];
        }
    }

    return mp(pa[a][0], mp(a, b));
}

void dfs(int u, int p, int pathsSoFar) {
    pathsSoFar += numStart[u];
    ans += (ll)numEnding[u]*pathsSoFar;
    ans += (ll)numStart[u]*(numStart[u]-1)/2;
    ans -= (ll)numStart[u]*pathsSoFar;

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, pathsSoFar);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    cin >> n >> m;
    vector<ii> specialTrails;
    F0R(i, m) {
        int a, b; cin >> a >> b; --a; --b;
        if (i < n-1) {
            adj[a].pb(b);
            adj[b].pb(a);
        } else {
            specialTrails.push_back(mp(a, b));
        }
    }
    dfsLCA(0, 0, 0);
    FOR(i, 1, 20) {
        F0R(j, n) {
            pa[j][i] = pa[pa[j][i-1]][i-1];
        }
    }

    map<ii, int> overcount[n];
    for (auto x : specialTrails) {
        pair<int, ii> l = lca(x.f, x.s);
        if (l.s.f == l.s.s) {
            assert(x.f == l.f || x.s == l.f);
            numStart[l.s.f]++;
            if (x.f == l.f) numEnding[x.s]++;
            else numEnding[x.f]++;
        } else {
            overcount[l.f][mp(min(l.s.f, l.s.s), max(l.s.f, l.s.s))]++;
            //cout << l.s.f << " and " << l.s.s << " to " << x.f << " " << x.s << endl;
            numStart[l.s.f]++;
            numStart[l.s.s]++;
            numEnding[x.f]++;
            numEnding[x.s]++;
        }
    }
    dfs(0, 0, 0);
    F0R(i, n) {
        for (auto x : overcount[i]) {
            ans -= (ll)x.s*(x.s-1)/2;
        }
    }

    cout << ans << endl;

    return 0;
}
