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

#define maxn 300000

int n, m; 
vector<int> adj[maxn];
bool lit[maxn];

int need[maxn]; // # of dynamites needed
int farthestDyn[maxn]; // farthest dynamite in subtree of i
int extraExplosion[maxn]; // extra explosion coming out of subtree of i

void dfs(int u, int p, int t) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, t);
        }
    }
    int extra = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        extra = max(extra, extraExplosion[v]);
    }
    --extra;
    int farDyn = lit[u] ? 0 : -inf;
    for (int v : adj[u]) {
        if (v == p) continue;
        farDyn = max(farDyn, farthestDyn[v] + 1);
    }
    if (farDyn <= extra) {
        farDyn = -inf;
    }
    assert(farDyn <= t);
    int totNeed = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        totNeed += need[v];
    }
    if (farDyn == t) {
        farDyn = -inf;
        extra = t;
        totNeed++;
    }

    need[u] = totNeed;
    farthestDyn[u] = farDyn;
    extraExplosion[u] = extra;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    F0R(i, n) cin >> lit[i];
    F0R(i, n-1) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    int lo = 0, hi = n, mid, ans = -1;

    while (lo < hi) {
        mid = (lo+hi)/2;
        dfs(0, 0, mid);
        if (farthestDyn[0] >= 0) need[0]++;
        if (need[0] <= m) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid+1;
        }
    }

    cout << ans << endl;

    return 0;
}
