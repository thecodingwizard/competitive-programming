/*
 * Same solution as editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2007/editorial.pdf
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
vi adj[1000];
vi adj2[1000];
int pos[1000][1000];
vi edgeCost[1000];
vi memoDPVal[1000];
vector<vi> edgeLeft[1000], edgeRight[1000];

int color[1000];
int depth[1000];
int pa[1000][10];

int dfs(int u, int p, int d) {
    pa[u][0] = p;
    depth[u] = d;
    color[u] = d % 2;
    trav(x, adj2[u]) {
        if (x == p) continue;
        adj[u].pb(x);
        dfs(x, u, d+1);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) return lca(b, a);
    F0Rd(i, 10) {
        if (depth[pa[a][i]] >= depth[b]) {
            a = pa[a][i];
        }
    }
    if (a == b) return a;
    F0Rd(i, 10) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    return pa[a][0];
}

int memo[1000][(1 << 10)];
int dp(int n, int mask) {
    if (memo[n][mask] != -1) return memo[n][mask];
    int best = 0;

    F0R(i, sz(adj[n])) {
        if (mask & (1 << i)) continue;
        best += dp(adj[n][i], 0);
    }

    F0R(i, sz(edgeLeft[n])) {
        vi &l = edgeLeft[n][i], &r = edgeRight[n][i];
        int newMask = mask;
        if (sz(l)) {
            if (mask & (1 << pos[n][l.back()])) continue;
            newMask |= (1 << pos[n][l.back()]);
        }
        if (sz(r)) {
            if (mask & (1 << pos[n][r.back()])) continue;
            newMask |= (1 << pos[n][r.back()]);
        }

        int thisOne = edgeCost[n][i];
        if (memoDPVal[n][i] != -1) {
            thisOne = memoDPVal[n][i];
        } else {
            F0R(j, sz(l)) {
                int m = 0;
                if (j != 0) {
                    m |= (1 << pos[l[j]][l[j - 1]]);
                }
                thisOne += dp(l[j], m);
            }
            F0R(j, sz(r)) {
                int m = 0;
                if (j != 0) {
                    m |= (1 << pos[r[j]][r[j - 1]]);
                }
                thisOne += dp(r[j], m);
            }
            memoDPVal[n][i] = thisOne;
        }

        thisOne += dp(n, newMask);
        MAX(best, thisOne);
    }

    return memo[n][mask] = best;
}

int main() {
    setupIO();

    re(n, m);
    int totCost = 0;
    vii edgeNodes;
    vi edgeCosts;
    F0R(i, m) {
        int a, b, c;
        re(a, b, c);

        if (c == 0) {
            adj2[--a].pb(--b);
            adj2[b].pb(a);
        } else {
            a--;
            b--;
            edgeNodes.pb({a, b});
            edgeCosts.pb(c);
            totCost += c;
        }
    }

    dfs(0, 0, 0);
    FOR(i, 1, 10) {
        F0R(j, n) {
            pa[j][i] = pa[pa[j][i-1]][i-1];
        }
    }

    F0R(i, sz(edgeNodes)) {
        ii x = edgeNodes[i];
        if (color[x.pA] != color[x.pB]) continue;
        int top = lca(x.pA, x.pB);
        edgeLeft[top].pb(vi());
        edgeRight[top].pb(vi());
        int a = x.pA;
        while (a != top) {
            edgeLeft[top].back().pb(a); a = pa[a][0];
        }

        a = x.pB;
        while (a != top) {
            edgeRight[top].back().pb(a); a = pa[a][0];
        }

        edgeCost[top].pb(edgeCosts[i]);
        memoDPVal[top].pb(-1);
    }

    F0R(i, n) {
        F0R(j, sz(adj[i])) {
            pos[i][adj[i][j]] = j;
        }
    }

    SET2D(memo, -1, 1000, (1 << 10));
    ps(totCost - dp(0, 0));

    return 0;
}
