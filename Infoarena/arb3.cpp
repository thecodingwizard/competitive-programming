/*
 * Note that the height of the tree is at most 20.
 *
 * Define solve(i, j) = the answer to the query for node i, for j times.
 *
 * If i is the root node, the answer is simply j.
 *
 * For everything else, we simplify the problem a bit and ask ourselves "how many times do we need
 * to touch the parent of i in order for node i to be touched j times?"
 *
 * We can answer this question by storing some prefix sums, sorting all the children of every node, and doing some math.
 *
 * Then, our answer is simply solve(parent_of_i, number_of_times_we_need_to_touch_i).
 */

#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define pb push_back
#define ll long long

vi adj[100000];
int pa[100000];
int A[100000];
vector<ll> PS[100000];

int solve(int u, int ct) {
    if (pa[u] == -1) {
        return ct;
    }
    int p = pa[u];
    int tgtVal = A[u] - ct;
    auto lowerIt = lower_bound(adj[p].begin(), adj[p].end(), tgtVal+1);
    ll ans = PS[p][lowerIt - adj[p].begin()] - (ll)(tgtVal+1)*(adj[p].end()-lowerIt) + (adj[p].end()-lower_bound(adj[p].begin(),adj[p].end(),A[u]));
    return solve(p, ans);
}

int main() {
    freopen("arb3.in", "r", stdin);
    freopen("arb3.out", "w", stdout);
    cin.tie(NULL); ios_base::sync_with_stdio(false);

    int n, q; cin >> n >> q;
    pa[0] = -1;
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        pa[i] = p-1;
        adj[p-1].pb(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) adj[i][j] = A[adj[i][j]];
        sort(adj[i].begin(), adj[i].end());
    }
    for (int i = 0; i < n; i++) {
        PS[i].resize(adj[i].size());
        for (int j = (int)adj[i].size()-1; j >= 0; j--) {
            PS[i][j] = (j+1<(int)adj[i].size()?PS[i][j+1]:0) + adj[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; --a;
        cout << solve(a, b) << "\n";
    }

    return 0;
}
