/*
 * This can actually be solved with seg tree.
 *
 * First, do a preorder traversal of the tree to convert it into an array.
 * The range [start[i], end[i]] in the array will be node i and its entire subtree.
 *
 * Then, make a lazy seg tree for this array. Each node will store the smallest
 * value that appears in its range, as well as the number of such smallest values.
 *
 * Initially, set all numbers to be 0. Then, sort the queries. When we encounter
 * a broken fuse, we want to add one to the subtree of the fuse that is broken.
 * When we fix a broken fuse, we subtract one.
 *
 * Whenever we encounter a question, we look for the root node of the seg tree.
 * If the minimum value is > 0, then we output 0. However, if the minimum
 * value is 0, then we output the number of zeroes in the entire array.
 */

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

const int maxn = 100100;

vector<int> adj[maxn];
int dfsCtr = 0;
int start[maxn], End[maxn];
void dfs(int u) {
    start[u] = dfsCtr++;
    for (int v : adj[u]) dfs(v);
    End[u] = dfsCtr-1;
}

struct node {
    int min, ct, lazy;
} st[maxn*4];

void build(int p, int i, int j) {
    st[p].min = 0; st[p].ct = j-i+1; st[p].lazy = 0;
    if (i == j) return;
    build(p << 1, i, (i+j)/2);
    build((p << 1)+1, (i+j)/2+1, j);
}

void down(int p, int i, int j) {
    if (st[p].lazy == 0) return;
    st[p].min += st[p].lazy;
    if (i != j) {
        st[2*p].lazy += st[p].lazy;
        st[2*p+1].lazy += st[p].lazy;
    }
    st[p].lazy = 0;
}

void upd(int p, int i, int j, int L, int R, int v) {
    down(p, i, j);
    if (R < i || L > j) return;
    if (L <= i && j <= R) {
        st[p].lazy += v;
        down(p, i, j);
    } else {
        upd(p << 1, i, (i+j)/2, L, R, v);
        upd((p << 1) + 1, (i+j)/2+1, j, L, R, v);
        st[p].min = min(st[2*p].min, st[2*p+1].min);
        st[p].ct = 0;
        if (st[p].min == st[2*p].min) st[p].ct += st[2*p].ct;
        if (st[p].min == st[2*p+1].min) st[p].ct += st[2*p+1].ct;
    }
}

int main() {
    freopen("curent.in", "r", stdin);
    freopen("curent.out", "w", stdout);
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int p; cin >> p; --p;
        adj[p].push_back(i);
    }
    dfs(0);

    vector<pair<int, pair<int, int>>> stuff;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int day, u, c; cin >> day >> u >> c; --u;
        stuff.push_back({day,{u,c}});
    }
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int x; cin >> x;
        stuff.push_back({x,{1e9,-1}});
    }
    sort(stuff.begin(), stuff.end());

    build(1, 0, n-1);
    for (auto thing : stuff) {
        if (thing.s.s == -1) {
            if (st[1].min == 0) cout << st[1].ct << "\n";
            else cout << 0 << "\n";
        } else {
            upd(1, 0, n-1, start[thing.s.f], End[thing.s.f], thing.s.s == 0 ? 1 : -1);
        }
    }

    return 0;
}
