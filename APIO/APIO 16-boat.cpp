/*
 * https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/APIO/16-Boat.cpp
 *
 * the number of ways to assign j schools to len boat options is (len+j-1) choose j (assuming you fix the first school).
 *
 * One way to think about this is you need to choose j options to assign to schools; or,
 * a school can be told to not send any boats (but the first school must send boats).
 * So, you have len possible options for boat assignments and j-1 schools you can
 * tell to not send boats; you need to choose j of these.
 *
 * for the schools that need to send boats, there is one way to assign them to the
 * selected boat option spots.
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

const int mod = 1e9+7;

ll binpow(ll x, ll n, ll m) {
    assert(n >= 0);
    x %= m; //note: m*m must be less than 2^63 to avoid ll overflow
    ll res = 1;
    while (n > 0) {
        if (n % 2 == 1) //if n is odd
            res = res * x % m;
        x = x * x % m;
        n /= 2; //divide by two
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    ii A[n];
    map<int, int> compress;
    set<int> setValues; setValues.insert(0); setValues.insert(1);
    F0R(i, n) {
        cin >> A[i].f >> A[i].s;
        A[i].s++;
        setValues.insert(A[i].f);
        setValues.insert(A[i].s);
    }
    int idx = 0;
    vector<int> values;
    for (auto x : setValues) {
        compress[x] = idx;
        values.pb(x);
        idx++;
    }
    F0R(i, n) {
        A[i].f = compress[A[i].f];
        A[i].s = compress[A[i].s];
    }

    // ct[i][j] = nCr(len + j - 1, j)
    int ct[values.size()][n+1];
    F0R(i, values.size()-1) {
        F0R(j, n+1) {
            if (j == 0) ct[i][j] = 0;
            else {
                int len = values[i+1]-values[i];
                if (j == 1) ct[i][j] = len;
                else {
                    ct[i][j] = ((ll)ct[i][j-1]*(len+j-1)%mod*binpow(j, mod-2, mod))%mod;
                }
            }
        }
        ct[i][0] = 0;
    }

    int dp[n][values.size()];
    int dpSum[n][values.size()];
    F0R(i, n) {
        F0R(j, values.size()-1) {
            if (j == 0) { dp[i][j] = 1; continue; }

            dp[i][j] = 0;
            int num = 0;
            for (int k = i-1; k >= -1; k--) {
                if (A[k+1].f <= j && A[k+1].s > j) {
                    num++;
                    dp[i][j] = (dp[i][j] + (ll)(k>=0?dpSum[k][j-1]:1)*ct[j][num])%mod;
                }
            }
        }
        F0R(j, values.size()-1) {
            dpSum[i][j] = ((j?dpSum[i][j-1]:0)+dp[i][j])%mod;
        }
    }

    ll ans = 0;
    FOR(j, 1, values.size()-1) {
        ans = (ans + dp[n-1][j]) % mod;
    }
    cout << ans << endl;

    return 0;
}
