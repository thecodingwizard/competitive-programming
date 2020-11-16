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

#define maxn 10000
int n, k, x;
vector<ii> adj[maxn];
vector<int> sz[maxn];

int dfs(int u, int p) {
    sz[u].assign(adj[u].size()+1, 0);
    sz[u][0] = 0;
    int idx = 0;
    for (ii v : adj[u]) {
        if (v.f != p) sz[u][idx] += dfs(v.f, u)+1;
        idx++;
    }
    for (int i = idx-2; ~i; i--) {
        sz[u][i] += sz[u][i+1];
    }
    return sz[u][0];
}

vector<vector<int>> memo[maxn][2];
int dp(int u, int p, int k, int childIdx, int comeBack) {
    if (k == 0) return 0;
    if (k > sz[u][childIdx]) return inf;
    if (childIdx >= (int)adj[u].size()) return inf;
    if (adj[u][childIdx].f == p) return dp(u, p, k, childIdx+1, comeBack);

    if (memo[u][comeBack].size() == 0) {
        F0R(i, adj[u].size()) {
            memo[u][comeBack].emplace_back(sz[u][i]+1, -1);
        }
    }

    if (memo[u][comeBack][childIdx][k] != -1) return memo[u][comeBack][childIdx][k];

    int best = dp(u, p, k, childIdx+1, comeBack);
    for (int amt = max(0, k-1-sz[u][childIdx+1]); amt <= min(sz[adj[u][childIdx].f][0], k-1); amt++) {
        int needToComeBack = 1; // (comeBack == 0 && amt == k-1 ? 0 : 1);
        int extra = adj[u][childIdx].s*(1+needToComeBack) + dp(u, p, k-amt-1, childIdx+1, comeBack);
        best = min(best, dp(adj[u][childIdx].f, u, amt, 0, needToComeBack) + extra);
        if (comeBack == 0) {
            best = min(best, dp(adj[u][childIdx].f, u, amt, 0, 0) + adj[u][childIdx].s + dp(u, p, k-amt-1, childIdx+1, 1));
        }
    }

    //cout << u << " " << p << " " << k << " " << childIdx << " " << comeBack << " " << best << endl;
    return memo[u][comeBack][childIdx][k] = best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> x; --x;
    F0R(i, n-1) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].pb(mp(b, w));
        adj[b].pb(mp(a, w));
    }
    dfs(x, x);
    cout << dp(x, x, k-1, 0, 0) << endl;

    return 0;
}
