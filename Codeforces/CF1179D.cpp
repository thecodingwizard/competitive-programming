/*
 * Same sol as editorial
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
 
const int maxn = 500000;
 
ll n; 
vector<int> adj[maxn];
ll sz[maxn];
 
int dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) sz[u] += dfs(v, u);
    }
    return sz[u];
}
 
ll dp[maxn];
ll dfs2(int u, int p) {
    vector<pair<ll, int>> children;
    for (int v : adj[u]) {
        if (v == p) continue;
        children.pb(mp(dfs2(v, u), sz[v]));
    }
    ll best = (sz[u]*sz[u]-1);
 
    for (auto x : children) {
        best = min(best, x.f + (sz[u]-x.s)*(sz[u]-x.s-1));
    }
 
    return dp[u] = best;
}
 
deque<pair<ll, ll>> cht;
 
long double intersect(pair<ll, ll> a, pair<ll, ll> b) {
    return (long double)(b.s-a.s)/(a.f-b.f);
}
 
ll dfs3(int u, int p) {
    ll best = 1e18;
    vector<int> children;
    for (int v : adj[u]) {
        if (v == p) continue;
        children.pb(v);
        best = min(best, dfs3(v, u));
    }
 
    sort(all(children), [](int a, int b) {
        return sz[a] > sz[b];
    });
 
    cht.clear();
    for (int I = 0; I < sz(children); I++) {
        int i = children[I];
        ll toAdd = dp[i] + n*n - 2*n*sz[i] + sz[i]*sz[i] + sz[i]-n;
 
        if (I > 0) {
            while (cht.size() > 1 && intersect(cht[sz(cht)-2], cht.back()) > sz[i]) {
                cht.pop_back();
            }
            best = min(best, cht.back().f*sz[i] + cht.back().s + toAdd);
        }
 
        ll slope = 2*sz[i];
        ll intercept = dp[i]-2*n*sz[i]+sz[i]*sz[i]+sz[i];
        pair<ll, ll> newline = mp(slope, intercept);
 
        while (cht.size() > 1 && intersect(cht[sz(cht)-2], cht.back()) >= intersect(cht.back(), newline)) {
            cht.pop_back();
        }
        if (cht.empty() || !(cht.back().f == slope && cht.back().s <= intercept))
            cht.push_back(newline);
 
        /*
        for (int J = I+1; J < sz(children); J++) {
            int i = children[I], j = children[J];
            best = min(best, dp[i] + dp[j] + n*n - 2*n*sz[i] - 2*n*sz[j] + sz[i]*sz[i] + sz[j]*sz[j] + 2*sz[i]*sz[j] + sz[i]+sz[j]-n);
        }
        */
    }
 
    return best;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n;
    F0R(i, n-1) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
 
    int notLeaf = 0;
    while (notLeaf < n && adj[notLeaf].size() == 1) notLeaf++;
    if (notLeaf == n) {
        cout << 2 << endl;
        return 0;
    }
 
    dfs(notLeaf, notLeaf);
    dfs2(notLeaf, notLeaf);
 
    ll best = dfs3(notLeaf, notLeaf);
    cout << n*(n-1)/2 + n*(n-1)/2 - best/2 << endl;
 
    return 0;
}
