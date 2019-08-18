/*
 * Same as editorial.
 * - Root at exit vertex.
 * - Note that if the edge doesn't disconnect the queried node from the exit vertex, then it's possible to escape
 * - Solve the above problem by doing a preorder dfs traversal, find the root of the newly formed subtree after the
 * edge removal and see if the queried vertex is in the subtree
 * - If it isn't, then escape. Otherwise, we have to go to a shop.
 *
 * - Assume that the queried vertex is u, and the optimal shop is v. Assume that lca(u, v) = w. Define d[x] = distance
 * from root to x. Note that the distance to shop v from u is d[u] + d[v] - 2*d[w]. So for every vertex x,
 * define magic[x] = -2*d[x] + d[optimalShop] where optimalShop is a shop located in the subtree of x that minimizes
 * magic[x]. magic can be computed by dp O(n).
 *
 * - We can now solve the problem by starting at u and moving up one parent at a time utilizing magic[x]. However that's
 * too slow, we precompute with binary jumping and now we can find the smallest magic[x] in log n time.
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

/* ============================ */

int n, s, q, e;
vii adj[100000];
bool shop[100000];
viii edges;
int id[100000], lower[100000], upper[100000];
ll nearestShop[100000];
ll dist[100000];
int pa[100000];
int jump[100000][18];
ll jumpVal[100000][18];
int depth[100000];

int dfs(int u, int p, int idd, ll d, int dd) {
    depth[u] = dd;
    pa[u] = p;
    dist[u] = d;
    id[u] = idd;
    lower[u] = idd;
    int extra = 1;
    trav(e, adj[u]) {
        if (e.pA == p) continue;
        extra += dfs(e.pA, u, idd + extra, d + e.pB, dd+1);
    }
    upper[u] = idd + extra - 1;
    return extra;
}

ll dfsShop(int u, int p) {
    ll closestShop = LL_INF;
    if (shop[u]) closestShop = dist[u];

    trav(e, adj[u]) {
        if (e.pA == p) continue;
        MIN(closestShop, dfsShop(e.pA, u));
    }

    nearestShop[u] = -2*dist[u]+closestShop;
    return closestShop;
}

int main() {
    setupIO();

    re(n, s, q, e);
    F0R(i, n - 1) {
        int a, b, w; re(a, b, w);
        adj[--a].pb({--b, w});
        adj[b].pb({a, w});
        edges.pb({w, {a, b}});
    }
    SET(shop, false, n);
    F0R(i, s) {
        int c; re(c);
        shop[--c] = true;
    }

    dfs(e - 1, e - 1, 0, 0, 0);
    dfsShop(e - 1, e - 1);
    F0R(i, n) {
        jump[i][0] = pa[i];
    }
    FOR(i, 1, 18) {
        F0R(j, n) {
            jump[j][i] = jump[jump[j][i-1]][i-1];
        }
    }
    F0R(i, n) {
        jumpVal[i][0] = nearestShop[jump[i][0]];
    }
    FOR(i, 1, 18) {
        F0R(j, n) {
            jumpVal[j][i] = min(jumpVal[j][i-1], jumpVal[jump[j][i-1]][i-1]);
        }
    }

    F0R(i, q) {
        int x, r; re(x, r); --x; --r;
        iii edge = edges[x];
        int a = edge.pB.pA, b = edge.pB.pB;
        if (id[a] > id[b]) tie(a, b) = mt(b, a);

        if (id[r] > upper[b] || id[r] < lower[b]) {
            ps("escaped");
        } else {
            int cur = r;
            ll best = nearestShop[r];
            F0Rd(i, 18) {
                if (depth[jump[cur][i]] >= depth[b]) {
                    MIN(best, jumpVal[cur][i]);
                    cur = jump[cur][i];
                }
            }
            if (best >= LL_INF/2) {
                ps("oo");
            } else {
                ps(best + dist[r]);
            }
        }
    }

    return 0;
}
