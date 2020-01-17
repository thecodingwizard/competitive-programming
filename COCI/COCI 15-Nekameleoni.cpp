/*
 * Same solution as editorial. My implementation *barely* runs in time, and frequently submissions will return "bad_alloc"
 * even though it's not supposed to (my solution fits within the memory limit comfortably at ~414mb).
 * Resubmitting usually fixes it. I had a test case that was 2.995s/3.0s...
 *
 * I used a segment tree of length 263000. Each segment tree stores the answer (or INF if no answer exists),
 * and its K "interesting" prefixes and suffixes. Each prefix/suffix stores a bitmask and a position value.
 *
 * When merging, we can use two pointers on the left suffix and the right prefix in order to calculate answer.
 * To merge prefix, we loop through all the prefixes on the left, then loop through prefixes on the right.
 * If adding a right prefix results in a different bitmask, we add it to the list of "interesting" prefixes.
 * Similar for suffix.
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

int n, K, m;

struct node {
    pair<ll, int> prefix[51], suffix[51];
    int ans = INF;
};

node *st = new node[263000];

void build(int p, int i, int j) {
    F0R(x, K+1) st[p].prefix[x].pB = st[p].suffix[x].pB = -1;
    if (i != j) {
        build(p << 1, i, (i+j)/2);
        build((p << 1) + 1, (i+j)/2+1, j);
    }
}

void upd(int p, int i, int j, int k, int v) {
    if (i > k || j < k) return;
    if (i == j && i == k) {
        st[p].prefix[0].pA = (1LL << v);
        st[p].suffix[0].pA = (1LL << v);
        st[p].suffix[0].pB = st[p].prefix[0].pB = i;
        if (K == 1) st[p].ans = 1;
        return;
    }
    int l = p << 1, r = (p << 1) + 1;
    upd(l, i, (i+j)/2, k, v);
    upd((p << 1) + 1, (i+j)/2+1, j, k, v);
    st[p].ans = min(st[l].ans, st[r].ans);

    int lPtr = K-1, rPtr = 0;
    while (st[l].suffix[lPtr].pB == -1) lPtr--;
    while (lPtr >= 0) {
        while (st[r].prefix[rPtr].pB != -1 && (st[l].suffix[lPtr].pA | st[r].prefix[rPtr].pA) != ((1LL << K) - 1)) rPtr++;
        if (rPtr == K || st[r].prefix[rPtr].pB == -1) break;
        MIN(st[p].ans, st[r].prefix[rPtr].pB - st[l].suffix[lPtr].pB + 1);
        lPtr--;
    }

    int idx;
    for (idx = 0; idx < K; idx++) {
        if (st[l].prefix[idx].pB == -1) break;
        st[p].prefix[idx] = st[l].prefix[idx];
    }
    int i2 = 0;
    for (int i = 0; i < K - idx; i++) {
        while (st[r].prefix[i2].pB != -1 && (st[r].prefix[i2].pA | st[p].prefix[idx+i-1].pA) == st[p].prefix[idx+i-1].pA) i2++;
        if (i2 == K || st[r].prefix[i2].pB == -1) {
            st[p].prefix[idx + i].pB = -1;
        } else {
            st[p].prefix[idx + i].pA = st[l].prefix[idx - 1].pA | st[r].prefix[i2].pA;
            st[p].prefix[idx + i].pB = st[r].prefix[i2].pB;
        }
    }
    for (idx = 0; idx < K; idx++) {
        if (st[r].suffix[idx].pB == -1) break;
        st[p].suffix[idx] = st[r].suffix[idx];
    }
    i2 = 0;
    for (int i = 0; i < K - idx; i++) {
        while (st[l].suffix[i2].pB != -1 && (st[l].suffix[i2].pA | st[p].suffix[idx+i-1].pA) == st[p].suffix[idx+i-1].pA) i2++;
        if (i2 == K || st[l].suffix[i2].pB == -1) {
            st[p].suffix[idx + i].pB = -1;
        } else {
            st[p].suffix[idx + i].pA = st[r].suffix[idx - 1].pA | st[l].suffix[i2].pA;
            st[p].suffix[idx + i].pB = st[l].suffix[i2].pB;
        }
    }
}

int main() {
    setupIO();

    re(n, K, m);
    build(1, 0, n-1);
    F0R(i, n) {
        int x; re(x); --x; upd(1, 0, n-1, i, x);
    }
    F0R(i, m) {
        int cmd; re(cmd);
        if (cmd == 1) {
            int p, v; re(p, v); --p; --v;
            upd(1, 0, n-1, p, v);
        } else {
            if (st[1].ans == INF) ps(-1);
            else ps(st[1].ans);
        }
    }

    return 0;
}