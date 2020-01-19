/*
 * Ignore ingredients and shopping. Our new problem is: Given a graph with 25 nodes and up to 500 edges,
 * how many ways are there to start from node 1 and end at node 1 after T steps?
 *
 * Define ways[a][b] = # of ways to get from a to b with time x. Let's say that x = 4 right now.
 * In O(n^3) time, we can calculate ways[a][b] for all (a, b) for time x = 8:
 * - For every pair (a, b, c) of nodes, ways_8[a][c] += ways_4[a][b]*ways_4[b][c].
 *
 * Similarly we can get answer[a][b]; if (1 << bit) is set for T, then we do the above steps for answer[a][b] with ways_(1 << bit).
 *
 * To handle shopping, split each node into two nodes. To handle ingredients, use principle of inclusion exclusion.
 *
 * Supposedly a matrix exponentiation problem...
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

int n, m;
vector<pair<int, int>> adj[25];
const int mod = 5557;

ll t;

// can only use paths that are subsets of mask
int solve(int mask) {
    int ways[2*n+1][2*n+1]; SET2D(ways, 0, 2*n+1, 2*n+1);
    int ways2[2*n+1][2*n+1];
    int waysAns[2*n+1][2*n+1]; SET2D(waysAns, 0, 2*n+1, 2*n+1); F0R(i, n) waysAns[i][i] = 1;
    ways[2*n][2*n] = 1; // handles < t case
    F0R(bitPos, 30) {
        if (bitPos == 0) {
            F0R(i, 2*n) {
                if (i % 2 == 0) {
                    trav(v, adj[i/2]) {
                        ways[i][2*v.pA] = 1;
                        if (v.pA == 0) ways[i][2*n] = 1;
                        if ((mask | v.pB) == mask) {
                            ways[i][2*v.pA+1] = 1;
                        }
                    }
                } else {
                    ways[i][i-1] = 1;
                }
            }
            ways[1][2*n] = 1;
        } else {
            SET2D(ways2, 0, 2*n+1, 2*n+1);
            F0R(i, 2*n+1) {
                F0R(j, 2*n+1) {
                    F0R(k, 2*n+1) {
                        ways2[i][k] = (ways2[i][k] + ways[i][j]*ways[j][k]) % mod;
                    }
                }
            }
            F0R(i, 2*n+1) {
                F0R(j, 2*n+1) {
                    ways[i][j] = ways2[i][j];
                }
            }
        }

        if ((1 << bitPos) & t) {
            SET2D(ways2, 0, 2*n+1, 2*n+1);
            F0R(i, 2*n+1) {
                F0R(j, 2*n+1) {
                    F0R(k, 2*n+1) {
                        ways2[i][k] = (ways2[i][k] + waysAns[i][j]*ways[j][k]) % mod;
                    }
                }
            }
            F0R(i, 2*n+1) {
                F0R(j, 2*n+1) {
                    waysAns[i][j] = ways2[i][j];
                }
            }
        }
    }
    assert(ways[2*n][2*n] == 1);
    return waysAns[0][2*n];
}

int main() {
    setupIO();

    re(n, m);
    F0R(i, m) {
        int a, b; re(a, b); --a; --b;
        int mask = 0;
        string c; re(c);
        trav(x, c) {
            if (x == 'B') mask |= (1 << 3);
            else if (x == 'M') mask |= (1 << 2);
            else if (x == 'J') mask |= (1 << 1);
            else mask |= 1;
        }
        adj[a].pb({b,mask});
    }
    re(t);
    ll ans = 0;
    F0Rd(i, 1 << 4) {
        int mult = -1;
        if (__builtin_popcount(i) % 2 == 0) mult = 1;
        ans = (ans + mult*solve(i)) % mod;
    }
    ps((ans + mod) % mod);

    return 0;
}