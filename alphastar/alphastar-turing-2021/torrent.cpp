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

int n, a, b; 
vector<int> adj[maxn];
int pa[maxn];

void dfs0(int u, int p) {
    pa[u] = p;
    for (int v : adj[u]) {
        adj[v].erase(find(all(adj[v]), u));
        dfs0(v, u);
    }
}

bool done[maxn];
int cost[maxn];

int dfsCost(int u) {
    if (cost[u] != -1) return cost[u];
    vector<int> children;
    for (int v : adj[u]) {
        if (done[v]) continue;
        children.pb(dfsCost(v));
    }
    sort(all(children));
    int cur = 0;
    for (int v : children) {
        cur = max(cur+1, v+1);
    }
    return cost[u] = cur;
}

void dfs1(int curNode, int steps) {
    done[curNode] = true;
    vector<int> children;
    for (int v : adj[curNode]) {
        if (done[v]) continue;
        children.pb(dfsCost(v));
    }
    sort(all(children));
    //cout << curNode << ": ";
    //for (int v : children) cout << v << " ";
    //cout << endl;
    int cur = 0;
    int bestTime = 0;
    for (int v : children) {
        if (v+1 > cur+1) {
            bestTime = cur+1;
        }
        cur = max(cur+1, v+1);
    }
    if (cur > steps) {
        done[curNode] = false;
    } else if (!done[pa[curNode]]) {
        if (cur < steps) bestTime = steps;
        dfs1(pa[curNode], bestTime - 1);
    }
}

bool can(int steps) {
    F0R(i, n) done[i] = false;
    F0R(i, n) cost[i] = -1;
    dfs1(b, steps);
    dfs1(a, steps);
    return done[a] && done[b];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a >> b; --a; --b;
    F0R(i, n-1) {
        int x, y; cin >> x >> y; --x; --y;
        adj[x].pb(y); adj[y].pb(x);
    }
    dfs0(a, a);

    int lo = 0, hi = n, mid, ans;
    while (lo < hi) {
        mid = (lo+hi)/2;
        if (can(mid)) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    cout << ans << endl;

    return 0;
}
