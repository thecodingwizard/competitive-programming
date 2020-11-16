#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

const int mod = 1000000007;
#define maxn 2000
int dp[maxn][maxn];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, cs, cf; cin >> n >> cs >> cf; --cs; --cf;
    dp[0][1] = 1;

    for (int i = 1; i < n; i++) {
        F0R(j, n) {
            if (i == cs) {
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % mod;
            } else if (i == cf) {
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % mod;
            } else {
                dp[i][j] = ((ll)dp[i-1][j-1]*(j-(i>cs)-(i>cf)) + (ll)dp[i-1][j+1]*j) % mod;
            }
        }
    }

    cout << dp[n-1][1] << endl;

    return 0;
}
