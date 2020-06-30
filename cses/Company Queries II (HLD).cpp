#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define vi vector<int>

vi adj[200000];
int parent[200000], heavy[200000], depth[200000], root[200000], treePos[200000];

int dfs(int u) {
    int sz = 1, mxSubtree = 0;
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u]+1;
        int subtree = dfs(v);
        if (subtree > mxSubtree) heavy[u] = v, mxSubtree = subtree;
        sz += subtree;
    }
    return sz;
}

int queryPath(int u, int v) {
    int ans = -1;
    for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]]) swap(u, v);
        ans = root[v];
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (ans == -1 || depth[ans] > depth[u]) {
        ans = u;
    }
    return ans+1;
}

int main() {
    int n, q; cin >> n >> q;

    for (int i = 0; i < n-1; i++) {
        int x; cin >> x;
        adj[x-1].push_back(i+1);
    }

    for (int i = 0; i < n; i++) {
        heavy[i] = -1;
    }
    parent[0] = -1;
    depth[0] = 0;
    dfs(0);
    for (int i = 0, curPos = 0; i < n; i++) {
        if (parent[i] == -1 || heavy[parent[i]] != i) {
            for (int j = i; j != -1; j = heavy[j]) {
                root[j] = i;
                treePos[j] = curPos++;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; --a; --b;
        cout << queryPath(a, b) << "\n";
    }

    return 0;
}
