/*
 * In this problem, we essentially have to union every pair of nodes that don't have an edge between them, and then
 * count the number of final components.
 *
 * Note that since there aren't that many edges, there must exist some node that is going to get unioned with a lot of other nodes.
 * In fact, if x is the minimum number of edges of an arbitrary node, then 100000*x = 2000000 ==> x is at most 20!
 *
 * So, we can find the node with the fewest outgoing edges, and then union this node with every node it doesn't have an edge with.
 * We'll be left with at most 20 nodes that haven't been unioned.
 *
 * Finally, for the remaining 20 nodes, we can brute force check every single other node and union them as necessary.
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> bad[100000];

int sz[100000], pa[100000];

int findSet(int x) {
    return pa[x] == x ? x : pa[x] = findSet(pa[x]);
}

void unionSet(int a, int b) {
    a = findSet(a), b = findSet(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        bad[a].push_back(b); bad[b].push_back(a);
    }

    int best = -1;
    for (int i = 0; i < n; i++) {
        sz[i] = 1;
        pa[i] = i;
        bad[i].push_back(n);
        sort(bad[i].begin(), bad[i].end());
        if (best == -1 || bad[i].size() < bad[best].size()) best = i;
    }

    vector<int> todo;
    for (int j = 0; j < n; j++) {
        if (*lower_bound(bad[best].begin(), bad[best].end(), j) != j) {
            unionSet(best, j);
        } else {
            todo.push_back(j);
        }
    }

    for (int x : todo) {
        for (int y = 0; y < n; y++) {
            if (*lower_bound(bad[x].begin(), bad[x].end(), y) != y) {
                unionSet(x, y);
            }
        }
    }

    vector<int> sizes;
    for (int i = 0; i < n; i++) {
        if (findSet(i) == i) {
            sizes.push_back(sz[i]);
        }
    }
    sort(sizes.begin(), sizes.end());

    cout << sizes.size() << endl;
    for (int v : sizes) cout << v << " ";
    cout << endl;

    return 0;
}
