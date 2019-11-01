/*
 * Same as editorial, put all the candle heights in decreasing height in a segment tree.
 * During updates, ensure that heights remain decreasing.
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

int n, m, H[100000], C[100000];

struct node {
    int val, lazy;
};

node st[400000];

void build(int p, int i, int j) {
    if (i == j) {
        st[p].val = H[i];
        st[p].lazy = 0;
    } else {
        build(p << 1, i, (i+j)/2);
        build((p << 1) + 1, (i+j)/2 + 1, j);
        st[p].val = min(st[p << 1].val, st[(p << 1)+1].val);
        st[p].lazy = 0;
    }
}

void down(int p, bool children) {
    if (st[p].lazy == 0) return;
    if (children) {
        st[p << 1].lazy += st[p].lazy;
        st[(p << 1) + 1].lazy += st[p].lazy;
        st[p << 1].val += st[p].lazy;
        st[(p << 1) + 1].val += st[p].lazy;
    }
    st[p].lazy = 0;
}

int qry(int p, int i, int j, int l, int r) {
    down(p, i != j);
    if (l > j || r < i) return INF;
    if (i >= l && r >= j) return st[p].val;
    return min(qry(p << 1, i, (i+j)/2, l, r), qry((p << 1) + 1, (i+j)/2+1, j, l, r));
}

int getLeft(int p, int i, int j, int v) {
    down(p, i != j);
    if (i == j) {
        return i;
    }
    if (st[(p << 1)].val > v) {
        return getLeft((p << 1) + 1, (i+j)/2+1, j, v);
    } else {
        return getLeft((p << 1), i, (i+j)/2, v);
    }
}

int getRight(int p, int i, int j, int v) {
    down(p, i != j);
    if (i == j) {
        if (st[p].val == v) return i;
        return i - 1;
    }
    if (st[(p << 1)].val >= v) {
        return getRight((p << 1) + 1, (i+j)/2+1, j, v);
    } else {
        return getRight((p << 1), i, (i+j)/2, v);
    }
}

void upd(int p, int i, int j, int l, int r, int v) {
    down(p, i != j);
    if (i > r || j < l) return;
    if (i >= l && j <= r) {
        st[p].lazy += v;
        st[p].val += v;
    } else {
        upd(p << 1, i, (i+j)/2, l, r, v);
        upd((p << 1) + 1, (i+j)/2+1, j, l, r, v);
        st[p].val = min(st[p << 1].val, st[(p << 1) + 1].val);
    }
}

int main() {
    setupIO();

    re(n, m);
    reA(H, n);
    reA(C, m);
    sort(H, H+n);
    reverse(H, H+n);

    build(1, 0, n-1);

    F0R(i, m) {
        int q = C[i];
        int minVal = qry(1, 0, n-1, 0, q-1);
        if (minVal == 0 || q > n) {
            ps(i);
            exit(0);
        } else {
            int l = getLeft(1, 0, n-1, minVal), r = getRight(1, 0, n-1, minVal);
            if (l-1 >= 0) upd(1, 0, n-1, 0, l-1, -1);
            int ct = q - l;
            upd(1, 0, n-1, r - ct + 1, r, -1);
        }
    }
    ps(m);

    return 0;
}