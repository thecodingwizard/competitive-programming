/*
 * https://github.com/stefdasca/CompetitiveProgramming/blob/master/COCI/COCI%2009-Gremlini.cpp
 *
 * Matrix exponentiation, but instead of using matrix multiplication, use https://en.wikipedia.org/wiki/Min-plus_matrix_multiplication
 *
 * Note that this operation is still associative, so we can continue to use matrix exponentiation.
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

const ll inf = 1e18;
const int logt = 50;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, t; cin >> n >> t;

    ll time[logt][100][100];
    F0R(i, logt) F0R(j, n) F0R(k, n) time[i][j][k] = inf;

    F0R(i, n) {
        ll k, y; cin >> k >> y;
        vector<ll> types, times;
        F0R(i, k) {
            int x; cin >> x; --x; types.pb(x);
        }
        F0R(i, k) {
            int x; cin >> x; times.pb(x);
        }
        F0R(j, k) {
            time[0][i][types[j]] = min(time[0][i][types[j]], times[j]+y);
        }
    }

    FOR(i, 1, logt) {
        F0R(j, n) {
            F0R(k, n) {
                F0R(l, n) {
                    time[i][j][k] = min(time[i][j][k], time[i-1][j][l] + time[i-1][l][k]);
                }
            }
        }
        F0R(j, n) {
            F0R(k, n) {
                //cout << "time[" << i << "][" << j << "][" << k << "] = " << time[i][j][k] << endl;
            }
        }
    }

    ll ans = 0;
    ll cur[100][100]; F0R(j, n) F0R(k, n) cur[j][k] = 0;
    for (int i = logt-1; ~i; i--) {
        ll nxt[100][100];
        F0R(j, n) F0R(k, n) nxt[j][k] = inf;
        F0R(j, n) {
            F0R(k, n) {
                F0R(l, n) {
                    nxt[j][k] = min(nxt[j][k], cur[j][l] + time[i][l][k]);
                }
            }
        }

        bool g = 0;
        F0R(i, n) F0R(j, n) if (nxt[i][j] <= t) g = 1;
        if (g) {
            ans |= (1LL << i);
            F0R(i, n) F0R(j, n) cur[i][j] = nxt[i][j];
        }
    }

    cout << ans << endl;

    return 0;
}
