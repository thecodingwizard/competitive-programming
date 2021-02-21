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

const int mod = 1e6+7;
ll dp[2][10010];
ll mx[10010];

int main() {
    cin.tie(0)->sync_with_stdio(0);


    int n; cin >> n;
    vector<ll> A(n);
    F0R(i, n) cin >> A[i];

    ll ans = 0;
    F0R(i, n) {
        dp[1][i] = 1;
        mx[i] = max(i>0?mx[i-1]:0, (i>0?A[i-1]-1:0));
    }
    F0R(i, n) {
        int cur = i%2;
        int prev = !cur;
        F0R(j, n) {
            dp[cur][j] = ((ll)dp[prev][j]*(j+1)+dp[prev][j+1]) % mod;
        }
        if (A[n-1-i]-2 >= 0) {
            ans = (ans + (ll)(A[n-1-i]-1)*dp[prev][mx[n-1-i]]) % mod;
        }
    }
    cout << ans+1 << endl;

    return 0;
}
