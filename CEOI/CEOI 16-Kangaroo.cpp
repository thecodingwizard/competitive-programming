/*
 * DP Component: https://codeforces.com/blog/entry/47764
 *
 * dp[i][j] = number of ordered permutations of first i numbers with j components
 *
 * So { 314, 2, 56 } is different from { 2, 314, 56 }
 *
 * dp[1][1] = 1
 *
 * dp[i][j] = dp[i-1][j-1] + dp[i-1][j] if i = cs or i = cf
 * - We either add a new component in the beginning/end, or we attach to existing first/last component
 *
 * dp[i][j] = dp[i-1][j+1]*j + dp[i-1][j-1]*(j-(i>cs)-(i>cf)) if i != cs and i != cf
 * - The first term: we join two adjacent components. There are j options for adjacent components
 * - The second term: We add a new component. There are j locations for us to add the component, but if i>cs, then we can't add the component in the beginning, so we subtract 1. Likewise for i>cf.
 */

#include <bits/stdc++.h>

using namespace std;

long long dp[2001][2001]; 

int main() {
    int n, cs, cf; cin >> n >> cs >> cf;

    for (int i = 0; i <= n;i++) for (int j = 0; j <= n; j++) dp[i][j] = 0;
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == cs || i == cf) {
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%1000000007;
            } else {
                dp[i][j] = ((dp[i-1][j+1]*j) + dp[i-1][j-1]*(j-(i>cs)-(i>cf))) % 1000000007;
            }
        }
    }
    cout << dp[n][1] << endl;

    return 0;
}
