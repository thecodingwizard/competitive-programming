/*
 * Let's say the longest distance between any two nodes is d, then
 * our answer is log2(d-1). We can't find d bc that would take too long,
 * but because we only need to give an approximate answer, we can just
 * find something close-ish to d. We bfs from node 0 to all the other nodes
 * and find max d for node 0; as it turns out, log2(d-1)+1 is acceptable answer
 * due to the "approximate" condition.
 *
 * See: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/amici2.cpp
 */

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> adj[21000];
int dist[21000];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    freopen("amici2.in", "r", stdin);
    freopen("amici2.out", "w", stdout);

    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            vector<int>().swap(adj[i]);
            dist[i] = -1;
        }

        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dist[0] = 0;
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        int longestDist = 0;
        for (int i = 0; i < n; i++) {
            longestDist = max(longestDist, dist[i]-1);
        }

        int ans = 0, num = 1;
        while (num < longestDist) {
            ans++; num *= 2;
        }
        cout << ans+1 << "\n";
    }

    return 0;
}
