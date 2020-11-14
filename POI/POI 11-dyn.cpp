/*
 * Binary Search + greedy:
 *
 * Let's say we want to check if we can explode everything in t time. We aim to minimize the number of dynamites we need to put.
 * Root the tree arbitrarily.
 *
 * Note that if we're at a node where the farthest node in our subtree that needs to be exploded is exactly t steps away from this node, it is
 * always optimal for us to place a dynamite down on this node.
 *
 * Also, if we place a dynamite down at this node, then it can also explode upwards to the parent.
 *
 * So, for each node, we need to compute three things:
 * - need[i] = dynamites placed within i's subtree
 * - farthestDyn[i] = farthest node that still needs to be exploded in the subtree of i
 * - extraExplosion[i] = how much extra explosion comes from the subtree of i to the parent of i
 *
 * We compute need[i] = sum of need[j] where j is a child of i, plus one if farthestDyn[i] == t.
 * We compute farthestDyn[i] = max((0 if i needs to be exploded, -inf otherwise), farthestDyn[j]+1 where j is a child of i)
 * We compute extraExplosion[i] = t if farthestDyn[i] == t, else max(extraExplosion[j]-1) where j is a child of i. If no children, extraExplosion[i] = -inf
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
