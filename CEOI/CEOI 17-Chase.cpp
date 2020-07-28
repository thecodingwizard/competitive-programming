/*
 * Same solution as editorial.
 *
 * Root tree at node 0.
 *
 * Define dpDown[i][j] = max difference assuming Jerry is at node i and has j breadcrumbs to drop,
 * and Jerry can only move down the subtree, and Jerry cannot drop a breadcrumb on node i.
 *
 * Define dpUp[i][j] = max difference assuming Jerry can start anywhere within the subtree of node i,
 * Jerry must end at node i, and Jerry can drop a breadcrumb on node i.
 *
 * Then we just have to loop through all the nodes and do dpDown + dpUp. However, dpDown and dpUp
 * must be from different subtrees. To handle this, we can just store the best transition and
 * the second best transition for both dpDown and dpUp. (Note that memory limit is a bit tight
 * so you might have to optimize by only storing second best transition for the current active node)
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define f first
#define s second
#define ii pair<int, int>
#define pll pair<ll, int>
#define INF 1e15

int n, v; 
vector<int> adj[100000];
int A[100000];
ll sumAdj[100000];
int pa[100000];

vector<int> S;
void dfs(int u) {
    S.push_back(u);
    for (int v : adj[u]) {
        pa[v] = u;
        adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
        dfs(v);
    }
}

bool vis1[100000][101];
bool vis2[100000][101];
pll memo1[100000][101];
pll memo2[100000][101];
pll second1, second2;
pll dp1(int u, int j, bool storeSecond = false) { // go down, excluding node u
    if (j < 0) return make_pair(-INF, -1);
    if (vis1[u][j] && !storeSecond) return memo1[u][j];
    vis1[u][j] = true;
    pll b1 = make_pair(0, -1), b2 = make_pair(0, -1);

    for (int v : adj[u]) {
        pll opt = make_pair(max(dp1(v, j).f, dp1(v, j-1).f + sumAdj[v]), v);
        if (opt > b1) {
            b2 = b1;
            b1 = opt;
        } else if (opt > b2) {
            b2 = opt;
        }
    }

    if (storeSecond) second1 = b2;
    return memo1[u][j] = b1;
}
pll dp2(int u, int j, bool storeSecond = false) { // go up, including node u
    if (j < 0) return make_pair(-INF, -1);
    if (vis2[u][j] && !storeSecond) return memo2[u][j];
    vis2[u][j] = true;
    pll b1 = make_pair(0, -1), b2 = make_pair(0, -1);
    if (j > 0) {
        b1 = make_pair(sumAdj[u] + A[pa[u]], -2);
    }

    for (int v : adj[u]) {
        pll opt = make_pair(max(dp2(v, j).f, dp2(v, j-1).f + sumAdj[u] + A[pa[u]] - A[v]), v);
        if (opt > b1) {
            b2 = b1;
            b1 = opt;
        } else if (opt > b2) {
            b2 = opt;
        }
    }
    if (storeSecond) second2 = b2;
    return memo2[u][j] = b1;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    cin >> n >> v;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        for (int j = 0; j <= 100; j++) vis1[i][j] = vis2[i][j] = false;
    }

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    pa[0] = -1;

    for (int i = 0; i < n; i++) {
        sumAdj[i] = 0;
        for (int v : adj[i]) {
            sumAdj[i] += A[v];
        }
    }

    reverse(S.begin(), S.end());

    ll best = 0;
    for (int i : S) {
        for (int j = 0; j <= v; j++) {
            pll a = dp1(i, j, true), b = dp2(i, v-j, true);
            pair<pair<pll, pll>, pair<pll, pll>> val = make_pair(make_pair(a, second1), make_pair(b, second2));
            if (val.f.f.s == val.s.f.s) {
                best = max(best, max(val.f.f.f + val.s.s.f, val.f.s.f + val.s.f.f));
            } else {
                best = max(best, val.f.f.f + val.s.f.f);
            }
        }
    }
    cout << best << endl;

    return 0;
}
