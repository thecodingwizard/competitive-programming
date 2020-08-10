/*
 * Translated problem statement:
 * You're given N (1 <= N <= 2e5) dolls. Each doll has a radius (1 <= r <= 1e9) and a height (1 <= h <= 1e9).
 * You're given Q (1 <= Q <= 2e5) queries. Each query is represented by two numbers, (A, B).
 *
 * For a given query (A, B), we need to "package" all the dolls whose radius is >= A, and whose height is <= B.
 * A doll can be "nested" in another doll (it's like a Russian nested doll). One doll can
 * only be nested in another if both its radius and its height is strictly less than its "parent" doll.
 * Each doll can only have one immediate nested doll, though the nested doll can contain another nested
 * doll, and so on.
 *
 * For each query, we want to find out the minimum number of "root"/"top-level" dolls we need to ship.
 * If a doll is nested inside another doll, it doesn't count towards this number.
 *
 * The sample input is helpful for understanding the problem.
 *
 *
 *
 * Solution:
 *
 * Dilworth's Theorem!
 *
 * Sort queries offline and process them from greatest radius to least radius. Add dolls that satisfy
 * the radius requirement. Now we need to handle the height requirement.
 *
 * Let's write out the heights of all the dolls, sorted by decreasing doll radius. Note that the
 * a valid configuration would just be some number of strictly decreasing subsequences of heights
 * such that each doll is in one of these subsequences.
 *
 * By Dilworth's theorem, the minimum number of these subsequences is equal to the length of the
 * longest increasing subsequence!
 *
 * We can find this in logn per query/doll; see the code below.
 *
 * Note that dolls with the same radius can't be nested in each other. Therefore, when we write
 * the heights of all the dolls, we will first sort by decreasing doll radius. If two dolls have
 * the same radius, we'll sort by *increasing* height in order to ensure that they don't get
 * nested in each other.
 */

#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;

#define ii pair<int, int>
#define f first
#define s second

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    int n, q; cin >> n >> q;

    vector<ii> A;
    for (int i = 0; i < n; i++) {
        int r, h; cin >> r >> h; A.push_back(make_pair(r, h));
    }
    sort(A.begin(), A.end(), [](const ii &l, const ii &r) {
        return l.f == r.f ? l.s > r.s : l.f > r.f;
    });
    int ans[q];
    vector<pair<ii, int>> queries;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        queries.push_back(make_pair(make_pair(a, b), i));
    }
    sort(queries.begin(), queries.end());
    reverse(queries.begin(), queries.end());

    int idx = 0;
    vector<int> LIS; LIS.assign(n+10, 1e9+10);
    for (int i = 0; i < q; i++) {
        ii qry = queries[i].f;
        while (idx < n && A[idx].f >= qry.f) {
            *upper_bound(LIS.begin(), LIS.end(), A[idx].s) = A[idx].s;
            idx++;
        }

        ans[queries[i].s] = upper_bound(LIS.begin(), LIS.end(), qry.s) - LIS.begin();
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
