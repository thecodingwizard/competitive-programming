/*
 * This problem can be solved greedily with dp.
 *
 * Let's examine the very last plough of an optimal solution. It will either be a horizontal plough,
 * a vertical plough, or a plough of a single square. We will handle these cases separately.
 *
 * If the last plough is a single square, that means that we must have done m + n - 2 ploughs before
 * reaching the last square. Hence, we can set an upper bound for the answer as m + n - 1 ploughs.
 * We know that a solution exists, so to get m + n - 1, we just greedily plough whichever side we can.
 *
 * If the last plough is a horizontal plough, then we know that we must have done exactly n - 1 horizontal
 * ploughs and some number of vertical ploughs to reach this state. There is no way to avoid doing n - 1 horizontal
 * ploughs. Hence, we can greedily do horizontal ploughs: If we can plough the top/bottom row, we just greedily do so.
 *
 * However, what if we can't? Then we can use DP to solve this problem. Our state will be (a, b) ==> we have
 * done vertical ploughs from 0...a and from b...m - 1, and we have done as many greedy horizontal ploughs
 * as we can. We can transition to (a + 1, b) or (a, b - 1) by ploughing either the left/right side of the field.
 *
 * We then apply this to the case if the last plough is a vertical plough.
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

int k, m, n;
ll PS[2000][2000];

ll gPS(int a, int b) {
    if (a < 0 || b < 0) return 0;
    return PS[a][b];
}

ll getVert(int x, int y, int a) {
    return gPS(y, a) - gPS(x - 1, a) - gPS(y, a - 1) + gPS(x - 1, a - 1);
}
ll getHoriz(int a, int b, int x) {
    return gPS(x, b) - gPS(x - 1, b) - gPS(x, a - 1) + gPS(x - 1, a - 1);
}

int memo[2000][2000];

int dp(int type, int a, int b, int c, int d) {
    if (c > d) return 0;
    if (memo[a][b] != -1) return memo[a][b];
    if (type == 0) {
        if (getVert(a, b, c) <= k) {
            return dp(type, a, b, c + 1, d);
        }
        if (getVert(a, b, d) <= k) {
            return dp(type, a, b, c, d - 1);
        }
        int bestOpt = INF;

        if (getHoriz(c, d, a) <= k) MIN(bestOpt, dp(type, a + 1, b, c, d) + 1);
        if (getHoriz(c, d, b) <= k) MIN(bestOpt, dp(type, a, b - 1, c, d) + 1);

        return memo[a][b] = bestOpt;
    } else {
        if (getHoriz(a, b, c) <= k) {
            return dp(type, a, b, c + 1, d);
        }
        if (getHoriz(a, b, d) <= k) {
            return dp(type, a, b, c, d - 1);
        }
        int bestOpt = INF;

        if (getVert(c, d, a) <= k) MIN(bestOpt, dp(type, a + 1, b, c, d) + 1);
        if (getVert(c, d, b) <= k) MIN(bestOpt, dp(type, a, b - 1, c, d) + 1);

        return memo[a][b] = bestOpt;
    }
}

int main() {
    setupIO();

    re(k, m, n);
    F0R(i, n) reA(PS[i], m);

    F0R(i, n) {
        F0R(j, m) {
            PS[i][j] = (i > 0 ? PS[i - 1][j] : 0) + (j > 0 ? PS[i][j - 1] : 0) - (i > 0 && j > 0 ? PS[i-1][j-1] : 0) + PS[i][j];
        }
    }

    int best = m + n - 1;

    SET2D(memo, -1, 2000, 2000);
    // vertical
    MIN(best, dp(0, 0, n - 1, 0, m - 1) + m);
    SET2D(memo, -1, 2000, 2000);
    // horizontal
    MIN(best, dp(1, 0, m - 1, 0, n - 1) + n);

    ps(best);

    return 0;
}