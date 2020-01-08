/*
 * Same as luciocf: https://gist.github.com/luciocf/3cae49c9fe640a7d78e22ca832908091
 *
 * Use Parallel Binary Search (https://codeforces.com/blog/entry/45578)
 * and Finding Bridges Online (https://cp-algorithms.com/graph/bridge-searching-online.html)
 *
 * Note that 0 <= a, b <= n, ie. A_i/B_i/x_i/y_i can equal n (read the comment for the problem on DMOJ).
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

#define MAXN 150010

int dsu_2ecc[MAXN], dsu_cc[MAXN], ecc_sz[MAXN], cc_sz[MAXN], par[MAXN], vis[MAXN];
int iter = 0;

int find_dsu2(int u) {
    if (u == -1) return -1;
    return dsu_2ecc[u] == u ? u : dsu_2ecc[u] = find_dsu2(dsu_2ecc[u]);
}
int find_dsu1(int u) {
    return dsu_cc[u] == u ? u : dsu_cc[u] = find_dsu1(dsu_cc[u]);
}

void make_root(int u) {
    u = find_dsu2(u);
    int root = u;
    int child = -1;
    while (u != -1) {
        int p = find_dsu2(par[u]);
        par[u] = child;
        dsu_cc[u] = root;
        child = u;
        u = p;
    }
    cc_sz[root] = cc_sz[child];
}

void merge_path(int u, int v) {
    iter++;
    vi path_u, path_v;
    int lca = -1;
    while (lca == -1) {
        if (u != -1) {
            u = find_dsu2(u);
            path_u.pb(u);
            if (vis[u] == iter) {
                lca = u;
            }
            vis[u] = iter;
            u = par[u];
        }
        if (v != -1) {
            v = find_dsu2(v);
            path_v.pb(v);
            if (vis[v] == iter) {
                lca = v;
            }
            vis[v] = iter;
            v = par[v];
        }
    }
    for (int x : path_u) {
        dsu_2ecc[x] = lca;
        if (x == lca) break;
    }
    for (int x : path_v) {
        dsu_2ecc[x] = lca;
        if (x == lca) break;
    }
}

void add(int u, int v) {
    u = find_dsu2(u), v = find_dsu2(v);
    if (u == v) return;
    if (find_dsu1(u) == find_dsu1(v)) {
        merge_path(u, v);
        return;
    }
    if (cc_sz[find_dsu1(u)] > cc_sz[find_dsu1(v)]) {
        swap(u, v);
    }
    // now merge u into v
    make_root(u);
    dsu_cc[u] = par[u] = v;
    cc_sz[find_dsu1(v)] += cc_sz[find_dsu1(u)];
}

int main() {
    setupIO();

    int n, d, q; re(n, d, q);

    vii roads;
    F0R(i, d) {
        int a, b; re(a, b);
        roads.pb({a, b});
    }

    vii queries;
    F0R(i, q) {
        int a, b; re(a, b);
        queries.pb({a, b});
    }

    int logD = 25;
    vi check[d];
    int L[q], R[q], ans[q];
    F0R(i, q) {
        L[i] = 0, R[i] = d;
        ans[i] = -1;
    }
    for (int step = 1; step <= logD; step++) {
        F0R(i, MAXN) {
            dsu_cc[i] = dsu_2ecc[i] = i;
            cc_sz[i] = ecc_sz[i] = 1;
            vis[i] = par[i] = -1;
        }
        F0R(i, d) check[i].clear();

        F0R(i, q) {
            if (L[i] != R[i]) {
                int mid = (L[i] + R[i])/2;
                if (mid < d) check[mid].pb(i);
            }
        }
        F0R(i, d) {
            add(roads[i].pA, roads[i].pB);
            trav(v, check[i]) {
                if (find_dsu2(queries[v].pA) == find_dsu2(queries[v].pB)) {
                    ans[v] = i;
                    R[v] = i;
                } else {
                    L[v] = i+1;
                }
            }
        }
    }
    F0R(i, q) {
        ps(ans[i]);
    }

    return 0;
}