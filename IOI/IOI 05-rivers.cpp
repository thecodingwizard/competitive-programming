/*
 * Define dp[i][j][k] = min cost to ship wood from town i and its subtree, assuming the
 * closest sawmill is at town j, and we can build k new sawmills in i & i's subtree.
 *
 * The answer is then dp[0][0][k].
 *
 * The base case is simple: if i's subtree is empty, then:
 * a) if k = 0, answer is W[i]*dist[i][j]
 * b) if k != 0, answer is 0 (build a sawmill at node i)
 *
 * If i's subtree is not empty, then take the min of:
 * a) We build a sawmill at node i, then split k-1 sawmills amongst i's subtree
 * b) Do not build a sawmill at node i, then split k sawmills amongst i's subtree
 *
 * How do we split sawmills efficiently? We can use a second dp:
 * Let's say node i has n direct children.
 * dp2[i][j][k][l] = min cost to transport wood from i's [l...n] subtrees, assuming we have k
 * sawmills left to build and the nearest sawmill is at j.
 *
 * Then dp2[i][j][k][l] can transition to dp2[i][j][k - x][l + 1] where x is the # of
 * sawmills allocated to the l'th subtree of i.
 *
 * (My implementation's dp indexes are slightly different from what's written here)
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

    template<class T> void prD(const T& x) { cout << x; }
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

ll dp(int u, int p, int k);
ll dp2(int u, int idx, int p, int k);

int n, k;
ll W[101];
pll p[101];
ll d[101][101];
vector<pair<int, ll>> adj[101];

ll memo[101][101][51];
ll dp(int u, int p, int k) {
    if (memo[u][p][k] != -1) return memo[u][p][k];
    if (sz(adj[u]) == 0) return k == 0 ? W[u]*d[p][u] : 0;
    ll best = LL_INF;

    MIN(best, dp2(u, 0, p, k) + W[u]*d[u][p]);
    MIN(best, dp2(u, 0, u, k-1));

    return memo[u][p][k] = best;
}

vector<ll> memo2[101][101][51];
ll dp2(int u, int idx, int p, int k) {
    if (k < 0) return LL_INF;
    if (idx == sz(adj[u])) return 0;
    if (memo2[u][p][k].size() == 0) memo2[u][p][k].assign(sz(adj[u]), -1);
    if (memo2[u][p][k][idx] != -1) return memo2[u][p][k][idx];

    ll best = LL_INF;
    F0R(i, k+1) {
        MIN(best, dp(adj[u][idx].pA, p, i) + dp2(u, idx + 1, p, k - i));
    }
    return memo2[u][p][k][idx] = best;
}

int main() {
    setupIO();

    re(n, k);
    F0R1(i, n) {
        int w, v, d; re(w, v, d);
        W[i] = w;
        p[i] = mp(v, d);
        adj[v].pb(mp(i, d));
    }

    SET2D(d, INF, 101, 101);
    F0R(i, n+1) {
        d[i][i] = 0;
        trav(x, adj[i]) {
            d[x.pA][i] = d[i][x.pA] = x.pB;
        }
    }
    F0R(k, n+1) {
        F0R(i, n+1) {
            F0R(j, n+1) {
                if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
            }
        }
    }

    SET3D(memo, -1, 101, 101, 51);
    ps(dp(0, 0, k));

    return 0;
}
