/*
 * XOR all the diagonals in both directions:
 * - (0, 0); (0, 1), (1, 0); (0, 2), (1, 1), (2, 0); etc
 * - (H-1, 0); (H-2, 0), (H-1, 1); (H-3, 0), (H-2, 1), (H-1, 2); etc
 *
 * Note that at least one of the diagonals will have two 1's, representing the two diagonals that the black
 * squares are located on. Let's say that the distance between these two 1's is `a` and `b` respectively
 * for the two sets of diagonals. The distance between the two black squares is max(a, b).
 *
 * Therefore, the distance between the two black squares is exactly K if max(a, b) = K. How to calculate max(a, b)?
 *
 * We can split this into two parts: first, either a or b must be at least K. second, both a and b have to be at most K.
 *
 * Let's do a "prefix xor" on the diagonals. If the XOR of diagonals was: 0 0 1 0 0 0 1 0 0 (k = 4 in this example)
 * we will XOR each number w/ the previous number to get 0 0 1 1 1 1 0 0 0.
 *
 * To check the first condition, that either a or b must be at least K, we will do the following for each diagonal direction:
 * - add_or(add_and(i, i+k-1) for all valid i)
 * if result of add_or is true for either diagonal direction, then first condition met.
 *
 * To check the second condition, that a and b must be at most K, we can basically check to see if either a or b is >= K+1:
 * - add_or(add_and(i, i+k) for all valid i)
 * if result of add_or is true for _either_ diagonal, then the second condition is _not_ met.
 *
 * Therefore our complete condition is:
 * add_and({
 *     add_or({
 *         add_or(condition_1_diagonal_1),
 *         add_or(condition_1_diagonal_2),
 *     }),
 *     add_not(add_or(condition_2_diagonal_1)),
 *     add_not(add_or(condition_2_diagonal_2))
 * });
 */

//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

#include <utility>

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

#include "vision.h"

void construct_network(int H, int W, int K) {
    if (H >= 2 && W >= 2) { // General case code
        vi diagonal1;
        F0Rd(i, H) {
            vi diag;
            for (int a = i, b = 0; a < H && b < W; a++, b++) {
                diag.pb(a*W+b);
            }
            if (i == H-1) diagonal1.pb(add_xor(diag));
            else diagonal1.pb(add_xor({diagonal1.back(), add_xor(diag)}));
        }
        FOR(j, 1, W) {
            vi diag;
            for (int a = 0, b = j; a < H && b < W; a++, b++) {
                diag.pb(a*W+b);
            }
            diagonal1.pb(add_xor({diagonal1.back(), add_xor(diag)}));
        }
        vi diagonal2;
        F0R(j, W) {
            vi diag;
            for (int a = 0, b = j; a < H && b >= 0; a++, b--) {
                diag.pb(a*W+b);
            }
            if (j == 0) diagonal2.pb(add_xor(diag));
            else diagonal2.pb(add_xor({diagonal2.back(), add_xor(diag)}));
        }
        FOR(i, 1, H) {
            vi diag;
            for (int a = i, b = W - 1; a < H && b >= 0; a++, b--) {
                diag.pb(a*W+b);
            }
            diagonal2.pb(add_xor({diagonal2.back(), add_xor(diag)}));
        }
        // If number of 1s > K, fail
        vi diag1check;
        F0R(i, sz(diagonal1) - K) {
            diag1check.pb(add_and({diagonal1[i], diagonal1[i + K]}));
        }
        vi diag2check;
        F0R(i, sz(diagonal2) - K) {
            diag2check.pb(add_and({diagonal2[i], diagonal2[i + K]}));
        }
        // If number of 1s == K, good
        vi diag1check2;
        F0R(i, sz(diagonal1) - (K-1)) {
            diag1check2.pb(add_and({diagonal1[i], diagonal1[i + K - 1]}));
        }
        vi diag2check2;
        F0R(i, sz(diagonal2) - (K-1)) {
            diag2check2.pb(add_and({diagonal2[i], diagonal2[i + K - 1]}));
        }
        add_and({
            add_or({
                add_or(diag1check2),
                add_or(diag2check2),
            }),
            add_not(add_or(diag1check)),
            add_not(add_or(diag2check))
        });
    } else if (H >= 2 && W >= 2 && K == 1) { // Code to solve 7th case
        // Step 1: XOR all rows
        vi xor_rows;
        F0R(i, H) {
            vi list;
            F0R(j, W) {
                int k = i*W+j;
                list.pb(k);
            }
            xor_rows.pb(add_xor(list));
        }
        int inSameRow = add_not(add_or(xor_rows));
        // Step 2: XOR all cols
        vi xor_cols;
        F0R(i, W) {
            vi list;
            F0R(j, H) {
                int k = j*W+i;
                list.pb(k);
            }
            xor_cols.pb(add_xor(list));
        }
        int inSameCol = add_not(add_or(xor_cols));
        // Step 3: AND adjacent rows
        vi and_adjRows;
        F0R(i, H-1) {
            and_adjRows.pb(add_and({xor_rows[i], xor_rows[i+1]}));
        }
        int isAdjRow = add_or(and_adjRows);
        // Step 4: AND adjacent cols
        vi and_adjCols;
        F0R(i, W-1) {
            and_adjCols.pb(add_and({xor_cols[i], xor_cols[i+1]}));
        }
        int isAdjCol = add_or(and_adjCols);
        add_or({add_and({isAdjRow, inSameCol}), add_and({isAdjCol, inSameRow})});
    } else { // Brute force code
        vector<ii> opts;
        F0R(i, H) {
            F0R(j, W) {
                F0R(k, H) {
                    F0R(l, W) {
                        if (abs(k - i) + abs(l - j) == K) {
                            opts.pb({i * W + j, k * W + l});
                        }
                    }
                }
            }
        }
        vi final;
        trav(x, opts) {
            final.pb(add_and({x.pA, x.pB}));
        }
        add_or(final);
    }
}
