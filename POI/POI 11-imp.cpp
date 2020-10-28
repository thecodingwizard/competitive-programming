/*
 * If there are two nodes that aren't connected by an edge, delete both nodes. Repeat until no more such nodes exist.
 *
 * There are 1/3 nodes that didn't attend the party, so those nodes will be deleted along with at most
 * 1/3 nodes that did attend the party. This will leave at least 1/3 nodes left where every node is connected
 * to every other node.
 *
 *
 *
 * Also, you can do a sketchy greedy solution where you take nodes w/ over 2/3*n connections if you can.
 * Then, if you don't end up with enough nodes, delete all the nodes you took and rerun the algorithm again.
 * This also gets AC but I cannot prove whether this works or not (it probably has some edge case).
 */

#include <bits/stdc++.h>

using namespace std;

#define pb push_back

bool adj[3000][3000];
bool dead[3000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a][b] = 1; adj[b][a] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (!dead[i] && !dead[j] && !adj[i][j]) {
                dead[i] = dead[j] = 1;
            }
        }
    }

    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (!dead[i]) {
            cout << i+1 << " ";
            ct++;
            if (ct == n/3) break;
        }
    }
    cout << endl;

    return 0;
}
