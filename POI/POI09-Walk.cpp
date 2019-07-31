/*
 * Same as editorial.
 *
 * We can solve this problem by running bfs on an implicit graph.
 *
 * Let's define a graph G with vertices (u, v, c) ==> u, v are in the set of crossings,
 * and c is in the set { a, b, c, ... x, y, z, # }.
 *
 * There is an edge from (u, v, #) to (u', v, c) if there is an edge from u to u' labeled c.
 * There is an edge from (u, v, c) to (u, v', #) if there is an edge from v' to v labeled c.
 *
 * From each node, we store the next node that minimizes the number of edges traveled. Note that 1 edge == 1 character.
 *
 * However, there might be cycles, so a recursive DP solution won't work here; instead, we must BFS
 * from the base case to all the other cases.
 *
 * The base case is when u == v, so we insert { x, x, c } ==> x = 1...n, c = a...# into the queue.
 * Then we "flip" the edges of G during our update, so we find all nodes that can transition to this node and update them.
 *
 * Finally, to answer a query to travel from node a to node b, we just follow the path
 * from (a, b, #) all the way to the base case.
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

int n, m;
vii children[400];
vii rChildren[400];

struct state {
    int a, b, c, v;
};

state nxt[400][400][27];
int main() {
    setupIO();

    re(n, m);
    F0R(i, m) {
        int a, b; char c; re(a, b, c);
        children[--a].pb({--b, c - 'a'});
        rChildren[b].pb({a, c - 'a'});
    }
    int d; re(d);
    int A[d]; reA(A, d);

    F0R(i, n) F0R(j, n) F0R(k, 27) nxt[i][j][k].v = INF;

    queue<state> q;
    F0R(i, n) {
        F0R(j, 27) {
            nxt[i][i][j] = { -1, -1, j, 0 };
            q.push({ i, i, j, 0 });
        }
    }

    while (!q.empty()) {
        state u = q.front(); q.pop();
        if (u.c == 26) {
            trav(x, children[u.b]) {
                if (nxt[u.a][x.pA][x.pB].v > u.v + 1) {
                    nxt[u.a][x.pA][x.pB] = { u.a, u.b, u.c, u.v + 1 };
                    q.push({ u.a, x.pA, x.pB, u.v + 1 });
                }
            }
        } else {
            trav(x, rChildren[u.a]) {
                if (x.pB == u.c) {
                    if (nxt[x.pA][u.b][26].v > u.v + 1) {
                        nxt[x.pA][u.b][26] = { u.a, u.b, u.c, u.v + 1 };
                        q.push({ x.pA, u.b, 26, u.v + 1 });
                    }
                }
            }
        }
    }

    FOR(i, 1, d) {
        int a = A[i - 1], b = A[i]; --a; --b;

        state x = nxt[a][b][26];
        if (x.v == INF) {
            ps(-1);
        } else {
            pr(x.v, " ");
            vector<char> print;
            char prv;
            while (x.a != -1) {
                if (x.c != 26) {
                    pr((char)('a' + x.c));
                    prv = 'a' + x.c;
                }
                if (x.c == 26) {
                    print.pb(prv);
                }
                x = nxt[x.a][x.b][x.c];
            }
            reverse(all(print));
            trav(x, print) pr(x);
            pr("\n");
        }
    }

    return 0;
}