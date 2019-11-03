/**
 * Very similar to CSAcademy41-E
 *
 * Sort masts from lowest to tallest. Greedily place the sails of a mast on the height that
 * has the fewest number of sails. To do this, maintain a decreasing lazy max segment tree.
 *
 * Updates are very similar to CSA41E. Just update [h-k...h] with +1. However in order
 * to maintain the "decreasing" property, we add two queries to the seg tree: findLeft(x) and findRight(x)
 * which finds the leftmost index of the element x and the rightmost index of the element x. Then
 * instead of updating [h-k...h] we find the leftmost & rightmost index of the biggest number in the
 * range [h-k...h] and update accordingly (see CSA41E editorial for more clear explanation)
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


struct node {
    int val = 0, lazy = 0;
};

node st[400000];

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
    if (l > j || r < i) return -1;
    if (i >= l && r >= j) return st[p].val;
    return max(qry(p << 1, i, (i+j)/2, l, r), qry((p << 1) + 1, (i+j)/2+1, j, l, r));
}

int getLeft(int p, int i, int j, int v) {
    down(p, i != j);
    if (i == j) {
        if (st[p].val == v) return i;
        return i + 1;
    }
    if (st[(p << 1) + 1].val <= v) {
        return getLeft((p << 1), i, (i+j)/2, v);
    } else {
        return getLeft((p << 1) + 1, (i+j)/2+1, j, v);
    }
}

int getRight(int p, int i, int j, int v) {
    down(p, i != j);
    if (i == j) {
        if (st[p].val == v) return i;
        assert(false);
    }
    if (st[(p << 1) + 1].val < v) {
        return getRight((p << 1), i, (i+j)/2, v);
    } else {
        return getRight((p << 1) + 1, (i+j)/2+1, j, v);
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
        st[p].val = max(st[p << 1].val, st[(p << 1) + 1].val);
    }
}


int main() {
    setupIO();

    int nn; re(nn);
    int n = 100000;
    vii sails;
    F0R(i, nn) {
        int h, k; re(h, k);
        sails.pb({h, k});
    }
    sort(all(sails));

    trav(x, sails) {
        int h = x.pA, k = x.pB;
        int mx = qry(1, 0, n-1, h-k, h-1);
        int left = getLeft(1, 0, n-1, mx);
        int right = getRight(1, 0, n-1, mx);
        int ct = h-right - 1;
        if (ct <= 0) {
            upd(1, 0, n-1, left, left+k-1, 1);
        } else {
            upd(1, 0, n-1, right + 1, right + ct, 1);
            upd(1, 0, n-1, left, left + (k-ct) - 1, 1);
        }
    }

    ll ans = 0;
    F0R(i, n) {
        ll x = qry(1, 0, n-1, i, i);
        ans += x*(x-1)/2;
    }
    ps(ans);

    return 0;
}