/*
 * First note that we can split up the problem into X- and Y- components and solve them individually.
 *
 * Then our problem is simpler: Given a list of 1D vectors, support the following queries:
 * 1. Move pointer up one
 * 2. Move pointer down one
 * 3. Change the vector at the pointer
 * 4. Count number of vectors that cross x = 0
 *
 * Let's consider a simpler problem where the pointer can't move up/down, and we can only change the first vector.
 *
 * If we draw out a number line and a list of vectors, observe that changing the first vector is
 * similar to "moving" the line x = 0 and then counting the number of vectors it intersects.
 *
 * We can  create a list of "delta" values for every x location. When the first vector changes,
 * we imagine "moving" the line x = 0. Every time we reach a delta value, then we update the number of
 * vectors that the line intersects.
 *
 * For example, if the line is currently at x = 0 and there's a vector with head at x = 1 and tail at x = -1,
 * then delta[1] = -1 and delta[-1] = -1. The number of intersections we have right now is 1.
 *
 * If we "move" the line x = 0 to x = 2 (by updating the first vector), then we will hit delta[1], so we will subtract
 * 1 from our answer to get 0 intersections. We then do delta[1] *= -1 because the next time the "intersection line" x = 2
 * crosses x = 1, then we have to add 1 as there is one intersection.
 *
 * With some offset stuff and math, we can handle queries 1) and 2).
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

class Solve {
private:
    map<int, int> delta;
    vii A;
    int offset[100000];
    int curOffset = 0;
    int ans = 0;
    int curLine = 0;

    void add(int i) {
        int a = A[i].pA, b = A[i].pB;
        if (b > 0) {
            if (a >= curOffset) {
                delta[a]++;
                delta[a+b]--;
            } else if (a+b > curOffset) {
                delta[a]--;
                delta[a+b]--;
            } else {
                delta[a+b]++;
                delta[a]--;
            }
        } else {
            if (a <= curOffset) {
                delta[a]++;
                delta[a+b]--;
            } else if (a+b < curOffset) {
                delta[a]--;
                delta[a+b]--;
            } else {
                delta[a]--;
                delta[a+b]++;
            }
        }
    }

    void remove(int i) {
        int a = A[i].pA, b = A[i].pB;
        if (b > 0) {
            if (a >= curOffset) {
                delta[a]--;
                delta[a+b]++;
            } else if (a+b > curOffset) {
                delta[a]++;
                delta[a+b]++;
            } else {
                delta[a+b]--;
                delta[a]++;
            }
        } else {
            if (a <= curOffset) {
                delta[a]--;
                delta[a+b]++;
            } else if (a+b < curOffset) {
                delta[a]++;
                delta[a+b]++;
            } else {
                delta[a]++;
                delta[a+b]--;
            }
        }
    }

public:
    Solve(const vii &input) {
        A = input;
        SET(offset, 0, 100000);
        F0R(i, sz(A)) {
            if (A[i].pA > 0 && A[i].pA + A[i].pB < 0) ans++;
            if (A[i].pA < 0 && A[i].pA + A[i].pB > 0) ans++;
        }
        FOR(i, 1, sz(A)) {
            add(i);
        }
    }

    // move line back
    void B() {
        if (curLine == 0) return;
        int offsetDiff = curOffset - offset[curLine];
        A[curLine].pA += offsetDiff;
        add(curLine);
        curLine--;
    }

    // move line forward
    void F() {
        if (curLine == sz(A)-1) return;
        offset[++curLine] = curOffset;
        remove(curLine);
    }

    // change line
    void change(int newVal) {
        int cng = A[curLine].pB - newVal;
        int newOffset = curOffset + cng;
        int a = min(curOffset, newOffset), b = max(curOffset, newOffset);
        auto it = delta.lb(a);
        while (it != delta.end() && it->pA <= b) {
            ans += delta[it->pA];
            delta[it->pA] *= -1;
            it++;
        }
        if (A[curLine].pA > offset[curLine] && A[curLine].pA + A[curLine].pB < offset[curLine]) ans--;
        if (A[curLine].pA < offset[curLine] && A[curLine].pA + A[curLine].pB > offset[curLine]) ans--;
        curOffset = newOffset;
        A[curLine].pB = newVal;
        if (A[curLine].pA > offset[curLine] && A[curLine].pA + A[curLine].pB < offset[curLine]) ans++;
        if (A[curLine].pA < offset[curLine] && A[curLine].pA + A[curLine].pB > offset[curLine]) ans++;
    }

    int qry() {
        return ans;
    }
};

int main() {
    setupIO();

    int n; re(n);

    vector<ii> X, Y;
    int x = 1, y = 1;
    F0R(i, n) {
        int a, b; re(a, b);
        X.eb(x, a);
        Y.eb(y, b);
        x += a; y += b;
    }

    Solve xx(X), yy(Y);

    int m; re(m);
    F0R(i, m) {
        char c; re(c);
        if (c == 'B') {
            xx.B(); yy.B();
        } else if (c == 'F') {
            xx.F(); yy.F();
        } else if (c == 'C') {
            re(x, y);
            xx.change(x); yy.change(y);
        } else {
            ps(xx.qry() + yy.qry());
        }
    }

    return 0;
}
