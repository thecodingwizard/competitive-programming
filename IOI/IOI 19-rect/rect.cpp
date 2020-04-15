/*
 * Same solution as editorial
 *
 * With precomputation it's possible to check whether a rectangle is valid in O(1)
 *
 * # of rectangles is bounded by O(n^2)
 *
 * R[i][j] = first column k where A[i][j] < A[i][k]. Define similarly for the other three
 *
 * RU[i][j] = the highest row x such that for every row from x to i inclusive,
 * the columns j and R[i][j] have values that are bigger than everything in between.
 *
 * Formally, the smallest number x such that for every row k where x <= k <= i,
 * For every column c in row k where j < c < R[i][j], A[k][c] < A[k][j] and A[k][c] < A[k][R[i][j]]
 *
 * Define similarly for the other three
 *
 * Can use these values to check rectangle valid in O(1)
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

#include "rect.h"

int U[2500][2500], D[2500][2500], L[2500][2500], R[2500][2500];
int RU[2500][2500], LU[2500][2500], DL[2500][2500], UL[2500][2500];

unordered_set<ll> valid;
void check(int i1, int i2, int j1, int j2) {
    if (i2 < i1 || j2 < j1) return;
    if (!((R[i2][j1-1]-1 == j2 && RU[i2][j1-1] <= i1) || (L[i2][j2+1]+1 == j1 && LU[i2][j2+1] <= i1))) return;
    if (!((D[i1-1][j2]-1 == i2 && DL[i1-1][j2] <= j1) || (U[i2+1][j2]+1 == i1 && UL[i2+1][j2] <= j1))) return;
    valid.insert((((ll)i1*2501+i2)*2501+j1)*2501+j2);
}

long long count_rectangles(std::vector<std::vector<int> > a) {
    F0R(i, sz(a)) {
        stack<int> s;
        F0R(j, sz(a[i])) {
            while (!s.empty() && a[i][s.top()] < a[i][j]) s.pop();
            L[i][j] = s.empty() ? -1 : s.top();
            s.push(j);
        }
        while (!s.empty()) s.pop();
        F0Rd(j, sz(a[i])) {
            while (!s.empty() && a[i][s.top()] < a[i][j]) s.pop();
            R[i][j] = s.empty() ? -1 : s.top();
            s.push(j);
        }
    }
    F0R(i, sz(a[0])) {
        stack<int> s;
        F0R(j, sz(a)) {
            while (!s.empty() && a[s.top()][i] < a[j][i]) s.pop();
            U[j][i] = s.empty() ? -1 : s.top();
            s.push(j);
        }
        while (!s.empty()) s.pop();
        F0Rd(j, sz(a)) {
            while (!s.empty() && a[s.top()][i] < a[j][i]) s.pop();
            D[j][i] = s.empty() ? -1 : s.top();
            s.push(j);
        }
    }

    F0R(i, sz(a)) {
        F0R(j, sz(a[i])) {
            if (R[i][j] == -1) {
                RU[i][j] = -1;
            } else {
                if (i-1>=0 && R[i][j] == R[i-1][j]) RU[i][j] = RU[i-1][j];
                else if (i-1>=0 && j == L[i-1][R[i][j]]) RU[i][j] = LU[i-1][R[i][j]];
                else RU[i][j] = i;
            }
            if (L[i][j] == -1) {
                LU[i][j] = -1;
            } else {
                if (i-1>=0 && L[i][j] == L[i-1][j]) LU[i][j] = LU[i-1][j];
                else if (i-1>=0 && j == R[i-1][L[i][j]]) LU[i][j] = RU[i-1][L[i][j]];
                else LU[i][j] = i;
            }
        }
    }

	F0R(j, sz(a[0])) {
		F0R(i, sz(a)) {
            if (U[i][j] == -1) {
                UL[i][j] = -1;
            } else {
                if (j>0 && U[i][j] == U[i][j-1]) UL[i][j] = UL[i][j-1];
                else if (j>0 && i == D[U[i][j]][j-1]) UL[i][j] = DL[U[i][j]][j-1];
                else UL[i][j] = j;
            }
            if (D[i][j] == -1) {
                DL[i][j] = -1;
            } else {
                if (j>0 && D[i][j] == D[i][j-1]) DL[i][j] = DL[i][j-1];
                else if (j>0 && i == U[D[i][j]][j-1]) DL[i][j] = UL[D[i][j]][j-1];
                else DL[i][j] = j;
            }
        }
    }

    FOR(i, 1, sz(a)-1) {
        FOR(j, 1, sz(a[0])-1) {
			if(U[i+1][j] != -1 && L[i][j+1] != -1) check(U[i+1][j]+1, i, L[i][j+1]+1, j);
			if(U[i+1][j] != -1 && R[i][j-1] != -1) check(U[i+1][j]+1, i, j, R[i][j-1]-1);
			if(D[i-1][j] != -1 && L[i][j+1] != -1) check(i, D[i-1][j]-1, L[i][j+1]+1, j);
			if(D[i-1][j] != -1 && R[i][j-1] != -1) check(i, D[i-1][j]-1, j, R[i][j-1]-1);
			if(D[i-1][j] != -1 && R[D[i-1][j]-1][j-1] != -1) check(i, D[i-1][j]-1, j, R[D[i-1][j]-1][j-1]-1);
			if(D[i-1][j] != -1 && L[D[i-1][j]-1][j+1] != -1) check(i, D[i-1][j]-1, L[D[i-1][j]-1][j+1]+1, j);
        }
    }

	return sz(valid);
}
