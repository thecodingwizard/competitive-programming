#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, m, k;
vii words;
map<int, vii> rhymeClass;
ll rhymeClassWays[5010];
ll dp[10100];
ll mod = 1000000007;

/* Calculates (base^pwr)%mod in O(log pwr) */
ll power(ll base, ll pwr, ll mod) {
    ll res = 1;
    base = base % mod;
    while (pwr > 0) {
        if (pwr & 1) res = (res*base) % mod;
        pwr = pwr >> 1;
        base = (base*base)%mod;
    }
    return res;
}

int main() {
    setupIO("poetry");

    cin >> n >> m >> k;
    F0R(i, n) {
        int s, c; cin >> s >> c;
        c--;
        words.pb(mp(s, c));
        rhymeClass[c].pb(mp(s, c));
    }

    SET(dp, 0, 10100);
    dp[0] = 1;
    F0R(i, k) {
        for (ii word : words) {
            dp[i + word.pA] += dp[i];
            dp[i + word.pA] %= mod;
        }
    }

    SET(rhymeClassWays, 0, n);
    for (ii word : words) {
        rhymeClassWays[word.pB] += dp[k - word.pA];
        rhymeClassWays[word.pB] %= mod;
    }

    map<char, int> scheme;
    F0R(i, m) {
        char c; cin >> c;
        scheme[c]++;
    }

    ll ans = 1;
    for (auto const &x : scheme) {
        int ct = x.pB;
        ll toMultiply = 0;
        F0R(i, n) {
            if (rhymeClassWays[i] == 0) continue;
            toMultiply += power(rhymeClassWays[i], ct, mod);
            toMultiply %= mod;
        }
        ans = (ans * toMultiply) % mod;
    }

    cout << ans << endl;

    return 0;
}
