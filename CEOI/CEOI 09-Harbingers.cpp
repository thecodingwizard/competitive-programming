/*
 * CHT on a tree
 * dfs from the root node. when you enter a node, you delete the last X lines; keep track of X.
 * Then, when you leave the node, "undo" your deletions of the last X lines.
 *
 * Binary search to find X; use an array + a size pointer to efficiently delete / add the last X lines in O(1)
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

#define maxn 100000

int n; 
vector<ii> adj[maxn];
ll dp[maxn];
ll d[maxn];
ii A[maxn];

void dfsd(int u, int p, ll di = 0) {
    d[u] = di;
    for (auto v : adj[u]) {
        if (v.f != p) dfsd(v.f, u, di+v.s);
    }
}

struct Func {
    ll m, b;
    long double intersectX(Func other) {
        return (long double)(other.b-b)/(m-other.m);
    }
    ll eval(ll x) {
        return m*x+b;
    }
};

Func dq[100001];
int dqSz = 0;
vector<int> nums;
auto cmp = [](int idx, int x) {
    return dq[idx].intersectX(dq[idx+1]) < x;
};
void dfs(int u, int p) {
    if (u == 0) {
        dp[u] = 0;
    } else {
        int idx = *lower_bound(nums.begin(), nums.begin() + dqSz-1, A[u].s, cmp);
        ll v = dq[idx].eval(A[u].s);
        dp[u] = A[u].f + (ll)A[u].s*d[u] + v;
    }

    int oldSz = dqSz;
    Func f = {-d[u], dp[u]};
    int lo = 0, hi = dqSz-1, mid, ans = dqSz;
    while (lo < hi) {
        mid = (lo+hi)/2;
        if (dq[mid].intersectX(dq[mid+1]) >= dq[mid].intersectX(f)) {
            hi = mid;
            ans = mid+1;
        } else {
            lo = mid+1;
        }
    }
    dqSz = ans;
    Func backup = dq[dqSz];
    dq[dqSz++] = f;

    for (auto v : adj[u]) {
        if (v.f != p) dfs(v.f, u);
    }

    dq[dqSz-1] = backup;
    dqSz = oldSz;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    F0R(i, n-1) {
        int u, v, d; cin >> u >> v >> d; --u; --v;
        adj[u].pb(mp(v, d));
        adj[v].pb(mp(u, d));
    }
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        A[i+1] = mp(a, b);
    }
    dfsd(0, 0);

    nums = vector<int>(n);
    for (int i = 0; i < n; i++) nums[i] = i;
    dfs(0, 0);

    FOR(i, 1, n) {
        cout << dp[i] << " \n"[i == n-1];
    }

    return 0;
}
