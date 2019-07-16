/*
 * My solution is the same as the editorial. Note that my implementation may be slightly different,
 * but the concept is the same.
 *
 * To solve this problem, we first create a list of possible salaries to assign to blank nodes.
 *
 * We will call each node with a known value a "tree". The root of the "tree" is the node
 * with the known salary, and all the other nodes of the tree are blank nodes connected (directly or indirectly)
 * to the root node.
 *
 * We observe that the only time we can determine the missing values of a tree is when the tree is a path:
 * when each node in the tree has exactly one child. Otherwise, if a node in the tree has two or more children,
 * the node's children cannot be determined.
 *
 * Let's now process the trees in increasing value. Assume we are processing a tree i with root salary A_i and B_i
 * empty nodes (nodes that need to have salaries assigned to them.)
 * Define K_i to be the list of all available, unused salaries <= A_i. We have to figure out a way to assign
 * salaries from K_i to the blank nodes of the tree we are currently processing. However, note that since
 * we are processing trees in increasing value order, it doesn't actually matter which of the K_i salaries
 * we choose, since any salary we don't use from K_i will be part of K_(i+1). So we can just greedily pick
 * any subset of B_i salaries from K_i.
 *
 * To assign salaries to our tree, we can once again do this greedily by assigning the largest available salary to
 * the first child, the second largest salary to the second child, and so on. Once we hit a node that has 2+
 * children, we must stop since it's no longer possible to determine the salaries for those nodes.
 *
 * However, what will happen if len(K_i) > B_i? In other words what will happen if we have more
 * possible salaries than nodes to assign them to? Then all the possible salaries are invalid
 * (all salaries in K_i cannot be determined).
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

int n;
vi children[1000001];
vi blankChildren[1000001];
int stop[1000001];
int val[1000001];
int root;
vii toProcess;
vii available;
bool taken[1000001];
vii bad;
int final[1000001];
int badCtr[1000002];

void dfs(int u, int x) {
    int ct = 0;
    int initSz = sz(blankChildren[x]);
    for (int v : children[u]) {
        if (val[v] != 0) continue;
        ct++;
        if (ct == 2) MIN(stop[x], initSz);
        blankChildren[x].pb(v);
        dfs(v, x);
    }
}

void handle(int u, int i) {
    i += sz(blankChildren[u]);
    int idx = 0;
    for (int v : blankChildren[u]) {
        if (stop[u] == idx) break;
        idx++;
        final[v] = available[i--].pA;
    }
}

int main() {
    setupIO();

    re(n);
    SET(taken, false, 1000001);
    F0R1(i, n) {
        int p, z;
        re(p, z);
        val[i] = final[i] = z;
        taken[z] = true;
        if (p == i) {
            root = i;
            val[i] = final[i] = n;
            taken[n] = true;
        } else {
            children[p].pb(i);
        }
    }
    int ctr = 0;
    F0R1(i, n) {
        if (!taken[i]) available.pb(mp(i, ctr++));
    }

    F0R1(i, n) {
        if (val[i] != 0) {
            stop[i] = INF;
            dfs(i, i);
            toProcess.pb(mp(val[i], i));
        }
    }
    SORT(toProcess);

    int lhs = -1;
    SET(badCtr, 0, 1000002);
    trav(x, toProcess) {
        int val = x.pA;
        int node = x.pB;
        if (sz(blankChildren[node]) == 0) continue;
        auto it = lb(all(available), mp(val, -1));
        it--;
        int legal = it->pB - lhs;
        assert(legal >= sz(blankChildren[node]));
        if (legal == sz(blankChildren[node])) {
            handle(node, lhs);
        } else {
            badCtr[available[lhs + 1].pA]++;
            badCtr[it->pA + 1]--;
        }
        lhs += sz(blankChildren[node]);
    }
    FOR(i, 1, 1000002) {
        badCtr[i] += badCtr[i - 1];
    }

    F0R1(i, n) {
        if (val[i] == 0 && final[i] != 0 && badCtr[final[i]] > 0) {
            ps(0);
        } else {
            ps(final[i]);
        }
    }

    return 0;
}