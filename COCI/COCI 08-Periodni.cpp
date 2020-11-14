/*
 * Same solution as editorial
 *
 * dp(i, j, k, baseHeight) = number of ways to put k elements
 * in the histograph bounded by [i...j] on the x-axis, and with a lower bound of
 * y = baseHeight.
 *
 * To transition:
 * - If i > j, then return 1 if k = 0, else return 0
 * - if there exists a 0-height column (taking into account baseHeight), then split the histogram into two histograms without the 0-height column
 * - Else, remove the tallest rectangle possible that spans the entire range [i...j].
 *   We will be left with a histogram with a 0-height column.
 *   - We loop through x where x is the # of elements we want to put in the rectangle.
 *     If the rectangle is width by height, then we first remove (k-x) columns since
 *     they will have elements on them; then, we use math to assign x elements to the remaining width-(k-x) by height histogram
 * - The state looks like n^3 * 1000000, but actually we can show that the number of
 *   states is linear to the width of the histogram, multiplied by k.
 * - Why? The baseHeight can only really take on two values for a given [i, j].
 * - Every dp call makes [i, j] get smaller: the third transition reduces
 *   to the second transition, and the second transition reduces to two smaller widths
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define mod 1000000007
vector<int> A;
int minIdx[500][500];
int fact[1000001];
int inv[1000001];

int binpow(ll x, ll n, ll m) {
    ll res = 1;
    while (n > 0) {
        if (n % 2 == 1) res = res*x%m;
        x = x*x%m;
        n /= 2;
    }
    return res;
}

map<pair<ii, ii>, int> memo;
int dp(int i, int j, int k, int baseHeight) {
    if (i > j) {
        return k == 0 ? 1 : 0;
    }
    if (j-i+1 < k) {
        return 0;
    }

    int small = minIdx[i][j];
    assert(A[small] >= baseHeight);

    pair<ii, ii> key = mp(mp(i, j), mp(k, baseHeight));
    if (memo.count(key)) return memo[key];

    if (A[small] == baseHeight) {
        if (i == j) {
            return memo[key] = (k == 0 ? 1 : 0);
        }
        int ways = 0;
        for (int x = 0; x <= k; x++) {
            ways = (ways + (ll)dp(i, small-1, x, baseHeight) * dp(small+1, j, k-x, baseHeight)) % mod;
        }
        return memo[key] = ways;
    }

    int width = j-i+1, height = A[small] - baseHeight;

    int ways = 0;
    for (int x = 0; x <= k; x++) {
        if (width-x < k-x || height < k-x) continue;
        // ((width-x) choose (k-x))*(height choose k-x)*(k-x)!
        ll waysInRect = (ll)fact[width-x]*inv[width-x-(k-x)]%mod*inv[k-x]%mod*fact[height]%mod*inv[height-(k-x)]%mod*inv[k-x]%mod*fact[k-x]%mod;
        ways = (ways + (ll)dp(i, j, x, A[small])*waysInRect) % mod;
    }
    return memo[key] = ways;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    F0R(i, n) {
        int x; cin >> x;
        A.pb(x);
    }
    F0R(i, n) {
        int small = inf, smallIdx;
        FOR(j, i, n) {
            if (small > A[j]) {
                small = A[j];
                smallIdx = j;
            }
            minIdx[i][j] = smallIdx;
        }
    }

    F0R(i, 1000001) {
        fact[i] = i == 0 ? 1 : (ll)fact[i-1]*i%mod;
    }
    F0R(i, 1000001) {
        inv[i] = binpow(fact[i], mod-2, mod);
    }
    cout << dp(0, n-1, k, 0) << endl;

    return 0;
}
