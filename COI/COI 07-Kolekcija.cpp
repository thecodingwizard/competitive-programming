/*
 * Note that order + duplicates don't matter, so sort + remove duplicates
 *
 * Then, define dp[i] = minimum cost to cover [i...end]
 *
 * Note that the transition for dp[i] is decreasing, so keep a right pointer
 * for where to transition to.
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    int m; cin >> m;
    vector<int> A; A.resize(m);
    for (int i = 0; i < m; i++) cin >> A[i];
    vector<int> queries(A);
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    m = A.size();

    int dp[m], next[m];
    int optimal = m-1;
    int mxOptimal = m-1;
    int rptr = m-1;
    for (int i = m-1; ~i; i--) {
        while (optimal - 1 >= 0 && A[optimal-1] - A[i] + 1 >= k) {
            optimal--;
        }
        dp[i] = max(k, A[m-1]-A[i]+1);
        next[i] = m;
        if (i != m-1) {
            if (dp[i+1]+A[i+1]-A[i] < dp[i]) {
                dp[i] = dp[i+1]+A[i+1]-A[i];
                next[i] = next[i+1];
            }
        }
        for (int x = mxOptimal; x >= optimal; x--) {
            int opt = max(A[x-1]-A[i]+1, k) + dp[x];
            if (opt < dp[i]) {
                dp[i] = opt;
                next[i] = x;
            }
            mxOptimal = x;
        }
    }
    
    cout << dp[0] << endl;

    int cur = 0;
    while (cur != m) {
        for (int i = cur; i < next[cur]; i++) {
            next[i] = next[cur];
        }
        cur = next[cur];
    }


    map<int, int> idx;
    for (int i = 0; i < m; i++) {
        idx[A[i]] = i;
    }
    for (int x = 0; x < queries.size(); x++) {
        int i = idx[queries[x]];
        int tgt = A[next[i]-1];
        if (tgt-k+1 <= A[i]) {
            if (tgt-k+1 <= 0) {
                cout << 1 << " " << k << "\n";
            } else {
                cout << tgt-k+1 << " " << tgt << "\n";
            }
        } else {
            if (A[i]+k-1 <= n) {
                cout << A[i] << " " << A[i]+k-1 << "\n";
            } else {
                cout << n-k+1 << " " << n << "\n";
            }
        }
    }

    return 0;
}
