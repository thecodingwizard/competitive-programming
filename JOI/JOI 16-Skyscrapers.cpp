/*
 * DP Component: https://codeforces.com/blog/entry/47764
 *
 * My code has ORDERED components
 *
 * Note that if n = 1, the answer is 1
 */

#include <bits/stdc++.h>

using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define ll long long

void add(ll &a, ll b) {
    a = (a + b) % 1000000007;
}

ll A[101]; 
ll dp[101][101][1001][3];
int main() {
    int n, L; cin >> n >> L;

    F0R(i, n) cin >> A[i];
    sort(A, A+n);

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    F0R(i, n+1) F0R(j, n+1) F0R(k, L+1) F0R(m, 3) dp[i][j][k][m] = 0;
    dp[0][0][0][0] = 1;
    A[n] = 2000;
    for (int i = 0; i < n; i++) {
        ll diff = A[i+1] - A[i];
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= L; k++) {
                for (int l = 0; l <= 2; l++) {
                    if (dp[i][j][k][l] == 0) continue;
                    // fill in an endpoint
                    if (l < 2) {
                        // create new component
                        int k2 = k + diff*(2*j-l+1);
                        if (k2 <= L) {
                            add(dp[i+1][j+1][k2][l+1], dp[i][j][k][l]*(2-l));
                        }
                        // merge with a component
                        if (j > 0) {
                            k2 = k + diff*(2*j-l-1);
                            if (k2 <= L) add(dp[i+1][j][k2][l+1], dp[i][j][k][l]*(2-l));
                        }
                    }
                    // create a new component
                    int k2 = k + diff*(2*j-l+2);
                    if (k2 <= L) add(dp[i+1][j+1][k2][l], dp[i][j][k][l]*(j-l+1));
                    // append to a component
                    k2 = k + diff*(2*j-l);
                    if (k2 <= L) add(dp[i+1][j][k2][l], dp[i][j][k][l]*(2*j-l));
                    // merge two components
                    if (j >= 2) {
                        k2 = k + diff*(2*j-l-2);
                        if (k2 <= L) add(dp[i+1][j-1][k2][l], dp[i][j][k][l]*(j-1));
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= L; i++) {
        add(ans, dp[n][1][i][2]);
    }
    cout << ans << endl;

    return 0;
}
