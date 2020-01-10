/*
 * Same as editorial, Ternary Partitioning with Randomized Pivot
 * 
 * First, pick two random indexes a and b. Assume you know for sure that a < b. You don't actually know for sure,
 * but if it was actually a > b you will just end up sorting the array in reverse order and you'll still get the same
 * answer for the median.
 * 
 * Next, run Med3(a, b, i) for all i that's not a, b. Depending on which value is the median, you know that either:
 * 1. i < a < b
 * 2. a < i < b
 * 3. a < b < i
 * 
 * From this, we can "partition" the array into three parts, one that's before a, one that's between a and b,
 * and one that's after b.
 * 
 * We figure out which partition contains the median and recursively do the same thing on the smaller array
 * (pick two random indexes to act as the pivot. Note that you can figure out their order by comparing to a & b).
 * 
 * If the indexes are chosen randomly then this algorithm will almost always pass within 7777 calls.
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

#include "device.h"

int N;

vi solve(vi &numbers, int lowerPivot, int upperPivot, int L, int R) {
    if (L > N/2 || R < N/2) {
        vi x = numbers;
        x.pb(lowerPivot); x.pb(upperPivot);
        return x;
    }

    vi left, middle, right;

    trav(x, numbers) {
        int median = Med3(lowerPivot, upperPivot, x);
        if (median == x) middle.pb(x);
        else if (median == lowerPivot) left.pb(x);
        else right.pb(x);
    }

    vi sLeft, sMiddle, sRight;

    if (sz(left) >= 2) {
        int a = rand() % left.size(), b = rand() % left.size();
        while (a == b) b = rand() % left.size();
        int A = left[a], B = left[b];
        vi newLeft; trav(x, left) if (x != A && x != B) newLeft.pb(x);
        int med = Med3(A, B, lowerPivot);
        int lower = med == A ? B : A;
        sLeft = solve(newLeft, lower, med, L, L+sz(left));
    } else {
        sLeft = left;
    }
    if (sz(middle) >= 2) {
        int a = rand() % middle.size(), b = rand() % middle.size();
        while (a == b) b = rand() % middle.size();
        int A = middle[a], B = middle[b];
        vi newMiddle; trav(x, middle) if (x != A && x != B) newMiddle.pb(x);
        int med = Med3(A, B, upperPivot);
        int lower = med == A ? B : A;
        sMiddle = solve(newMiddle, lower, med, L + sz(left) + 1, L + sz(left) + 1 + sz(middle));
    } else {
        sMiddle = middle;
    }
    if (sz(right) >= 2) {
        int a = rand() % right.size(), b = rand() % right.size();
        while (a == b) b = rand() % right.size();
        int A = right[a], B = right[b];
        vi newRight; trav(x, right) if (x != A && x != B) newRight.pb(x);
        int med = Med3(A, B, upperPivot);
        int upper = med == A ? B : A;
        sRight = solve(newRight, med, upper, L + sz(left) + sz(middle) + 2, R);
    } else {
        sRight = right;
    }

    vi sorted;
    trav(x, sLeft) sorted.pb(x);
    sorted.pb(lowerPivot);
    trav(x, sMiddle) sorted.pb(x);
    sorted.pb(upperPivot);
    trav(x, sRight) sorted.pb(x);
    return sorted;
}

int Median(int n) {
    N = n;
    srand(time(NULL));

    int a = rand() % n + 1, b = rand() % n + 1;
    while (b == a) b = rand() % n + 1;

    vi nums;
    F0R1(i, n) {
        if (i != a && i != b) nums.pb(i);
    }

    vi sorted = solve(nums, a, b, 0, n-1);
    return sorted[sorted.size()/2];
}