/*
 * Note that two skewers will only ever intersect if their 'R' is along the same diagonal i+j=k
 * For every diagonal k, we do dp on all the cells (i, j) where i+j=k.
 *
 * We only consider the cells that have 'R'. Every time we see an 'R', we need to decide
 * if we are going to: a) skip over it, b) skewer it to the right, or c) skewer it downwards
 *
 * If we skewer it downwards, then for the next two rows, we cannot skewer to the right.
 *
 * Therefore our dp state can be (row, numRowsWeCannotSkewerRight)
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ii pair<int, int>
#define pA first
#define pB second
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define vi vector<int>
#define pb push_back

int main() {
    int n, m; cin >> n >> m;
    char A[n][m]; F0R(i, n) F0R(j, m) cin >> A[i][j];

    int ans = 0;

    int dp[n+1][3];
    F0R(diagonal, n+m) {
        F0R(i, n+1) F0R(j, 3) dp[i][j] = 0;

        int lastI = -1;
        F0R(i, n) {
            int j = diagonal-i;
            if (j < 0 || j >= m) continue;
            lastI = i;
            int right = 0;
            if (j+2<m&& A[i][j] == 'R' && A[i][j+1] == 'G' && A[i][j+2] == 'W') right=1;
            int down = 0;
            if (i+2<n&& A[i][j] == 'R' && A[i+1][j] == 'G' && A[i+2][j] == 'W') down=1;
            dp[i+1][0] = max(dp[i][0] + right, dp[i][1]);
            dp[i+1][1] = dp[i][2];
            dp[i+1][2] = max(dp[i][0], max(dp[i][1], dp[i][2])) + down;
        }
        lastI++;

        // cout << diagonal << " " << max(dp[lastI][0], max(dp[lastI][1], dp[lastI][2])) << endl;
        ans += max(dp[lastI][0], max(dp[lastI][1], dp[lastI][2]));
    }

    cout << ans << endl;

    return 0;
}
