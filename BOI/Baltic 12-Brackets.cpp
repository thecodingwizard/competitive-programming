/*
 * dp[i][j] = # of ways to end up on index i with sum j, assuming (/[ = +1 and )/] = -1.
 *
 * if i+1 is (, then dp[i+1][j+1] += dp[i][j]
 * 
 * Additionally, dp[i+1][j-1] += dp[i][j]. This is true if i+1 = ), and is also
 * true if i+1 = ( because we can convert that ( and the previous opening ( to become [].
 *
 * Sliding window on i
 */

#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+9;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    int n; cin >> n;
    string A; cin >> A;

    int dp[2][n];
    for (int i = 0; i < n; i++) dp[0][i] = 0;
    dp[0][1] = 1;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) dp[(i+1)%2][j] = 0;
        for (int j = 0; j < n; j++) {
            if (dp[i%2][j] == 0) continue;

            if (A[i+1] == '(') dp[(i+1)%2][j+1] = (dp[(i+1)%2][j+1]+dp[i%2][j])%mod;
            if (j-1>=0) dp[(i+1)%2][j-1] = (dp[(i+1)%2][j-1]+dp[i%2][j])%mod;
        }
    }

    cout << dp[(n-1)%2][0] << endl;

    return 0;
}
