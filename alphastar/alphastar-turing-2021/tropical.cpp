#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define pb push_back
#define F0R(i, n) for (int i = 0; i < n; i++)
using ll = long long;

int n, m, p; 
vector<ii> adj[150000];
ii nxt[150000][2];

bool vis[150000][2];

int memo[150000][2][2];
bool dpvis[150000][2][2];
int dp(int u, int block, int tgt) {
    if (memo[u][block][tgt] != -1) return memo[u][block][tgt];
    if (u == p && block == tgt) return 0;
    if (dpvis[u][block][tgt]) return memo[u][block][tgt] = -2;
    dpvis[u][block][tgt] = 1;

    int res = dp(nxt[u][block].f, nxt[u][block].s, tgt);
    if (res == -2) return memo[u][block][tgt] = -2;
    return memo[u][block][tgt] = res + 1;
}
int qryAns[2000];

int main() {
    cin >> n >> m >> p;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].pb(mp(b, i));
        adj[b].pb(mp(a, i));
    }
    for (int i = 0; i < n; i++) {
        sort(all(adj[i]), [](ii x, ii y) { return x.s < y.s; });
    }
    for (int i = 0; i < n; i++) {
        nxt[i][0] = mp(adj[i][0].f, adj[adj[i][0].f][0].f == i ? 1 : 0);
        if (adj[i].size() == 1) adj[i].pb(adj[i][0]);
        nxt[i][1] = mp(adj[i][1].f, adj[adj[i][1].f][0].f == i ? 1 : 0);
    }

    ii cur = mp(p, 0);
    int p0len = 0;
    while (!vis[cur.f][cur.s]) {
        vis[cur.f][cur.s] = true;
        p0len++;
        cur = nxt[cur.f][cur.s];
    }
    if (cur != mp(p, 0)) p0len = -1;

    for (int i = 0; i < n; i++) for (int j = 0; j < 2; j++) vis[i][j] = 0;
    cur = mp(p, 1);
    int p1len = 0;
    while (!vis[cur.f][cur.s]) {
        vis[cur.f][cur.s] = true;
        p1len++;
        cur = nxt[cur.f][cur.s];
    }
    if (cur != mp(p, 1)) p1len = -1;

    int q; cin >> q;
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        queries.pb(x);
    }

    F0R(i, n) F0R(j, 2) F0R(k, 2) { memo[i][j][k] = -1; dpvis[i][j][k] = 0; }
    for (int i = 0; i < n; i++) {
        int distToP0 = dp(i, 0, 0);
        int distToP1 = dp(i, 0, 1);
        for (int j = 0; j < q; j++) {
            if (distToP0 != -2 && distToP0 <= queries[j]) {
                if (p0len != -1 && (queries[j]-distToP0)%p0len == 0) qryAns[j]++;
                else if (queries[j] == distToP0) qryAns[j]++;
            }
            if (distToP1 != -2 && distToP1 <= queries[j]) {
                if (p1len != -1 && (queries[j]-distToP1)%p1len == 0) qryAns[j]++;
                else if (queries[j] == distToP1) qryAns[j]++;
            }
        }
    }

    for (int i = 0; i < q; i++) cout << qryAns[i] << " \n"[i == q-1];

    return 0;
}
