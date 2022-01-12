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
const int maxn = 5001;
const int mod = 1000000007;
ll ncr[maxn][maxn];
ll fact[maxn];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    ncr[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            ncr[i][j] = ((ll)(j>0?ncr[i-1][j-1]:0)+ncr[i-1][j])%mod;
        }
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (ll)fact[i-1]*i%mod;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (j > x && i <= x) {}
            else continue;
            int a = i-1, b = (j-i-1), c = n-j;

            ll cur = 0;
            for (int z = b; z <= n-2; z++) {
                for (int x = max((a+b)-z, 0); x <= n-2-z; x++) {
                    cur = (cur + ncr[z][b]%mod * ncr[z-b+x][a]%mod) % mod;
                }
            }
            cur = cur*fact[b]%mod*fact[a]%mod*fact[c]%mod;
            ans = (ans + cur) % mod;
        }
    }
    cout << ans << endl;

    return 0;
}
