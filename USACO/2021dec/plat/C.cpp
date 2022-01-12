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
const int maxn = 510;
const int mod = 1000000007;
ll memo[maxn][maxn][2];
ll ncr[maxn][maxn];
ll fact[maxn];
ll dp(int lo, int hi, bool wasHi) {
    if (lo > hi) {
        return 0;
    }
    if (memo[lo][hi][wasHi] != -1) return memo[lo][hi][wasHi];

    ll ans = 0;
    for (int guess = lo; guess <= hi; guess++) {
        ll prev = ans;
        bool isLo = guess <= x;
        int leftover = isLo ? guess - lo : hi - guess;
        int remainingNums = isLo ? hi - guess : guess - lo;
        assert(leftover + remainingNums + 1 == hi - lo + 1);
        ll multiplier = ncr[remainingNums+leftover][leftover]*fact[leftover]%mod;
        if (isLo && wasHi) {
            ans = (ans + fact[remainingNums+leftover]) % mod;
        }
        if (isLo) {
            ans = (ans + dp(guess + 1, hi, false)*multiplier) % mod;
        } else {
            ans = (ans + dp(lo, guess - 1, true)*multiplier) % mod;
        }
    }
    return memo[lo][hi][wasHi] = ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    if (n > maxn) return 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j][0] = memo[i][j][1] = -1;
        }
    }
    ncr[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            ncr[i][j] = ((j>0?ncr[i-1][j-1]:0)+ncr[i-1][j])%mod;
        }
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1]*i%mod;
    }
    cout << dp(1, n, 0) << endl;

    return 0;
}
