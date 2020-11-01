#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back

vector<ii> adj[100000];
ii pa[100000];
ii A[100000];

void dfs(int u, int p, int c) {
    pa[u] = mp(p, c);
    for (auto v : adj[u]) {
        if (v.f != p) dfs(v.f, u, v.s);
    }
}

ll memo[100000];
ll dp(int u) {
    if (u == 0) return 0;
    if (memo[u] != -1) return memo[u];

    ll best = 1e18;
    ll dist = pa[u].s;
    int cur = pa[u].f;
    while (cur != -1) {
        best = min(best, dist*A[u].s+A[u].f + dp(cur));
        dist += pa[cur].s;
        cur = pa[cur].f;
    }

    return memo[u] = best;
}

int main() {
    int n; cin >> n;

    for (int i = 0; i < n-1; i++) {
        int a, b, w; cin >> a >> b >> w; --a; --b;
        adj[a].pb(mp(b, w));
        adj[b].pb(mp(a, w));
    }

    dfs(0, -1, 0);

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        A[i+1] = mp(a, b);
    }

    fill(memo, memo+n, -1);

    for (int i = 1; i < n; i++) {
        cout << dp(i) << " ";
    }
    cout << endl;
    
    return 0;
}
