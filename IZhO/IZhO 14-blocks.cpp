/*
 * define dp[i][j] = min cost to group first i integers into j groups.
 * For ease of implementation, we'll actually make it a pair: The first number
 * is the cost of the first (j-1) groups, and the second number is the maximum
 * number in the last group (the jth group). Therefore, the min cost is actually dp.f + dp.s
 *
 * (the following explanation is very sketchy oops)
 *
 * A naive implementation is O(n^2) where you check every k < i. However, let's say you have computed
 * dp[k][j] already, and you are computing dp[i][j] where i > k and A[i] < dp[k][j].s. Note that
 * if this is the case, you don't have to check any x < k, because you already checked that in dp[k][j].
 *
 * This motivates a solution where you maintain a stack of dp values. When computing dp[i][j], repeatedly
 * pop the stack until the stack.top().s > A[i]. Every time you pop, update dp[i][j]. Finally,
 * update dp[i][j] for the top value on the stack.
 *
 * See the code below for more clarity (?)
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int main() {
    cin.tie(0); ios::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    int A[n+1]; for (int i = 1; i <= n; i++) cin >> A[i];

    ii dp[n+1][k+1];
    dp[0][0] = mp(0, 0);
    for (int i = 1; i <= n; i++) dp[i][0] = mp(1e9, 1e9);
    for (int j = 1; j <= k; j++) {
        stack<ii> s;
        for (int i = j; i <= n; i++) {
            dp[i][j] = mp(dp[i-1][j-1].f+dp[i-1][j-1].s, A[i]);
            while (!s.empty() && s.top().s <= A[i]) {
                if (s.top().f+A[i] < dp[i][j].f+dp[i][j].s) {
                    dp[i][j] = mp(s.top().f, A[i]);
                }
                s.pop();
            }
            if (!s.empty()) {
                if (s.top().f + s.top().s < dp[i][j].f + dp[i][j].s) {
                    dp[i][j] = s.top();
                }
            }
            s.push(dp[i][j]);
        }
    }
    cout << dp[n][k].f + dp[n][k].s << endl;
}
