/*
 * We are basically going to visit all the farms once, and each time we do we will have to traverse through at least
 * one edge in that farm.
 *
 * Let's fix the order in which we visit the farms. Our answer is just that number times (n-1)!/2, because we
 * can visit the farms in any order, but we divide by 2 because it doesn't matter which direction we visit the farms in.
 *
 * Define paths[i][j] to be the list of path lengths on the i'th farm where the length equals j. If j = Y, then
 * paths[i][j] is the list of paths where the path length is >= Y. We can calculate this in O(n^2) time.
 *
 * Define pathsSum[i][j] to be the sum of the values of paths[i][j], and define pathsCt[i][j] = sz(paths[i][j]).
 * Define pathLengths[i] to contain the list of j values where pathsCt[i][j] != 0. this helps us speed up our DP transitions.
 *
 * We can solve this problem by DP. Define dp[i][j] = the sum of valid track lengths from the i'th farm to the
 * last farm where the track length must be at least j. Define dp2[i][j] = the number of valid tracks from
 * the i'th farm to the last farm where track length is at least j.
 *
 * Let's look at dp2[i][j] first: The base case is when i is the K'th farm (zero indexed, so it's an imaginary farm).
 * dp2[k][j] = 0 if j != 0, and dp2[k][0] = 1.
 * For the recurrence, we basically have to figure out which path we want to take in the i'th farm. If we are taking
 * a path of length a, then dp2[i][j] += dp2[i+1][max(j-a - X, 0)] (the - X comes from the length of the path we're adding).
 * We can do this quickly with the path info we calculated earlier. For every value j2 in pathLengths[i],
 * dp2[i][j] += dp2[i+1][j - j2 - X]*pathsCt[i][j2].
 *
 * dp[i][j] base case is: if i >= k, then 0.
 * Recurrence: Similar to dp2, except this time we use dp2 to help us compute the transition. The idea is the same:
 * we try out every path in farm i.
 * For every value j2 in pathLengths[i], dp[i][j] += dp[i+1][j - j2 - X]*pathsCt[i][j2] + dp2[i+1][j - j2 - X]*pathsSum[i][j2]
 */

//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define PI acos(-1.0)
// #define MOD (int)(2e+9+11)
#define MOD (int)(1e+9+7)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;

#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize
#define SORT(vec) sort(all(vec))
#define RSORT(vec) sort(vec.rbegin(),vec.rend())

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

// @formatter:off
// Source: Benq (https://github.com/bqi343/USACO) [Modified]
namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    template<class T> void reA(T A[], int sz);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }

    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.pA,p.pB); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    template<class T> void reA(T A[], int sz) { F0R(i, sz) re(A[i]); }

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
}
using namespace input;

namespace output {
    template<class T1, class T2> void prD(const pair<T1,T2>& x);
    template<class T, size_t SZ> void prD(const array<T,SZ>& x);
    template<class T> void prD(const vector<T>& x);
    template<class T> void prD(const set<T>& x);
    template<class T1, class T2> void prD(const map<T1,T2>& x);

    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void prD(const T& x) { cout << x; cout.flush(); }
    template<class Arg, class... Args> void prD(const Arg& first, const Args&... rest) {
        prD(first); prD(rest...);
    }

    template<class T1, class T2> void prD(const pair<T1,T2>& x) {
        prD("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prDContain(const T& x) {
        prD("{");
        bool fst = 1; for (const auto& a: x) prD(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        prD("}");
    }
    template<class T, size_t SZ> void prD(const array<T,SZ>& x) { prDContain(x); }
    template<class T> void prD(const vector<T>& x) { prDContain(x); }
    template<class T> void prD(const set<T>& x) { prDContain(x); }
    template<class T1, class T2> void prD(const map<T1,T2>& x) { prDContain(x); }

    void psD() { prD("\n"); }
    template<class Arg> void psD(const Arg& first) {
        prD(first); psD(); // no space at end of line
    }
    template<class Arg, class... Args> void psD(const Arg& first, const Args&... rest) {
        prD(first," "); psD(rest...); // print w/ spaces
    }


    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr(x.pA, " ", x.pB);
    }
    template<class T> void prContain(const T& x) {
        bool fst = 1; for (const auto& a: x) pr(!fst?" ":"",a), fst = 0; // const needed for vector<bool>
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}
using namespace output;
// @formatter:on

/* ============================ */

#define MAXN 1500
#define MAXY 2500
#define mod 1000000007

int n, m, x, y;
vii adj[MAXN];
int numFarms = 0;
vi paths[MAXN][MAXY+10];
ll pathsSum[MAXN][MAXY+10];
set<int> pathLengths[MAXN];
bool visited[MAXN];
int farmNumber[MAXN];
ll dp2(int farmNum, int minLength);

void dfs(int u, int p, int num) {
    visited[u] = true;
    farmNumber[u] = num;
    trav(v, adj[u]) {
        if (v.pA != p) dfs(v.pA, u, num);
    }
}

void dfs2(int u, int p, int dist) {
    trav(v, adj[u]) {
        if (v.pA != p) {
            int onePath = dist + v.pB;
            int num = farmNumber[u];
            if (onePath >= y) {
                paths[num][y].pb(onePath);
                pathsSum[num][y] = (pathsSum[num][y] + onePath) % mod;
                pathLengths[num].insert(y);
            } else {
                paths[num][onePath].pb(onePath);
                pathsSum[num][onePath] = (pathsSum[num][onePath] + onePath) % mod;
                pathLengths[num].insert(onePath);
            }
            dfs2(v.pA, u, onePath);
        }
    }
}

ll memo[MAXN][MAXY+10], memo2[MAXN][MAXY+10];
ll dp(int farmNum, int minLength) {
    if (minLength < 0) minLength = 0;
    if (farmNum >= numFarms) {
        return 0;
    }
    if (memo[farmNum][minLength] != -1) return memo[farmNum][minLength];
    ll ans = 0;
    trav(i, pathLengths[farmNum]) {
        ll psum = pathsSum[farmNum][i], pct = sz(paths[farmNum][i]);
        psum = (psum + x*pct) % mod;
        ans = (ans + dp(farmNum+1, minLength - i - x)*pct + dp2(farmNum+1, minLength - i - x)*psum) % mod;
    }
    return memo[farmNum][minLength] = ans;
}

ll dp2(int farmNum, int minLength) {
    if (minLength < 0) minLength = 0;
    if (farmNum >= numFarms) {
        if (minLength == 0) return 1;
        return 0;
    }
    if (memo2[farmNum][minLength] != -1) return memo2[farmNum][minLength];
    ll ans = 0;
    trav(i, pathLengths[farmNum]) {
        int pct = sz(paths[farmNum][i]);
        ans = (ans + dp2(farmNum+1, minLength - i - x)*pct) % mod;
    }
    return memo2[farmNum][minLength] = ans;
}

int main() {
    setupIO("mooriokart");

    re(n, m, x, y);
    F0R(i, m) {
        int a, b, d; re(a, b, d);
        adj[--a].pb({--b, d});
        adj[b].pb({a, d});
    }

    SET2D(pathsSum, 0, MAXN, MAXY+10);
    SET(visited, false, n);
    F0R(i, n) {
        if (!visited[i]) {
            dfs(i, i, numFarms++);
        }
        dfs2(i, i, 0);
    }

    SET2D(memo, -1, MAXN, MAXY+10);
    SET2D(memo2, -1, MAXN, MAXY+10);
    ll ans = dp(0, y)*500000004%mod; // divide by 2
    FOR(i, 2, numFarms) {
        ans = ans * i % mod;
    }
    ps(ans);

    return 0;
}