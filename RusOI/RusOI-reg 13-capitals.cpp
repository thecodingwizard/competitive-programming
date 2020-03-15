/*
 * Note: 1 <= n <= 1e5
 *
 * - If d is odd then our answer is 0
 * - Using binary lifting, we can, for every node, find the # of nodes d/2 units away in each of its subtrees
 * - Using centroid decomp we can, for every node, find the total number of nodes d/2 units away
 * - Subtract sum of nodes d/2 units away in subtree from the total number of nodes ==> we get the number
 *   of nodes d/2 units away in the parent tree
 * - Now for every node, we make a list that contains the number of nodes d/2 units away from that node for every
 *   adjacent node (one number per child node, and one number for the parent node)
 * - For every triplet in that list, we multiply the numbers together and add it to our answer
 * - We can do the above fast with prefix sums
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

int n, d;
vi adj[100000];
int sz[100000];
bool marked[100000];
int centroidParent[100000];
map<int, vi> nodeCt[100000];
vi totNodeCt[100000];
int numNodesDAway[100000];
map<int, int> dist[100000];

int dfsSize(int u, int p) {
    sz[u] = 1;
    trav(v, adj[u]) {
        if (!marked[v] && v != p) sz[u] += dfsSize(v, u);
    }
    return sz[u];
}

int findCentroid(int u, int p, int totSz) {
    trav(v, adj[u]) {
        if (!marked[v] && v != p && sz[v] > totSz / 2) return findCentroid(v, u, totSz);
    }
    return u;
}

void dfsDist(int u, int p, int d, vi &a, int centroid) {
    dist[centroid][u] = d;
    if (sz(a) <= d) {
        a.pb(1);
    } else {
        a[d]++;
    }
    trav(v, adj[u]) {
        if (v != p && !marked[v]) dfsDist(v, u, d+1, a, centroid);
    }
}

void centroidDecomp(int u, int p) {
    int centroid = findCentroid(u, u, dfsSize(u, u));

    if (p != -1) {
        nodeCt[p][centroid].pb(0);
        dfsDist(u, u, 1, nodeCt[p][centroid], p);
    }

    marked[centroid] = true;
    centroidParent[centroid] = p;

    trav(v, adj[centroid]) {
        if (!marked[v]) {
            centroidDecomp(v, centroid);
        }
    }
    trav(x, nodeCt[centroid]) {
        F0R(i, sz(x.pB)) {
            if (i >= sz(totNodeCt[centroid])) {
                totNodeCt[centroid].pb(x.pB[i]);
            } else {
                totNodeCt[centroid][i] += x.pB[i];
            }
        }
    }
    dist[centroid][centroid] = 0;
    if (totNodeCt[centroid].empty()) totNodeCt[centroid].pb(1);
    else totNodeCt[centroid][0]++;
}

int par[100000][18];
int depth[100000];

void dfsParent(int u, int p, int d) {
    depth[u] = d;
    par[u][0] = p;
    trav(v, adj[u]) {
        if (v != p) dfsParent(v, u, d+1);
    }
}

map<int, int> ct[100000];

int main() {
    setupIO("capitals");

    re(n, d);
    if (d & 1) {
        ps(0);
        return 0;
    } else {
        d /= 2;
    }
    F0R(i, n-1) {
        int a, b; re(a, b);
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }

    SET(marked, false, n);
    centroidDecomp(0, -1);

    F0R(i, n) {
        numNodesDAway[i] = 0;
        int target = i, targetParent = -1;
        while (target != -1) {
            int blah = d-dist[target][i];
            if (blah >= 0) {
                numNodesDAway[i] += blah<sz(totNodeCt[target])?totNodeCt[target][blah]-(targetParent!=-1&&blah<sz(nodeCt[target][targetParent])?nodeCt[target][targetParent][blah]:0):0;
            }
            targetParent = target;
            target = centroidParent[target];
        }
    }

    dfsParent(0, 0, 0);
    FOR(i, 1, 18) {
        F0R(j, n) {
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }

    F0R(i, n) {
        if (d > depth[i]) continue;
        int searchNumber = d - 1;
        int node = i;
        F0R(j, 18) {
            if ((1 << j) & searchNumber) {
                node = par[node][j];
            }
        }
        ct[par[node][0]][node]++;
    }

    ll ans = 0;
    F0R(i, n) {
        int subtreeNodeCt = 0;
        vi blah;
        trav(v, ct[i]) {
            subtreeNodeCt += v.pB;
            blah.pb(v.pB);
        }
        int numNodesAbove = numNodesDAway[i] - subtreeNodeCt;
        blah.pb(numNodesAbove);

        vl ps; ps.assign(sz(blah), 0);

        F0R(j, sz(blah)) {
            ps[j] = (j==0?0:ps[j-1]) + blah[j];
        }
        F0Rd(k,  sz(blah)) {
            ps[k] = (k==0?0:ps[k-1])*blah[k];
        }
        FOR(k, 1, sz(blah)) {
            ps[k] += ps[k-1];
        }
        F0Rd(l, sz(blah)) {
            ans += (l==0?0:ps[l-1])*blah[l];
        }
    }
    ps(ans);

    return 0;
}
