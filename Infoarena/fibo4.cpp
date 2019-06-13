/*
 * First batch: Just brute force
 *
 * Second batch: Since fibonacci number is just the previous two numbers added up, you can solve
 * in linear time. For each query, update A[start], A[start+1], A[end+1], A[end+2]. Then, after all the queries,
 * run a loop: A[i] += A[i-1] + A[i-2].
 *
 * Third + Fourth batch: nth fibonacci number mod m repeats at 1, 1 after some time (Pisano period). Therefore,
 * we can just brute force up to 2 million fibonacci numbers, stopping when we hit 1, 1 for the second time.
 * We should hit it around 1.3 million. Then to take nth fibonacci number, it's just fib(n % repeatSize)
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

int mod = 666013;

int n, m;

int dp[2000000];
ll repeatSize = LL_INF;
int fib(ll n) {
    if (n > repeatSize) {
        return fib(n%repeatSize);
    }
    if (dp[n] != -1) return dp[n];
    if (n == 0) return 1;
    if (n == 1) return 1;
    return dp[n] = (fib(n-1) + fib(n-2)) % mod;
}

int main() {
    setupIO("fibo4");

    SET(dp, -1, 2000000);

    FOR(i, 2, 2000000) {
        // nth fibonacci number mod m repeats at 1, 1 eventually
        if (fib(i) == 1 && fib(i+1) == 1) {
            repeatSize = i;
            break;
        }
    }

    cin >> n >> m;
    ll A[n+2]; SET(A, 0, n+2);

    F0R(i, m) {
        int start, end; ll k; cin >> start >> end >> k;
        k--; // our fib function is zero-based
        --start; --end;
        A[start] += fib(k);
        A[start + 1] += fib(k+1) - fib(k);
        A[end + 1] -= fib(k + (end-start) + 1);
        A[end + 2] -= fib(k + (end-start));
        A[start] %= mod;
        A[start + 1] %= mod;
        A[end + 1] %= mod;
        A[end + 2] %= mod;
    }

    F0R(i, n) {
        A[i] = (A[i] + (i-1 >= 0 ? A[i-1] : 0) + (i - 2 >= 0 ? A[i-2] : 0)) % mod;
        if (A[i] < 0) A[i] += mod;
    }

    F0R(i, n) {
        if (i != 0) cout << " ";
        cout << A[i];
    }
    cout << endl;

    return 0;
}