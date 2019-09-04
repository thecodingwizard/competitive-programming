/*
 * Crucially, we know there is a section that all the start nodes must pass through to reach the end node.
 * Furthermore, since it's a tree, between two nodes there's exactly one path.
 *
 * To find the section, we just simulate moving the start nodes up until we get to a node that all the start nodes
 * can reach. To do this efficiently, we run a DFS from one end node and assign "depth" trackers to each node.
 * We also assign parent pointers during this time (the end node is the root). Now we process the farthest nodes first,
 * each time we process a node we basically merge that node with its parent and process the parent, making sure to
 * process nodes from farthest to closest. Note that we only process each node at most once. Once we merge the
 * final start node, then we have found the start of the section.
 *
 * Next, from the section start node, we run another dfs to calculate dist from that node to every other node.
 * We make a list of all the distances from section node to end node. Now we need list of distances from beginning
 * nodes to the section start node. First, let's ignore the restriction of one node per edge at once. Let's make
 * list of distances from start nodes to the section node, let's say we get {2, 2, 2, 4, 8}. Note that at any
 * given point in time the section node can only let one node through at once. Therefore, the actual time
 * it takes from start node to section node (with the restriction) is {2, 3, 4, 5, 8} (basically just make it
 * strictly increasing). Finally we pair each start node distance with the distance from section node to end node.
 *
 * Much care must be taken to pass memory limit.
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

vi adj[1000000];
int depth[1000000];
vi pa;
vi numNodes;
bool vis[1000000];
int z; int n, w;
vi dest;
auto cmp = [](int a, int b) { return depth[a] < depth[b]; };
priority_queue<int, vi, decltype(cmp)> pq(cmp);

void dfs(int u, int p, int d) {
    pa[u] = p;
    depth[u] = d;
    trav(x, adj[u]) {
        if (x == p) continue;
        dfs(x, u, d + 1);
    }
}

void dfs2(int u, int p, int d) {
    depth[u] = d;
    if (u >= n - z) {
        dest.pb(d);
    } else {
        trav(x, adj[u]) if (x != p) dfs2(x, u, d + 1);
    }
}

int main() {
    setupIO();

    re(n, w, z);
    F0R(i, n-1) {
        int a, b; re(a, b);
        adj[--b].pb(--a);
        adj[a].pb(b);
    }
    int p; re(p);
    vi A; A.resz(p); re(A);
    F0R(i, p) A[i]--;
    numNodes.assign(n, 0);
    SET(vis, 0, n);
    pa.resize(n);

    dfs(n-1, -1, 0);

    trav(x, A) {
        pq.push(x);
        numNodes[x]++;
        vis[x] = true;
    }
    int startNode = -1;
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        if (numNodes[u] == p) {
            startNode = u;
            break;
        }
        int v = pa[u];
        numNodes[v] += numNodes[u];
        if (!vis[v]) {
            vis[v] = true;
            pq.push(v);
        }
    }
    while (!pq.empty()) pq.pop();
    numNodes.clear();
    pa.clear();

    dfs2(startNode, startNode, 0);
    sort(all(dest));

    F0R(i, n) adj[i].clear();

    vi rawDist;
    trav(x, A) {
        rawDist.pb(depth[x]);
    }
    A.clear();
    sort(all(rawDist));
    int prv = -1;
    int mx = 0;
    F0R(i, p) {
        int x = rawDist[i];
        int xx;
        if (x > prv) {
            xx = x;
            prv = x;
        } else {
            xx = prv + 1;
            prv++;
        }
        MAX(mx, xx + dest[p - i - 1]);
    }

    ps(mx);

    return 0;
}