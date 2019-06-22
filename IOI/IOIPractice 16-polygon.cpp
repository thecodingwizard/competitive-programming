/*
 * DP[i][j] = number of ways to draw j lines with i vertices.
 *
 * O(n^2) state, O(n^2) transition = O(n^4).
 *
 * My implementation had some overcounting so I have to divide by k (using modular multiplicative inverse)
 * for each DP value. I'm not too sure why this works, I figured it out by trial and error :P
 */

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
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
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

ll mod = 1000000007;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

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

// Find modular multiplicative inverse of x under modulo m
ll modInverse(ll x, ll m) {
    ll g = gcd(x, m);
    if (g != 1) {
        // Inverse doesn't exist!!
        return -1;
    } else {
        // answer is x^(m-2) % m
        return power(x, m - 2, m);
    }
}

ll memo[126][126];
ll dp(int n, int k) {
    if (memo[n][k] != -1) return memo[n][k];
    if (n < 3) return 0;
    if (k == 0) return 1;
    ll ways = 0;
    FOR(i, 2, n - 1) {
        if (i + 1 > (n-i) + 1) break;
        F0R(x, k) {
            ways = (ways + (((i * 2 == n ? n/2 : n)*dp(i + 1, x)) % mod) * dp((n - i) + 1, k - 1 - x)) % mod;
        }
    }
    return memo[n][k] = (ways * modInverse(k, mod)) % mod;
}

int main() {
    setupIO();

    int n, k; cin >> n >> k;
    SET2D(memo, -1, 126, 126);
    cout << dp(n, k - 1) << endl;

    return 0;
}