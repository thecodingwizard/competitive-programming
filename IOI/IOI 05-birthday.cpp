/*
 * Binary search on answer
 *
 * To test if an answer works, for every number, we calculate how much we can shift
 * the ending permutation such that the number can reach its ending destination
 * within the maximum number of moves. Note that the range we can shift the permutation
 * for a particular number is contiguous, [L...R] (it might wrap around to n, in which
 * case it will be split into two contiguous sections). Therefore, given a lot of
 * these ranges, we just have to see if there's a number that's within every
 * range.
 */

#include <bits/stdc++.h>

using namespace std;

int n; 
int A[1000000];
int loc[1000001];
int delta[1000004];

int solve() {
    for (int i = 0; i < n; i++) {
        loc[A[i]] = i;
    }

    int lo = 0, hi = n/2, mid, ans = n/2;

    while (lo < hi) {
        mid = (lo + hi) >> 1;

        for (int i = 0; i < n; i++) {
            int dist = loc[i+1] - i;
            if (dist < 0) dist += n;

            if (dist == 0) {
                delta[n-mid]++;
                delta[0]++;
                delta[mid+1]--;
                continue;
            }

            int small = n-mid-dist, large = mid - dist;
            if (small < 0) small += n;
            if (large < 0) large += n;
            if (small >= n) small -= n;
            if (large >= n) large -= n;

            if (small <= large) {
                delta[small]++;
                delta[large+1]--;
            } else {
                delta[small]++;
                delta[0]++;
                delta[large+1]--;
            }
        }

        int ctr = 0;
        bool good = false;
        for (int i = 0; i <= n; i++) {
            ctr += delta[i];
            if (ctr == n) {
                good = true;
            }
            delta[i] = 0;
        }

        if (good) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return ans;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    cin >> n; for (int i = 0; i < n; i++) cin >> A[i];

    int ans = solve();
    for (int i = 0; i < n/2; i++) {
        swap(A[i], A[n-1-i]);
    }
    ans = min(ans, solve());
    cout << ans << "\n";

    return 0;
}
