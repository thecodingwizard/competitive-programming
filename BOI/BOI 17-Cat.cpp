/*
 * Also see: https://github.com/luciocf/OI-Problems/blob/master/BOI/BOI%202017/cat.cpp
 *
 * Arbitrarily root the tree.
 *
 * Define S = our current set of marked nodes. Note that an optimal solution exists if the next marked
 * node we take is the node with the greatest depth (as deep as possible) whose distance from any node
 * in S is >= D.
 *
 * Therefore we can sort nodes by depth and greedily add them to our set if its distance is >= D
 * We need to be able to do the following two queries fast:
 * 1. Find minimum distance from node X to any node in our set S
 * 2. Add node X to our set S
 *
 * We can do this quickly with centroid decomposition (identical to CF342E - Xenia and Tree).
 * For each centroid, we store the minimum distance from that centroid to a marked node.
 * To find minimum distance from node X, we go up the centroid tree.
 * MIN(curMinDist, dist(X, centroid) + minDistFromCentroidToMarkedNode[centroid])
 *
 * When adding the node X to set S, go up the centroid tree.
 * MIN(minDistFromCentroidToMarkedNode[centroid], dist(X, centroid))
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

#define MAXN 200000
#define LOGN 18

int n, d;
vi adj[MAXN];
int treeSz[MAXN];
bool marked[MAXN];
int centroidParent[MAXN];
int minDist[MAXN];
int depth[MAXN];
int p[MAXN][LOGN];

int dfsSize(int u, int p) {
    treeSz[u] = 1;
    trav(v, adj[u]) {
        if (marked[v] || v == p) continue;
        treeSz[u] += dfsSize(v, u);
    }
    return treeSz[u];
}

int findCentroid(int u, int p, int totSz) {
    trav(v, adj[u]) {
        if (marked[v] || v == p) continue;
        if (treeSz[v] > totSz/2) {
            return findCentroid(v, u, totSz);
        }
    }
    return u;
}

void centroidDecomp(int node, int parent) {
    dfsSize(node, node);
    int centroid = findCentroid(node, node, treeSz[node]);
    marked[centroid] = true;
    centroidParent[centroid] = parent;
    trav(v, adj[centroid]) {
        if (marked[v]) continue;
        centroidDecomp(v, centroid);
    }
}

void dfsDepth(int u, int p, int d) {
    depth[u] = d;
    trav(v, adj[u]) {
        if (v != p) dfsDepth(v, u, d+1);
    }
}

void buildLCA() {
    FOR(i, 1, LOGN) {
        F0R(j, n) {
            p[j][i] = p[p[j][i-1]][i-1];
        }
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) return lca(b, a);
    F0Rd(i, LOGN) {
        if (depth[p[b][i]] >= depth[a]) b = p[b][i];
    }
    if (a == b) return a;
    F0Rd(i, LOGN) {
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}

int getDist(int a, int b) {
    return depth[a] + depth[b] - 2*depth[lca(a, b)];
}

int getDistToSet(int u) {
    int centroid = u;
    int dist = INF;
    while (centroid != -1) {
        dist = min(dist, getDist(u, centroid) + minDist[centroid]);
        centroid = centroidParent[centroid];
    }
    return dist;
}

void addToSet(int u) {
    int centroid = u;
    while (centroid != -1) {
        MIN(minDist[centroid], getDist(u, centroid));
        centroid = centroidParent[centroid];
    }
}

int main() {
    setupIO();

    re(n, d);
    F0R1(i, n-1) {
        int pa; re(pa);
        adj[pa].pb(i); adj[i].pb(pa);
        p[i][0] = pa;
    }
    p[0][0] = 0;

    SET(marked, false, MAXN);
    SET(minDist, INF, MAXN);
    centroidDecomp(0, -1);

    dfsDepth(0, 0, 0);
    vii nodes;
    F0R(i, n) {
        nodes.pb({depth[i], i});
    }
    sort(all(nodes));
    reverse(all(nodes));

    buildLCA();

    int ans = 0;
    trav(node, nodes) {
        int distToSet = getDistToSet(node.pB);
        if (distToSet >= d) {
            ans++;
            addToSet(node.pB);
        }
    }
    ps(ans);

    return 0;
}