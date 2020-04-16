/*
 * 2d seg tree with lazy propagation is difficult, but luckily not necessary since values
 * can only ever get bigger.
 *
 * For each node on the first dimension, store two 1d lazy segment trees. The first one stores values
 * that exist across its entire range; the second one stores the greatest value that appears anywhere
 * inside its range, not necessarily the entire range.
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

int D, S;

struct SegTree {
    vi st, lazy;
    int n;
    void init(int _n) {
        n = _n;
        st.assign(2049,0);
        lazy.assign(2049,-1);
    }
    int qry(int p, int i, int j, int L, int R) {
        if (i > R || j < L) return 0;
        if (lazy[p] != -1) {
            if (i != j) {
                lazy[p << 1] = max(lazy[p << 1], lazy[p]);
                st[p << 1] = max(lazy[p], st[p << 1]);
                lazy[(p << 1) + 1] = max(lazy[(p << 1) + 1], lazy[p]);
                st[(p << 1) + 1] = max(lazy[p], st[(p << 1)+1]);
            }
            lazy[p] = -1;
        }
        if (L <= i && j <= R) return st[p];
        return max(qry(p << 1, i, (i+j)/2, L, R), qry((p << 1) + 1, (i+j)/2+1, j, L, R));
    }
    int qry(int i, int j) {
        return qry(1, 0, n-1, i, j);
    }
    void upd(int p, int i, int j, int L, int R, int v) {
        if (i > R || j < L) return;
        if (L <= i && j <= R) {
            lazy[p] = max(lazy[p], v);
            st[p] = max(st[p], v);
        } else {
            upd(p << 1, i, (i+j)/2, L, R, v);
            upd((p << 1) + 1, (i+j)/2+1, j, L, R, v);
            st[p] = max(max(st[p << 1], st[(p << 1) + 1]), st[p]);
        }
    }
    void upd(int i, int j, int v) {
        return upd(1, 0, n-1, i, j, v);
    }
};

SegTree st[2049];
SegTree st2[2049];

int qry(int p, int i, int j, int L, int R, int y1, int y2) {
    if (i > R || j < L) return 0;
    if (L <= i && j <= R) {
        return st[p].qry(y1, y2);
    }
    return max(st2[p].qry(y1, y2), max(qry(p << 1, i, (i+j)/2, L, R, y1, y2), qry((p << 1) + 1, (i+j)/2+1, j, L, R, y1, y2)));
}
int qry(int x1, int x2, int y1, int y2) {
    return qry(1, 0, D-1, x1, x2, y1, y2);
}

void upd(int p, int i, int j, int L, int R, int y1, int y2, int v) {
    if (i > R || j < L) return;
    if (L <= i && j <= R) {
        st[p].upd(y1, y2, v);
        st2[p].upd(y1, y2, v);
        return;
    }
    st[p].upd(y1, y2, v);
    upd(p << 1, i, (i+j)/2, L, R, y1, y2, v);
    upd((p << 1) + 1, (i+j)/2+1, j, L, R, y1, y2, v);
}
void upd(int x1, int x2, int y1, int y2, int val) {
    upd(1, 0, D-1, x1, x2, y1, y2, val);
}

int main() {
    setupIO();

    int n; re(D, S, n);

    F0R(i, 2049) {
        st[i].init(S);
        st2[i].init(S);
    }

    F0R(i, n) {
        int d, s, w, x, y; re(d, s, w, x, y);
        --d; --s;

        int base = qry(x, x+d, y, y+s);
        upd(x, x+d, y, y+s, base + w);
    }

    ps(qry(0, D-1, 0, S-1));
}


