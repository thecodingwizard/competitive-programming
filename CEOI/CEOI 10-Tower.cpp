/*
 * N is actually very big so we need to think of a greedy solution.
 *
 * Let's sort all the input numbers and process them in ascending order.
 * Let's say there are n ways to arrange the numbers we have found so far.
 *
 * As we add the next number, we can either:
 * - Put it at the very bottom of the tower
 * - Put it right above an existing block of size >= num-D
 *
 * We can solve this greedily in O(n) after sorting (see code).
 */

#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+9;

int main() {
    int n, d; cin >> n >> d;
    vector<int> v; for (int i = 0; i < n; i++) { int x; cin >> x; v.push_back(x); }
    sort(v.begin(), v.end());
    int lptr = 0;
    long long ways = 1;
    for (int rptr = 0; rptr < n; rptr++) {
        while (v[rptr]-v[lptr]>d) lptr++;
        ways = ways*(1+rptr-lptr)%mod;
    }
    cout << ways << endl;
    return 0;
}
