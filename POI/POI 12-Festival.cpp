/*
 * Same solution as editorial
 *
 * - Denote time(u) = the time we assign to node u
 * - an edge between two nodes (u, v) with weight w means that time(u) + w <= time(v)
 * - (A, B) can be represented by two edges: (u, v, 1) and (v, u, -1)
 * - (C, D) can be represented by a single edge: (u, v, 0)
 * - If we have two edges between (u, v), take the one with the higher edge weight because it is more restrictive
 * - Consider a path from v_1 ... v_m that traverses the edges e_i = (v_i, v_i+1) for i = 1, 2, ... m-1
 * - We have: time(v_1) <= time(v_2) - w(e_1) <= time(v_3) - w(e_1) - w(e_2) <= ... <= time(v_m) - w(e_1) - ... - w(e_m-1)
 * - So, time(v_1) + w(path from e_1 to e_m) <= time(v_m)
 * - Now consider a cycle where the sum of the edges is positive. then, we will have time(v) + w(cycle) <= time(v), which isn't possible if w(cycle) > 0.
 *   - So, if there exists a cycle with positive weight, we output no.
 * - Now let's try to deal with SCCs. Consider two nodes u, v in an SCC. We have:
 *   - time(u) + longest_path(u, v) <= time(v)
 *   - time(v) + longest_path(v, u) <= time(u)
 *   - Combined: longest_path(u, v) <= time(v) - time(u) <= -longest_path(v, u)
 * - We can compute longest_path between every pair of nodes with modified Floyd Warshall
 * - One can then prove (see editorial) that it's possible to assign x unique values to the nodes in the SCC where x = max(longest_path(u, v), -longest_path(v, u)) + 1, for any (u, v) in the same SCC
 * - So, we run an SCC algorithm, and for each SCC determine the maximum number of times we can have for that SCC.
 * - Finally, we can sum up the contributions from each SCC, because the remaining edges form a DAG where all the edge weights are 0, so we can assign times in a way that they're all unique across different SCC's.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define INF 1000000000

// an edge (u, v) with weight w means that time(u) + w <= time(v)

int n, m1, m2; 
vector<int> adj[600];
vector<int> radj[600];

bool vis[600];
int scc[600];
vector<int> L;

void visit(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) visit(v);
    }
    L.pb(u);
}

void assign(int u, int v) {
    scc[u] = v;
    for (int x : radj[u]) {
        if (scc[x] == -1) assign(x, v);
    }
}

void findSCCs() {
    for (int i = 0; i < n; i++) {
        scc[i] = -1;
        if (!vis[i]) {
            visit(i);
        }
    }
    reverse(L.begin(), L.end());
    for (int u : L) {
        if (scc[u] == -1) assign(u, u);
    }
}

int dist[600][600];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m1 >> m2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j ? 0 : -INF);
        }
    }

    for (int i = 0; i < m1; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
        radj[a].pb(b); radj[b].pb(a);
        dist[a][b] = 1; dist[b][a] = max(dist[b][a], -1);
    }

    for (int i = 0; i < m2; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        radj[b].pb(a);
        dist[a][b] = max(dist[a][b], 0);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = max(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i][i] != 0) {
            cout << "NIE" << endl;
            return 0;
        }
    }

    findSCCs();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (scc[i] == i) {
            int best = 0;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (scc[j] == i && scc[k] == i) {
                        best = max(best, max(dist[j][k], -dist[k][j]) + 1);
                    }
                }
            }
            ans += best;
        }
    }
    cout << ans << endl;

    return 0;
}
