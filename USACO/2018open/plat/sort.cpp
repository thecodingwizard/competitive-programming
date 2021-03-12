/**
 * The official editorial is simpler :/
 * The idea behind my solution is the same but it's more complicated
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
            rb_tree_tag, tree_order_statistics_node_update>; 

int numSmallerLeft[100000], numSmallerRight[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n; cin >> n;
    vector<int> A(n);
    F0R(i, n) cin >> A[i];

    ll ans = 0;
    int left[n], right[n];

    vector<ii> leftNums;
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(all(leftNums), mp(A[i], i));
        if (it == leftNums.end()) left[i] = -1;
        else left[i] = it->s;
        if (leftNums.empty() || leftNums.back().f < A[i]) {
            leftNums.pb(mp(A[i], i));
        }
    }
    vector<ii> rightNums;
    for (int i = n-1; ~i; i--) {
        auto it = lower_bound(rightNums.rbegin(), rightNums.rend(), mp(A[i], -inf));
        if (it == rightNums.rbegin()) right[i] = -1;
        else {
            if (it != rightNums.rend() && it->f < A[i]) {
                cout << it->f << " " << A[i] << endl;
            }
            right[i] = (--it)->s;
            assert(it->f < A[i]);
        }
        if (rightNums.empty() || rightNums.back().f > A[i]) {
            rightNums.pb(mp(A[i], i));
        }
    }

    // exclusive on endpoints
    vector<vector<ii>> leftQueries(n), rightQueries(n);
    for (int i = 0; i < n; i++) {
        if (left[i] != -1) {
            if (left[i]<n-1) leftQueries[left[i]+1].pb(mp(i, -1));
            leftQueries[i].pb(mp(i, 1));
        }
        if (right[i] != -1) {
            rightQueries[i].pb(mp(i, 1));
            if (right[i]>0) rightQueries[right[i]-1].pb(mp(i, -1));
        }
    }

    Tree<ii> leftTree, rightTree;
    for (int i = 0; i < n; i++) {
        for (auto q : leftQueries[i]) {
            numSmallerLeft[q.f] += q.s*leftTree.order_of_key(mp(A[q.f], inf));
        }
        leftTree.insert(mp(A[i], i));
    }
    for (int i = n-1; ~i; i--) {
        for (auto q : rightQueries[i]) {
            numSmallerRight[q.f] += q.s*rightTree.order_of_key(mp(A[q.f], -inf));
        }
        rightTree.insert(mp(A[i], i));
    }

    for (int i = 0; i < n; i++) {
        if (left[i] != -1) {
            ans += i-left[i] - numSmallerLeft[i];
        }
        if (right[i] != -1) {
            ans += right[i]-i - numSmallerRight[i];
        }
        if (left[i] == -1 && right[i] == -1) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
