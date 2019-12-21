/*
 * Centroid decomposition
 *
 * For each centroid, we want to find the number of pairs (u, v) in the centroid's subtree such that
 * the path from u to v goes through the centroid, and is also valid.
 *
 * For each centroid, define cost[i] = minimum gas you will have as you start at the centroid and travel to
 * node i. Note that a path (u, v) is valid if and only if
 * a) you can get from u to the centroid without running out of gas,
 * b) cost[v] >= how much leftover gas you have after going from u to the centroid.
 *
 * Solution:
 * 1. Find the centroid of the graph
 * 2. Calculate cost[i], ie the cost (min amt of gas) to go from the centroid to every node. Do this in O(n) with a DFS.
 *    Insert every one of these values into a Binary Indexed Tree (or set or something). Also, if any of these values
 *    is >= 0, then we increment answer because one possible path is (centroid, node_whose_value_is_ge_0)
 * 3. For every child of the centroid,
 *    a) remove that child and the child's subtree from the binary indexed tree
 *    b) Make a list of how much gas left over after going from a node in the child's subtree to the centroid.
 *       Do this in O(n) with a DFS
 *    c) For every number in that list, query the binary indexed tree to find the number of values where value >= -item_in_list
 *       Add the result to the answer
 *    d) Re-add the child and the child's subtree to the binary indexed tree
 * 4. For every child of the centroid, repeat these steps on the smaller graph
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

#define MAXN 100000

int n;
vector<pair<int, ll>> adj[MAXN];
vl A;
int nodeSz[MAXN];
bool marked[MAXN];
ll ans = 0;
vector<pair<ll, int>> costFromCentroid;
int costIdx[MAXN];

ll ft[MAXN+10];
void upd(int k, int v, int n) {
    for (; k <= n; k += LSOne(k)) ft[k] += v;
}
ll qry(int k) {
    ll sum = 0; for (; k; k -= LSOne(k)) sum += ft[k];
    return sum;
}

int dfsSize(int u, int p) {
    nodeSz[u] = 1;
    trav(v, adj[u]) {
        if (v.pA != p && !marked[v.pA]) {
            nodeSz[u] += dfsSize(v.pA, u);
        }
    }
    return nodeSz[u];
}

int getCentroid(int u, int p, int totSz) {
    trav(v, adj[u]) {
        if (v.pA == p || marked[v.pA]) continue;
        if (nodeSz[v.pA] > totSz/2) return getCentroid(v.pA, u, totSz);
    }
    return u;
}

void dfsCostFromCentroid(int u, int p, ll cost, ll sum) {
    costFromCentroid.pb({cost,u});

    trav(v, adj[u]) {
        if (marked[v.pA] || v.pA == p) continue;
        dfsCostFromCentroid(v.pA, u, min(cost, sum + A[u] - v.pB), sum + A[u] - v.pB);
    }
}

vl costsToCentroid;
void dfsCostToCentroid(int u, int p, ll cost, ll sum) {
    if (cost >= 0) {
        costsToCentroid.pb(sum);
    }

    trav(v, adj[u]) {
        if (marked[v.pA] || v.pA == p) continue;
        dfsCostToCentroid(v.pA, u, min(A[v.pA] - v.pB, cost + (A[v.pA] - v.pB)), sum + A[v.pA] - v.pB);
    }
}

void solve(int node) {
    dfsSize(node, node);

    int centroid = getCentroid(node, node, nodeSz[node]);
    marked[centroid] = true;

    trav(v, adj[centroid]) {
        if (marked[v.pA]) continue;
        dfsCostFromCentroid(v.pA, centroid, A[centroid] - v.pB, A[centroid] - v.pB);
    }
    trav(x, costFromCentroid) if (x.pA >= 0) ans++;
    sort(all(costFromCentroid));
    vector<pair<ll, int>> allCostsFromCentroid = costFromCentroid;

    int ftsz = sz(allCostsFromCentroid)+1;

    SET(ft, 0, ftsz+1);
    F0R(i, sz(costFromCentroid)) {
        costIdx[costFromCentroid[i].pB] = i+1;
        upd(i+1, 1, ftsz);
    }

    trav(v, adj[centroid]) {
        if (marked[v.pA]) continue;

        costFromCentroid.clear();
        dfsCostFromCentroid(v.pA, centroid, A[centroid] - v.pB, A[centroid] - v.pB);
        trav(x, costFromCentroid) upd(costIdx[x.pB], -1, ftsz); // remove

        dfsCostToCentroid(v.pA, centroid, A[v.pA] - v.pB, A[v.pA] - v.pB);
        trav(cost, costsToCentroid) {
            auto it = lower_bound(all(allCostsFromCentroid), mp(-cost, -1));
            if (it != allCostsFromCentroid.end()) ans += qry(ftsz) - qry(costIdx[it->pB] - 1);

            if (cost >= 0) ans++; // Go to the centroid and stop
        }
        costsToCentroid.clear();

        trav(x, costFromCentroid) upd(costIdx[x.pB], 1, ftsz); // add
    }

    costFromCentroid.clear();

    trav(v, adj[centroid]) {
        if (marked[v.pA]) continue;
        solve(v.pA);
    }
}

int main() {
    setupIO();

    re(n);
    A.resz(n); re(A);
    F0R(i, n-1) {
        int a, b, w; re(a, b, w); --a; --b;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }

    solve(0);
    ps(ans);

    return 0;
}