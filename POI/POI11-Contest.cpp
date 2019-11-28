/*
 * Same solution as editorial:
 * - Create a bipartite graph, left nodes are programmers and right nodes are tasks, draw edges if programmer can solve task
 * - Greedily assign people to tasks s.t. max # of tasks are solved. Ignore the contest time limit constraint for now.
 *   Mark the edge between programmer => task if the programmer is assigned to that task
 * - We want to minimize the tasks each person has to solve. Note that if we find a path, starting from a programmer and
 *   ending at another programmer, where the path edges alternates from marked (programmer is assigned to that task)
 *   and unmarked (task can be solved by programmer but isn't currently assigned that way), and if the degree
 *   of the first node is greater than 1 + degree of end node, then we can alternate all the edges in that
 *   path and we will gain a better solution. (alternate meaning make marked edges unmarked and unmarked edges marked).
 * - To find this path, we iterate through all the programmer nodes in decreasing degree order, and we DFS
 *   to see if such a path exists. We mark all programmer nodes we visit as "visited" and we don't visit them twice,
 *   because if we visited them once before and we couldn't find a valid path, then we won't be able to find
 *   a valid path the second time around either due to the order in which we process the programmer nodes.
 * - In practice we won't have to DFS through every node to find a valid path, so even though complexity looks bad,
 *   if we make sure to exit the search as soon as we find a valid path then it will actually run in time
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

vi person[500];
vi problem[500];

int assign[500];
set<int> tasks[500];

int startNode, endNode;
int p[500];
void search(int u) {
    if (sz(tasks[startNode]) > sz(tasks[u]) + 1) {
        endNode = u;
        return;
    }
    trav(task, tasks[u]) {
        trav(x, problem[task]) {
            if (assign[task] == x) continue;
            if (p[x] == -1) {
                p[x] = task;
                search(x);
                if (endNode != -1) return;
            }
        }
    }
}

int main() {
    setupIO();

    int n, m, r, t, k; re(n, m, r, t, k);
    SET(assign, -1, m);
    F0R(i, k) {
        int a, b; re(a, b);
        person[--a].pb(--b);
        problem[b].pb(a);
        if (assign[b] == -1) {
            assign[b] = a;
            tasks[a].insert(b);
        } else if (sz(tasks[assign[b]]) > sz(tasks[a]) + 1) {
            // Note: You don't actually need this optimization
            tasks[assign[b]].erase(b);
            tasks[a].insert(b);
            assign[b] = a;
        }
    }

    while (true) {
        vii deg; F0R(i, n) deg.eb(sz(tasks[i]), i);
        SET(p, -1, n);

        sort(all(deg));
        endNode = -1;
        F0Rd(i, n) {
            startNode = deg[i].pB;
            search(deg[i].pB);
            if (endNode != -1) break;
        }

        if (endNode == -1) break;
        while (endNode != startNode) {
            int old = assign[p[endNode]];
            tasks[endNode].insert(p[endNode]);
            tasks[old].erase(p[endNode]);
            assign[p[endNode]] = endNode;
            endNode = old;
        }
    }

    int ct = 0; ll penalty = 0;
    vector<pair<int, ii>> print;
    F0R(i, n) {
        int taskCt = 0;
        trav(task, tasks[i]) {
            if (r*taskCt + r > t) break;
            penalty += r*taskCt+r;
            print.pb({i+1, {task+1, r*taskCt}});
            taskCt++; ct++;
        }
    }
    ps(ct, penalty);
    trav(x, print) ps(x);

    return 0;
}
