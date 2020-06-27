/*
 * Same as second solution of editorial
 *
 * Given a query (a, b) where sz[a] < sz[b], we can loop through every single
 * employee in a, and count the number of subordinates in region b in O(log n) with an indexed set.
 *
 * Given a query (a, b) where sz[a] > sz[b], we want to reverse the query to (b, a).
 * Now, for every node x of region b, we want to count the number of nodes of region a that lies
 * on the path from 0 to x. See the code for dfs2. We can do this in O(log n) with O(n) preprocessing.
 *
 * This solution (barely) passes TL (7s)
 */

#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
             rb_tree_tag, tree_order_statistics_node_update>; 

int n, r, q; 
int R[200000];
vector<int> adj[200000];
vector<int> A[200001];
int start[200000], End[200000];
Tree<int> regions[200001];
int id[200000];
vector<pair<int, int>> regions2[200001];
int regions2Ct[200001];

int ctr = 0;
void dfs(int u) {
    start[u] = ctr;
    for (int v : adj[u]) {
        dfs(v);
    }
    End[u] = ctr++;
    regions[R[u]].insert(End[u]);
}

int ctr2 = 0;
void dfs2(int u) {
    id[u] = ctr++;
    regions2Ct[R[u]]++;
    regions2[R[u]].push_back({id[u], regions2Ct[R[u]]});
    for (int v : adj[u]) {
        dfs2(v);
    }
    regions2Ct[R[u]]--;
    regions2[R[u]].push_back({ctr, regions2Ct[R[u]]});
}

int main() {
    cin >> n >> r >> q;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            cin >> R[i];
        } else {
            int p;
            cin >> p >> R[i];
            adj[p-1].push_back(i);
        }
        A[R[i]].push_back(i);
        regions2Ct[R[i]] = 0;
    }

    dfs(0);
    dfs2(0);

    map<pair<int, int>, long long> cache;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        if (cache.count(make_pair(a, b))) {
            cout << cache[make_pair(a, b)] << endl;
            continue;
        }
        bool swapped = false;
        if (A[a].size() > A[b].size()) {
            swap(a, b);
            swapped = true;
        }
        long long ans = 0;
        for (int n : A[a]) {
            if (!swapped) {
                int x = start[n], y = End[n];
                ans += regions[b].order_of_key(y) - regions[b].order_of_key(x);
            } else {
                auto it = lower_bound(regions2[b].begin(), regions2[b].end(), make_pair(id[n], 1000000));
                if (it == regions2[b].begin()) continue;
                ans += (--it)->second;
            }
        }
        cout << ans << endl;
        if (swapped) swap(a, b);
        cache[make_pair(a, b)] = ans;
    }

    return 0;
}
