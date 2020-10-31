/*
 * Solved w/ euler tour + compressed BIT
 *
 * Basically for every color we want to be able to find the number of instances
 * of that color from the root node to a given node i
 *
 * We can do this with euler tour; add 1 to the current timer index when we enter
 * a node's subtree and then subtract 1 from the current timer index when we leave
 * the node's subtree.
 *
 * See implementation
 */

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 

int n, m; 
int A[100000];
vector<int> adj[100000];

Tree<int> add[100000], sub[100000];

int pa[18][100000], depth[100000];

// [in, out)
int in[100000];
int timer = 0;
void dfs2(int u, int p, int d = 0) {
    pa[0][u] = p;
    depth[u] = d;
    in[u] = timer;
    add[A[u]].insert(timer);
    timer++;
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u, d+1);
        }
    }
    sub[A[u]].insert(timer);
    timer++;
}

int qry(int k, int x) {
    x = in[x]+1;
    int v = add[k].order_of_key(x) - sub[k].order_of_key(x);
    assert(v >= 0);
    return v;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) {
        if (depth[pa[i][a]] >= depth[b]) a = pa[i][a];
    }
    if (a == b) return a;
    for (int i = 17; ~i; i--) {
        if (pa[i][a] != pa[i][b]) {
            a = pa[i][a];
            b = pa[i][b];
        }
    }
    return pa[0][a];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        --A[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs2(0, 0);
    for (int i = 1; i < 18; i++) {
        for (int j = 0; j < n; j++) {
            pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; --a; --b; --c;
        if (qry(c, a) + qry(c, b) - 2*qry(c, lca(a, b)) > 0 || A[lca(a, b)] == c) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << endl;

    return 0;
}
