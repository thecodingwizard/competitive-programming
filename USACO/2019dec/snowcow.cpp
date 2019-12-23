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

vi adj[MAXN];

vi nodeList;
int startLoc[MAXN], endLoc[MAXN]; // startLoc = location of i, endLoc = location of last element in i
void dfs(int u, int p) {
    startLoc[u] = sz(nodeList);
    nodeList.pb(u);
    trav(x, adj[u]) {
        if (x != p) dfs(x, u);
    }
    endLoc[u] = sz(nodeList) - 1;
}

int queryParent[MAXN]; // points to the parent query that will override this query

// BEGIN queryST //
int queryST[4*MAXN];
int queryLazy[4*MAXN];
void querySTDown(int p, int i, int j) {
    if (queryLazy[p] != INF) {
        queryST[p] = queryLazy[p];
        if (i != j) {
            queryLazy[p << 1] = queryLazy[p];
            queryLazy[(p << 1) + 1] = queryLazy[p];
        }
        queryLazy[p] = INF;
    }
}
int querySTQuery(int p, int i, int j, int k) {
    querySTDown(p, i, j);
    if (i == k && j == k) return queryST[p];
    int mid = (i+j)/2;
    if (mid+1 <= k) return querySTQuery((p << 1) + 1, mid+1, j, k);
    return querySTQuery(p << 1, i, mid, k);
}
void querySTUpd(int p, int i, int j, int l, int r, int v) {
    querySTDown(p, i, j);
    if (i > r || j < l) return;
    if (l <= i && j <= r) {
        queryLazy[p] = v;
        return;
    }
    querySTUpd((p << 1), i, (i+j)/2, l, r, v);
    querySTUpd((p << 1) + 1, (i+j)/2+1, j, l, r, v);
}
// END queryST //

// START regular ST //
ll st[4*MAXN];
ll lazy[4*MAXN];
void down(int p, int i, int j) {
    if (lazy[p] != 0) {
        st[p] += lazy[p]*(j-i+1);
        if (i != j) {
            lazy[p << 1] += lazy[p];
            lazy[(p << 1) + 1] += lazy[p];
        }
        lazy[p] = 0;
    }
}
ll query(int p, int i, int j, int l, int r) {
    down(p, i, j);
    if (l > j || r < i) return 0;
    if (l <= i && j <= r) return st[p];
    return query(p << 1, i, (i+j)/2, l, r) + query((p << 1) + 1, (i+j)/2+1, j, l, r);
}
void upd(int p, int i, int j, int l, int r, int v) {
    down(p, i, j);
    if (l > j || r < i) return;
    if (l <= i && j <= r) {
        lazy[p] += v;
        return;
    }
    upd(p << 1, i, (i+j)/2, l, r, v);
    upd((p << 1) + 1, (i+j)/2+1, j, l, r, v);
    down(p << 1, i, (i+j)/2);
    down((p << 1) + 1, (i+j)/2+1, j);
    st[p] = st[p << 1] + st[(p << 1) + 1];
}
// END regular ST //

int main() {
    setupIO("snowcow");

    int n, q; re(n, q);
    F0R(i, n-1) {
        int a, b; re(a, b);
        adj[--a].pb(--b);
        adj[b].pb(a);
    }
    dfs(0, 0);

    vii queries;
    vi queriesOfColor[MAXN];
    F0R(i, q) {
        int t; re(t);
        if (t == 1) {
            int x, c; re(x, c);
            queries.pb({x-1, c-1});
            queriesOfColor[c-1].pb(i);
        } else {
            int x; re(x);
            queries.pb({x-1, -1});
        }
    }

    // Step 0.5: remove useless queries
    bool uselessQuery[MAXN]; SET(uselessQuery, false, MAXN);
    SET(queryLazy, INF, MAXN);
    F0R(c, MAXN) {
        if (sz(queriesOfColor[c])) {
            querySTUpd(1, 0, MAXN-1, startLoc[0], endLoc[0], -1);
        }
        F0R(i, sz(queriesOfColor[c])) {
            int qryIdx = queriesOfColor[c][i];
            int qryNode = queries[qryIdx].pA;
            int queryAtNode = querySTQuery(1, 0, MAXN-1, startLoc[qryNode]);
            if (queryAtNode != -1) {
                uselessQuery[qryIdx] = true;
            }
            querySTUpd(1, 0, MAXN-1, startLoc[qryNode], endLoc[qryNode], qryIdx);
        }
    }

    // Step 1: Find "parent" query
    vi childrenQueries[MAXN];
    F0R(c, MAXN) {
        if (sz(queriesOfColor[c])) {
            querySTUpd(1, 0, MAXN-1, startLoc[0], endLoc[0], -1);
        }
        F0Rd(i, sz(queriesOfColor[c])) {
            int qryIdx = queriesOfColor[c][i];
            if (uselessQuery[qryIdx]) continue;
            int qryNode = queries[qryIdx].pA;
            queryParent[qryIdx] = querySTQuery(1, 0, MAXN-1, startLoc[qryNode]);
            if (queryParent[qryIdx] != -1) {
                childrenQueries[queryParent[qryIdx]].pb(qryIdx);
            }
            querySTUpd(1, 0, MAXN-1, startLoc[qryNode], endLoc[qryNode], qryIdx);
        }
    }

    // Step 2: Process them queries
    SET(st, 0, MAXN*4);
    SET(lazy, 0, MAXN*4);
    F0R(i, q) {
        if (uselessQuery[i]) continue;

        ii qry = queries[i];
        if (qry.pB == -1) {
            // query type 2
            ll res = query(1, 0, MAXN-1, startLoc[qry.pA], endLoc[qry.pA]);
            ps(res);
        } else {
            // query type 1
            trav(qryIdx, childrenQueries[i]) {
                ii qryToRemove = queries[qryIdx];
                upd(1, 0, MAXN-1, startLoc[qryToRemove.pA], endLoc[qryToRemove.pA], -1);
            }
            upd(1, 0, MAXN-1, startLoc[qry.pA], endLoc[qry.pA], 1);
        }
    }

    return 0;
}