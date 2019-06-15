/*
 * Subset 1: Brute Force
 * Subset 2: DP
 *
 * Subset 3: To handle d=2, let's set each number's 20th bit to be 1. Clearly, we must now
 * select an even number of numbers, because if we don't then our extra bit will be turned on.
 * Hence, we have turned d=2 into d=1.
 *
 * How do we solve d=1? Let's process each new number individually. If we are processing a number
 * that we can already form using our existing numbers, then we double the number of ways we can form
 * any number (since for each existing way, we can now add in our new number and remove some subset
 * of our old numbers to still reach the same destination). If we are processing a number that
 * we can't form using our existing numbers, then for every number we can currently reach,
 * we will XOR it with the new number. The result will be a number that we couldn't have reached
 * before.
 *
 * Subset 4 + 5: See other file
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

int mod = 1000000007;
// Subset 2
/*
 * DP[i][j][k] = # of ways to use numbers from 0...i
 * s.t. the xor of all those numbers = j
 * And the # of #s mod d is k
 *
 * Sliding window on i
 */
ll dp[2][2000][10];
// Subset 3
bool seen[3000000];

int main() {
    setupIO();

    int n, d; cin >> n >> d;
    int A[n];
    int maxA = 0;
    F0R(i, n) {
        cin >> A[i];
        MAX(maxA, A[i]);
    }
    int tgt = 0; F0R(i, n) tgt ^= A[i];
    if (n <= 20) {
        // Subset 1
        ll ans = 0;
        F0R(i, (1 << n) - 1) {
            int num = 0;
            if (__builtin_popcount(i) % d == 0) {
                F0R(j, n) {
                    if (i & (1 << j)) num ^= A[j];
                }
            }
            if (num == tgt) ans++;
        }
        cout << ans << endl;
    } else if (n <= 10000 && maxA <= 1000) {
        // Subset 2
        assert(tgt < 2000);
        SET3D(dp, 0, 2, 2000, 10);
        dp[0][0][0] = 1;
        F0R(i, n) {
            int cur = i % 2, nxt = (i + 1) % 2;
            F0R(j, 2000) F0R(k, 10) dp[nxt][j][k] = dp[cur][j][k];
            F0R(j, 2000) {
                F0R(k, 10) {
                    dp[nxt][j ^ A[i]][(k + 1) % d] += dp[cur][j][k];
                    if (dp[nxt][j ^ A[i]][(k + 1) % d] >= mod) dp[nxt][j ^ A[i]][(k + 1) % d] -= mod;
                }
            }
        }
        // Edge case: Removing *all* the heaps is illegal
        bool canRemoveAll = n % d == 0;
        if (canRemoveAll) {
            dp[n%2][tgt][0] += mod - 1;
            dp[n%2][tgt][0] %= mod;
        }
        cout << dp[n%2][tgt][0] << endl;
    } else if (d <= 2) {
        // Subset 3
        if (d == 2) F0R(i, n) A[i] |= (1 << 20); // Trick to handle d=2: Just add another bit to every number so must be even # of #s
        SET(seen, false, 3000000);
        seen[0] = true;
        ll ans = 1;
        F0R(i, n) {
            if (seen[A[i]]) {
                ans = ans * 2 % mod;
            } else {
                F0R(j, 3000000) {
                    if (seen[j]) seen[j ^ A[i]] = true;
                }
                seen[A[i]] = true;
            }
        }
        // Edge case: Removing *all* the heaps is illegal
        bool canRemoveAll = n % d == 0;
        if (canRemoveAll) {
            ans += mod - 1;
            ans %= mod;
        }
        cout << ans << endl;
    } else {
        // Subset 4 + 5, see other file
    }

    return 0;
}