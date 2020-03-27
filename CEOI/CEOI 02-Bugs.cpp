/*
 * Note that because the chip sizes are 2x3 and 3x2, then if we are trying to add chips to the ith column,
 * we only need to know the holes in the ith column, i+1st column, and the i+2nd column
 *
 * This suggests we can use DP. Define dp(i, j) = # of chips you can put from the ith column to the n-1st column
 * where j represents the locations of the holes in the ith column and the i+1st column (the i+2nd column
 * will always be the same because you can't change the i+2nd column from the i-1 column). There are only 20 such
 * locations in two columns, so j can just be a bitmask of size 20. Also note that not all bitmasks will be used
 * so it will probably run in time (in fact # of values of j is under 3^10). To transition, just brute force putting
 * chips on the ith column and transition to dp(i+1, new_j).
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
#define MOD2 (int)(2e+9+11)
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

int n, m, k;
bool A[150][10];
bool B[150][10];

int dp(int idx, int mask);

int gen_mask(int n) {
    int mask = 0;
    F0R(i, 2) {
        F0R(j, m) {
            if (B[n+i][j]) mask |= (1 << (i*m+j));
        }
    }
    return mask;
}

int dpHelper(int nIdx, int mask, int mIdx) {
    if (mIdx + 1 >= m) return dp(nIdx + 1, gen_mask(nIdx+1));
    int best = dpHelper(nIdx, mask, mIdx + 1);
    // try putting one vertically
    bool canPutVertical = true;
    if (mIdx + 2 >= m) canPutVertical = false;
    else {
        F0R(i, 2) {
            F0R(j, 3) {
                if (B[nIdx+i][mIdx + j]) canPutVertical = false;
            }
        }
    }
    if (canPutVertical) {
        F0R(i, 2) {
            F0R(j, 3) {
                B[nIdx+i][mIdx + j] = true;
            }
        }
        best = max(best, 1 + dpHelper(nIdx, mask, mIdx + 2));
        F0R(i, 2) {
            F0R(j, 3) {
                B[nIdx+i][mIdx + j] = false;
            }
        }
    }
    // try putting one horizontally
    bool canPutHorizontal = true;
    if (nIdx + 2 >= n || mIdx + 1 >= m) canPutHorizontal = false;
    else {
        F0R(i, 3) {
            F0R(j, 2) {
                if (B[nIdx + i][mIdx + j]) canPutHorizontal = false;
            }
        }
    }
    if (canPutHorizontal) {
        F0R(i, 3) {
            F0R(j, 2) {
                B[nIdx+i][mIdx + j] = true;
            }
        }
        best = max(best, 1 + dpHelper(nIdx, mask, mIdx + 1));
        F0R(i, 3) {
            F0R(j, 2) {
                B[nIdx+i][mIdx + j] = false;
            }
        }
    }

    return best;
}
int serialize(int idx, int mask) {
    return idx*(1 << 20)+mask;
}
unordered_map<int, int> memo;
int dp(int idx, int mask) {
    if (idx + 1 >= n) return 0;
    if (memo.count(serialize(idx, mask)) != 0) return memo[serialize(idx, mask)];
    int best = dp(idx + 1, gen_mask(idx+1));
    best = max(best, dpHelper(idx, mask, 0));
    return memo[serialize(idx, mask)] = best;
}

void solve() {
    re(n, m, k);
    SET2D(A, false, n, m);
    SET2D(B, false, n, m);
    memo.clear();
    F0R(i, k) {
        int a, b; re(a, b);
        A[a-1][b-1] = true;
        B[a-1][b-1] = true;
    }
    int mask = gen_mask(0);
    ps(dp(0, mask));
}

int main() {
    setupIO();

    int d; re(d);
    F0R(i, d) {
        solve();
    }

    return 0;
}