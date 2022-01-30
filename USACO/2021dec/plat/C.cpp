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

int n, x; 
const int mod = 1000000007;
ll inverse(ll x) {
    ll res = 1;
    ll exp = mod-2;
    while (exp) {
        if (exp & 1) {
            res = res * x % mod;
        }
        x = x*x%mod;
        exp /= 2;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    int y = n - x;

    ll dp[2][x+1][y+1];
    ll memo[y+1], memo2[x+1];
    ll inv[n+1];
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            dp[0][i][j] = dp[1][i][j] = 0;
        }
    }
    for (int i = 0; i <= x; i++) memo2[i] = 0;
    for (int j = 0; j <= y; j++) memo[j] = 0;
    for (int i = 0; i <= n; i++) inv[i] = inverse(i);

    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            /*
            for (int k = 0; k < i; k++) {
                dp[0][i][j] += dp[0][k][j];
            }
            for (int k = 0; k < j; k++) {
                dp[0][i][j] += dp[1][i][k];
            }
            */
            if (i > 0) {
                memo[j] = (memo[j]+dp[0][i-1][j])%mod;
            }
            if (j > 0) {
                memo2[i] = (memo2[i]+dp[1][i][j-1])%mod;
            }
            dp[0][i][j] = memo[j] + memo2[i];
            dp[0][i][j] = dp[0][i][j]%mod*inv[i+j]%mod;
            dp[1][i][j] = (dp[0][i][j]+(ll)i*inv[i+j])%mod;
        }
    }

    ll ans = dp[0][x][y];
    for (int i = 0; i < n; i++) {
        ans = (ans*(i+1))%mod;
    }
    cout << ans << endl;

    return 0;
}
