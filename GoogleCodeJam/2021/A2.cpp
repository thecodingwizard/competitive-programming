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

void solve() {
    int x, y; cin >> x >> y;
    string s; cin >> s;
    int n = sz(s);
    vector<vector<int>> dp(n);
    F0R(i, n) dp[i].assign(2, inf);
    dp[0][0] = s[0] == 'J' ? inf : 0;
    dp[0][1] = s[0] == 'C' ? inf : 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'C') {
            dp[i][0] = min(dp[i-1][1] + y, dp[i-1][0]);
        } else if (s[i] == 'J') {
            dp[i][1] = min(dp[i-1][1], dp[i-1][0] + x);
        } else {
            dp[i][0] = min(dp[i-1][1] + y, dp[i-1][0]);
            dp[i][1] = min(dp[i-1][1], dp[i-1][0] + x);
        }
    }
    cout << min(dp[n-1][0], dp[n-1][1]) << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
