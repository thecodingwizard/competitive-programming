/*
 * Same sol as editorial
 */

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

map<int, ll> memo[20];
int dp(ll tgtProduct, int numsLeft, ll prefix, ll mn, ll mx) {
    ll tmp = 1;
    F0R(i, numsLeft) tmp *= 9;
    if (tmp < tgtProduct) return 0;
    __int128 minVal = prefix;
    F0R(i, numsLeft) {
        minVal = minVal*10+1;
    }
    ll curProduct = 1;
    ll x = prefix;
    while (x) {
        curProduct *= x%10;
        x /= 10;
    }
    if (minVal*curProduct*tgtProduct > mx) return 0;

    __int128 maxVal = prefix;
    F0R(i, numsLeft) {
        maxVal = maxVal*10+9;
    }
    if (maxVal*curProduct*tgtProduct < mn) return 0;

    if (minVal*curProduct*tgtProduct >= mn && maxVal*curProduct*tgtProduct <= mx) {
        // cache this DP value
        if (memo[numsLeft].count(tgtProduct)) {
            return memo[numsLeft][tgtProduct];
        }
    }

    if (numsLeft == 0) {
        if (tgtProduct == 1) {
            if (prefix == 0) return 0;
            //cout << mx << " " << prefix << " " << prefix*curProduct << endl;
            return 1;
        }
        return 0;
    }
    ll ans = 0;
    FOR(i, 1, 10) {
        if (tgtProduct % i != 0) continue;
        ans += dp(tgtProduct/i, numsLeft-1, prefix*10+i, mn, mx);
    }
    if (minVal*curProduct*tgtProduct >= mn && maxVal*curProduct*tgtProduct <= mx) {
        // cache this DP value
        memo[numsLeft][tgtProduct] = ans;
    }
    return ans;
}

ll solve(ll x, ll y) {
    ll ans = 0;
    for (ll n2 = 1; n2 <= y; n2 *= 2) {
        for (ll n3 = 1; n2*n3 <= y; n3 *= 3) {
            for (ll n5 = 1; n2*n3*n5 <= y; n5 *= 5) {
                for (ll n7 = 1; n2*n3*n5*n7 <= y; n7 *= 7) {
                    ll tgt = n2*n3*n5*n7;
                    for (int numDigits = 0; numDigits <= 18; numDigits++) {
                        ans += dp(tgt, numDigits, 0, x, y);
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a, b; cin >> a >> b;
    cout << solve(a, b) << endl;

    return 0;
}
