/*
 * Think of this problem as a graph: Each node is the position 1...n.
 * If two nodes u and v are currently in conflict (e.g. their soldiers have same height) then they have an edge
 * between them of weight 0.
 * If two nodes u and v will be in conflict if either one of them is flipped (their top/bottom soliders swap),
 * then they have an edge between them of weight 1.
 * Don't include self-edges.
 *
 * Let's make a few observations:
 * - The maximum number of soldiers with height x is 2, since any more and it is impossible to solve the problem.
 * - Each node has zero, one, or two edges.
 * - The graph will have a lot of cycles and a lot of straight lines.
 * - We can solve each of the cycles/straight lines independently.
 * - By flipping a node, all the edges next to it will be flipped (if they are currently weight 0, they will
 * be weight 1, and vice versa).
 * - If it's a cycle, it will have an even number of edges with weight 0.
 *
 * Let's now figure out how to solve a straight line.
 * Let's first make a list of edge weights, e.g. 0 1 1 0 1 0 1
 * Note that one move = flip values of two adjacent edges.
 * Let's make a list of edge weights. We want to make flips s.t. all the edges have weight 1.
 * We can do this greedily, if the current node has weight 0, we flip the current node and the next node.
 * However there is another case to consider, we can flip the value of the very first edge only in one operation.
 *
 * Now how do we solve a cycle?
 * Similar to solving a straight line, but when we flip edge 0, we also flip edge n-1.
 *
 * Now we can solve all of the cycles/straight lines independently and add the moves up to get our final answer.
 *
 * My implementation is very messy, you can write far more elegant code.
 */

// #pragma GCC optimize ("O3")
// #pragma GCC target ("sse4")

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
}

using namespace input;

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prContain(const T& x) {
        pr("{");
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        pr("}");
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

/* ============================ */

int main() {
    setupIO();

    int n; re(n); assert(n <= 50000);
    int A[n], B[n]; reA(A, n); reA(B, n);
    vii loc[100001];
    F0R(i, n) {
        loc[A[i]].pb(mp(i, 0));
        loc[B[i]].pb(mp(i, 1));
    }
    F0R(i, 100001) assert(loc[i].size() <= 2);
    bool visited[50000]; SET(visited, false, 50000);
    int ans = 0;
    F0R(i, n) {
        if (visited[i]) continue;
        vector<bool> edges; // true = good, false = bad
        stack<ii> s;
        visited[i] = true;
        int a = A[i], b = B[i];
        trav(x, loc[a]) {
            if (x.pA == i) continue;
            if (!visited[x.pA]) {
                s.push(mp(x.pA, x.pB != 0));
            }
        }
        vector<bool> edges1;
        while (!s.empty()) {
            ii xx = s.top(); s.pop();
            edges1.pb(xx.pB);
            int cur = xx.pA;
            visited[cur] = true;
            int a = A[cur], b = B[cur];
            set<ii> toAdd;
            trav(x, loc[a]) {
                if (x.pA == cur) continue;
                if (!visited[x.pA]) {
                    toAdd.insert(mp(x.pA, x.pB != 0));
                }
            }
            trav(x, loc[b]) {
                if (x.pA == cur) continue;
                if (!visited[x.pA]) {
                    toAdd.insert(mp(x.pA, x.pB != 1));
                }
            }
            trav(x, toAdd) s.push(x);
        }
        bool cycle = false;
        vector<bool> edges2;
        trav(x, loc[b]) {
            if (x.pA == i) continue;
            if (!visited[x.pA]) {
                s.push(mp(x.pA, x.pB != 1));
                cycle = false;
            } else {
                cycle = true;
                edges2.pb(x.pB != 1);
            }
        }
        while (!s.empty()) {
            ii xx = s.top(); s.pop();
            edges2.pb(xx.pB);
            int cur = xx.pA;
            visited[cur] = true;
            int a = A[cur], b = B[cur];
            set<ii> toAdd;
            trav(x, loc[a]) {
                if (x.pA == cur) continue;
                if (!visited[x.pA]) {
                    toAdd.insert(mp(x.pA, x.pB != 0));
                }
            }
            trav(x, loc[b]) {
                if (x.pA == cur) continue;
                if (!visited[x.pA]) {
                    toAdd.insert(mp(x.pA, x.pB != 1));
                }
            }
            trav(x, toAdd) s.push(x);
        }
        F0Rd(i, sz(edges1)) edges.pb(edges1[i]);
        F0R(i, sz(edges2)) edges.pb(edges2[i]);
        int n = sz(edges);
        if (n == 1) {
            ans += !edges[0];
            continue;
        }
        int bestOp = INF;

        F0R(round, 2) {
            vector<bool> xx(edges);
            int op = 0;
            if (round == 1) {
                if (n < 2) continue;
                op = 1;
                if (cycle) {
                    edges[0] = !edges[0];
                    edges[n-1] = !edges[n-1];
                } else {
                    edges[0] = !edges[0];
                }
            }
            F0R(i, n) {
                if (cycle) {
                    if (!edges[i]) {
                        op++;
                        edges[i] = !edges[i];
                        edges[(i + 1) % n] = !edges[(i + 1) % n];
                    }
                } else {
                    if (!edges[i]) {
                        op++;
                        edges[i] = !edges[i];
                        if (i + 1 < n) edges[i + 1] = !edges[i + 1];
                    }
                }
            }
            F0R(i, n) {
                if (!edges[i]) {
                    ps("error");
                }
            }
            edges = xx;
            MIN(bestOp, op);
        }

        ans += bestOp;
    }
    ps(ans);

    return 0;
}