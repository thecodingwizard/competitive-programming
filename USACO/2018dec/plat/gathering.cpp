/*
 * Same solution as editorial
 *
 * Greedily find a node that can be the last node
 * Then, run a BFS from that node. You can't enter
 * any node that must leave before another node.
 * The nodes that you BFS to are all able to be
 * the last node.
 */

#include <bits/stdc++.h>

using namespace std;

int n, m; 
vector<int> adj[100000];
vector<int> deps[100000];
int deg[100000];
bool vis[100000];
bool can[100000];
bool marked[100000];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    freopen("gathering.in", "r", stdin);
    freopen("gathering.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++; deg[b]++;
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        deps[a].push_back(b);
        deg[b]++;
        marked[a] = true;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
            vis[i] = true;
            q.push(i);
        }
    }
    int last = -1;
    int ct = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        last = u;
        ct++;
        for (int v : deps[u]) {
            deg[v]--;
            if (deg[v] == 1 && !vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 1 && !vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    if (ct == n) {
        queue<int> q;
        q.push(last);
        can[last] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!marked[v] && !can[v]) {
                    can[v] = true;
                    q.push(v);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "01"[can[i]] << endl;
    }

    return 0;
}
