/*
 * This problem is basically finding max independent set of graph, which is NP hard.
 *
 * First notice that the edge direction doesn't matter, so we'll make all edges undirected.
 *
 * The key to being able to solve this problem is that k >= n-10, so we can at most exclude 10 nodes.
 * Let's define l = n - k. l <= 10.
 *
 * If a node has degree > l, then notice that we definitely cannot take it, because if we did then we would
 * have to exclude more than l other nodes, and the answer is NIE.
 *
 * So we remove all nodes with degree > l and update the new l value to be the max number of nodes we can remove.
 * If l is negative then output NIE.
 *
 * Further notice that the number of remaining nodes with degree > 0 must be <= l*(l+1), otherwise we can also
 * prove that no solution is possible.
 *
 * Finally, we can brute force dfs with backtracking to find the answer.
 *
 * Implementation of dfs:
 * - make a list of all vertices with degree > 0
 * - dfs state: (idx, k) where idx is the index of the vertices list that we're currently on,
 *              k is the number of vertices we can still remove
 * - if k < 0, then NIE
 * - otherwise, we either keep this vertex or remove the vertex and decrement ks
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

int n, K, k;
vi rawAdj[1000000];
vi adj[1000000];
bool alive[1000000];
bool take[1000000];
vi vertices;
bool possible = false;
vi finalAns;

void solve(int idx, int k) {
    if (k < 0) return;
    if (idx == sz(vertices)) {
        possible = true;
        vi op;
        F0R(i, idx) {
            if (alive[vertices[i]]) op.pb(vertices[i]);
        }
        if (sz(op) > sz(finalAns)) finalAns = op;
        return;
    }
    int x = vertices[idx];
    if (!alive[x]) return solve(idx + 1, k - 1);

    alive[x] = false;
    solve(idx + 1, k - 1);

    alive[x] = true;
    vector<bool> cache;
    trav(y, adj[x]) {
        cache.pb(alive[y]);
        alive[y] = false;
    }
    solve(idx + 1, k);
    F0R(i, sz(adj[x])) alive[adj[x][i]] = cache[i];
}

int main() {
    setupIO();

    re(n, K); k = n - K;
    int m; re(m);
    SET(alive, true, n);
    F0R(i, m) {
        int a, b; re(a, b); --a; --b;
        rawAdj[a].pb(b); rawAdj[b].pb(a);
    }

    F0R(i, n) {
        sort(all(rawAdj[i]));
        rawAdj[i].erase(unique(all(rawAdj[i])), rawAdj[i].end());
    }

    int removed = 0;
    F0R(i, n) {
        if (alive[i] && rawAdj[i].size() > k) {
            alive[i] = false;
            removed++;
        }
    }

    F0R(i, n) {
        if (!alive[i]) {
            rawAdj[i].clear();
            continue;
        }
        trav(x, rawAdj[i]) {
            if (alive[x]) adj[i].pb(x);
        }
        rawAdj[i].clear();
    }

    int num = 0;
    F0R(i, n) {
        if (alive[i] && adj[i].size() > 0) {
            num++;
            vertices.pb(i);
            take[i] = false;
        } else {
            take[i] = alive[i];
        }
    }

    k -= removed;
    if (k < 0 || num > k*(k+1)) {
        ps("NIE");
        return 0;
    }

    solve(0, k);

    if (!possible) ps("NIE");
    else {
        trav(x, finalAns) take[x] = true;
        vi print;
        F0R(i, n) {
            if (take[i]) print.pb(i+1);
        }
        ps(sz(print));
        ps(print);
    }

    return 0;
}
