/*
 * Real messy implementation. I think editorial has a far cleaner implementation.
 *
 * Idea is same as editorial, recognize that each room + its border must be of one of the following:
 * + +
 *  ..
 * +.+
 *
 * +.+
 *  .
 * +.+
 *
 * etc. Then DP
 *
 * Input data:

17 15
+-+-+-+-+-+-+-+
|             |
+ + + + + + + +
|X  |   |     |
+ + + + + + + +
|   |   |  X  |
+-+ + + + + + +
|       |     |
+ + + +-+-+-+-+
|            X|
+ + +-+-+-+-+ +
|             |
+ + + + + + + +
|  X|         |
+ + + + + + + +
|   |         |
+-+-+-+-+-+-+-+

15 15
+-+-+-+-+-+-+-+
|X|           |
+ + + +-+ + + +
| |   |X|  X  |
+ + + + + + +-+
|     | |   |X|
+ +-+-+ + + + +
|       |   | |
+-+-+ + + +-+ +
|     |     | |
+ + + +-+-+ + +
|     |X  | | |
+ +-+-+ + + + +
|    X|       |
+-+-+-+-+-+-+-+

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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

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

/* ============================ */

int r, c;
char A[25][80];

int memo[(1 << 12)][12][40][2];
// 0 = center
// 1 = right
// 2 = bottom
// 3 = center, right, bottom
// 4 = none
// 5 = center, right
// 6 = center, bottom
int par[(1 << 12)][12][40][2];

int dp(int mask, int row, int col, int topConnect) {
    if (row >= r/2) {
        if (topConnect) return INF;
        return dp(mask, 0, col + 1, 0);
    }
    if (col >= c/2) {
        return 0;
    }
    if (memo[mask][row][col][topConnect] != -1) return memo[mask][row][col][topConnect];
    bool cntr = A[row*2+1][col*2+1] == 'X';
    bool tBlock = A[row*2][col*2+1] != ' ';
    bool lBlock = A[row*2+1][col*2] != ' ';
    bool rBlock = A[row*2+1][col*2+2] !=  ' ';
    bool bBlock = A[row*2+2][col*2+1] != ' ';
    bool left = (mask & (1 << row)) != 0;
    int off = mask & ~(1 << row);
    int on = mask | (1 << row);
    if (cntr) {
        if (topConnect) {
            if (tBlock || left) return memo[mask][row][col][topConnect] = INF;
            par[mask][row][col][topConnect] = 4;
            return memo[mask][row][col][topConnect] = dp(off, row + 1, col, 0);
        }
        if (left) {
            if (lBlock) return memo[mask][row][col][topConnect] = INF;
            par[mask][row][col][topConnect] = 4;
            return memo[mask][row][col][topConnect] = dp(off, row + 1, col, 0);
        }
        int x = (rBlock ? INF : dp(on, row + 1, col, 0) + 1), y = (bBlock ? INF : dp(off, row + 1, col, 1) + 1);
        if (x < y) par[mask][row][col][topConnect] = 1;
        else par[mask][row][col][topConnect] = 2;
        return memo[mask][row][col][topConnect] = min(x, y);
    }
    if (topConnect) {
        if (tBlock) return memo[mask][row][col][topConnect] = INF;
        if (left) {
            if (lBlock) return memo[mask][row][col][topConnect] = INF;
            par[mask][row][col][topConnect] = 0;
            return memo[mask][row][col][topConnect] = dp(off, row + 1, col, 0) + 1;
        }
        // right, bottom
        int best = INF;
        if (!rBlock) {
            par[mask][row][col][topConnect] = 5;
            MIN(best, dp(on, row + 1, col, 0) + 2);
        }
        if (!bBlock) {
            if (best > dp(off, row + 1, col, 1) + 2) {
                best = dp(off, row + 1, col, 1) + 2;
                par[mask][row][col][topConnect] = 6;
            }
        }
        return memo[mask][row][col][topConnect] = best;
    }
    if (left) {
        if (lBlock) return memo[mask][row][col][topConnect] = INF;
        // right, bottom
        int best = INF;
        if (!rBlock) {
            par[mask][row][col][topConnect] = 5;
            MIN(best, dp(on, row + 1, col, 0) + 2);
        }
        if (!bBlock) {
            if (best > dp(off, row + 1, col, 1) + 2) {
                best = dp(off, row + 1, col, 1) + 2;
                par[mask][row][col][topConnect] = 6;
            }
        }
        return memo[mask][row][col][topConnect] = best;
    }
    if (!rBlock && !bBlock) {
        int xx = dp(on, row + 1, col, 1) + 3, yy = dp(off, row + 1, col, 0);
        if (xx < yy) {
            par[mask][row][col][topConnect] = 3;
        } else {
            par[mask][row][col][topConnect] = 4;
        }
        return memo[mask][row][col][topConnect] = min(xx, yy);
    }
    par[mask][row][col][topConnect] = 4;
    return memo[mask][row][col][topConnect] = min(INF, dp(off, row + 1, col, 0));
}

int main() {
//    setupIO();

    cin >> r >> c; cin.ignore();
    F0R(i, r) {
        gets(A[i]);
    }
    int xx = 0; F0R(i, r) F0R(j, c) if (A[i][j] == 'X') xx++;
    SET4D(memo, -1, (1 << 12), 12, 40, 2);
    ps(dp(0, 0, 0, 0) + xx/2);
    assert(dp(0, 0, 0, 0) < INF);

    int mask = 0, row = 0, col = 0, topConnect = 0;
    while (col < c/2) {
        int p = par[mask][row][col][topConnect];
        int off = mask & ~(1 << row);
        int on = mask | (1 << row);
        // 0 = center
        // 1 = right
        // 2 = bottom
        // 3 = center, right, bottom
        // 4 = none
        // 5 = center, right
        // 6 = center, bottom
        if (p == 0) {
            A[row*2+1][col*2+1] = '.';
            mask = off;
            topConnect = 0;
        } else if (p == 1) {
            A[row*2+1][col*2+2] = '.';
            mask = on;
            topConnect = false;
        } else if (p == 2) {
            A[row*2+2][col*2+1] = '.';
            mask = off;
            topConnect = true;
        } else if (p == 3) {
            A[row*2+1][col*2+1] = A[row*2+2][col*2+1] = A[row*2+1][col*2+2] = '.';
            mask = on;
            topConnect = true;
        } else if (p == 4) {
            mask = off;
            topConnect = false;
        } else if (p == 5) {
            A[row*2+1][col*2+1] = A[row*2+1][col*2+2] = '.';
            mask = on;
            topConnect = false;
        } else if (p == 6) {
            A[row*2+1][col*2+1] = A[row*2+2][col*2+1] = '.';
            mask = off;
            topConnect = true;
        } else {
            assert(false);
        }
        row++;
        if (row >= r/2) {
            row = 0;
            col++;
        }
    }
    F0R(i, r) {
        F0R(j, c) pr(A[i][j]);
        ps();
    }

    return 0;
}