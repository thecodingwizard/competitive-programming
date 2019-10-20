/*
 * Idea from here: https://codeforces.com/blog/entry/17630?#comment-225408
 * An alternative approach (similar idea): https://github.com/luciocf/OI-Problems/blob/master/Balkan/Balkan%202012/paths.cpp
 *
 * Source = a, Sink = b
 *
 * 1. Run dijkstra's to get distance from source to every node, and from the sink to every node
 * 2. Construct a shortest path (SP) tree starting at the source. Force the tree to contain the given path.
 * 3. Note that the least common ancestor of node i and the sink is always going to be a node in the given path.
 *    Set lca[i] = least common ancestor of node i and sink
 * 4. Index the given path. pathIdx[i] = index of node i (assuming i is in given path)
 * 5. Define array ans[0...k-1], initialize to infinity
 * 6. For each edge (u, v) not in the given path, define x = pathIdx[lca[u]] and y = pathIdx[lca[v]]
 *    Update ans[x], ans[x+1], ... ans[y-1] = min(_current value_, sourceToNode(u) + edgeLength(u, v) + nodeToSink(v))
 * 7. Print ans[0], ans[1], ... ans[k-2].
 *
 * A brute force implementation is fast enough to AC on both SPOJ and acmicpc judge.
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

int n, m, a, b, k;
vii adj[2000];
vi spAdj[2000];

ll sourceToNode[2000], destToNode[2000];
int spParent[2000];
int depth[2000];
int lca[2000];
int pathIdx[2000];
int ans[2000];

void dijkstra(int s, ll (&dist)[2000]) {
    F0R(i, n) dist[i] = LL_INF;
    dist[s] = 0;

    min_heap<pair<ll, int>> pq; pq.push({0, s});
    while (!pq.empty()) {
        pair<ll, int> top = pq.top(); pq.pop();
        if (top.pA > dist[top.pB]) continue;

        trav(x, adj[top.pB]) {
            if (dist[x.pA] > dist[top.pB] + x.pB) {
                spParent[x.pA] = top.pB;
                dist[x.pA] = dist[top.pB] + x.pB;
                pq.push({ dist[x.pA], x.pA });
            }
        }
    }
}

void dfsDepth(int u, int p, int d) {
    depth[u] = d;
    trav(x, spAdj[u]) {
        if (x != p) dfsDepth(x, u, d+1);
    }
}

void findLCA(int a, int b, int tgt) {
    if (depth[a] > depth[b]) return findLCA(b, a, tgt);
    while (depth[b] > depth[a]) b = spParent[b];
    while (a != b) {
        a = spParent[a]; b = spParent[b];
    }
    lca[tgt] = a;
}

int main() {
    setupIO();

    re(n, m, a, b); --a; --b;
    viii edges;
    F0R(i, m) {
        int a, b, w; re(a, b, w); --a; --b;
        edges.pb({w, {a, b}});
        edges.pb({w, {b, a}});
        adj[a].pb({b, w}); adj[b].pb({a, w});
    }

    dijkstra(b, destToNode);
    dijkstra(a, sourceToNode);

    re(k);
    int prv = -1;
    vi path;
    F0R(i, k) {
        int x; re(x); --x;
        path.pb(x);
        pathIdx[x] = i;
        if (prv != -1) {
            spParent[x] = prv;
        } else {
            spParent[x] = -1;
        }
        prv = x;
    }

    F0R(i, n) {
        if (spParent[i] != -1) {
            spAdj[spParent[i]].pb(i);
            spAdj[i].pb(spParent[i]);
        }
    }

    dfsDepth(a, a, 0);
    F0R(i, n) {
        findLCA(i, b, i);
    }

    SET(ans, INF, n);
    trav(edge, edges) {
        int u = edge.pB.pA, v = edge.pB.pB;
        if (spParent[v] == u || spParent[u] == v) continue;
        int x = pathIdx[lca[u]], y = pathIdx[lca[v]];
        if (x >= y) continue;

        FOR(i, x, y) {
            MIN(ans[i], (int)(sourceToNode[u] + edge.pA + destToNode[v]));
        }
    }

    F0R(i, k-1) {
        if (ans[i] == INF) ps(-1);
        else ps(ans[i]);
    }

    return 0;
}
