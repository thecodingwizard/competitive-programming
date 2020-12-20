/*
 * http://blog.brucemerry.org.za/2012/09/ioi-2012-day-2-analysis.html
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define mod 1000000000
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define F0R(i, n) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()

int n;
vector<ii> A;

set<int> adj[100000];

int pa[100000], sz[100000];
int get(int x) { return pa[x] == x ? x : pa[x] = get(pa[x]); }
void unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
}

ll ans = 0;
ll subtreeSum[100000];
int dfs1(int u, int p) {
    subtreeSum[u] = sz[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        subtreeSum[u] += dfs1(v, u);
    }
    return subtreeSum[u];
}
void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            ll x = subtreeSum[v], y = n - subtreeSum[v];
            ans += x*y;
            ans %= mod;
            dfs2(v, u);
        }
    }
}
void solve() {
    map<ii, int> points;
    F0R(i, n) {
        points[A[i]] = i;
        adj[i].clear();
        pa[i] = i; sz[i] = 1;
        subtreeSum[i] = 0;
    }

    F0R(i, n) {
        if (points.count(mp(A[i].f, A[i].s-1))) unite(i, points[mp(A[i].f, A[i].s-1)]);
        if (points.count(mp(A[i].f, A[i].s+1))) unite(i, points[mp(A[i].f, A[i].s+1)]);
    }
    F0R(i, n) {
        if (points.count(mp(A[i].f-1, A[i].s))) adj[get(i)].insert(get(points[mp(A[i].f-1, A[i].s)]));
        if (points.count(mp(A[i].f+1, A[i].s))) adj[get(i)].insert(get(points[mp(A[i].f+1, A[i].s)]));
    }

    dfs1(get(0), -1);
    dfs2(get(0), -1);
}

int DistanceSum(int N, int *X, int *Y) {
    n = N;
    F0R(i, n) {
        A.pb(mp(X[i], Y[i]));
    }
    solve();
    A.clear();
    F0R(i, n) {
        A.pb(mp(Y[i], X[i]));
    }
    solve();
    return ans;
}
