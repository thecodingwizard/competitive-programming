/*
 * The minimum is n-1 (alternate edge directions).
 *
 * In the maximum arrangement, there will be some center vertex as the root. All its subtrees will
 * be partitioned into two sets. All nodes in the first set will be pointing towards the center vertex,
 * and all nodes in the second set will be pointing away from the center vertex.
 *
 * Define A = size(first set), B = size(second set). The answer for this partition will 
 * be A*B + (paths in the subtrees) + (paths involving the center vertex = A+B)
 * The optimal maximum arrangement will have the smallest abs(A - B).
 *
 * We try every center vertex. If one of its subtrees has size >= n/2, then we make that one partition and
 * all its other subtrees another partition.
 *
 * If none of its subtrees has size >= n/2, then we use knapsack to find a partition with smallest abs(A-B).
 * A normal knapsack will TLE, but we can optimize: Note that the maximum number of subtrees of different
 * sizes is sqrt(N). Our knapsack is only too slow when there are a large number of identical subtree sizes.
 *
 * We can optimize this by grouping subtrees with the same sizes. For example, if there are lots of
 * subtrees of size x, we group them into (x, 2x, 4x, 8x, 16x, ... etc). This way we can reduce
 * the number of items we have to process in our knapsack.
 *
 * You can also optimize knapsack time by using a bitset
 * ```
 * bitset<N> dp;
 * int item = 3;
 * dp |= (dp << item);
 * ```
 * But this MLE for me.
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

int n;
vi adj[250000];
int sz[250000];
ll val[250000];

int dfsSz(int u, int p) {
    sz[u] = 1;
    val[u] = 0;
    trav(v, adj[u]) {
        if (v != p) {
            int s = dfsSz(v, u);
            sz[u] += s;
            val[u] += s + val[v];
        }
    }
    return sz[u];
}

ll dfs(int u, int p, int parentSize, ll parentVal) {
    ll best = 0;
    vi rawChildren; if (parentSize > 0) rawChildren.pb(parentSize);
    trav(v, adj[u]) {
        if (v == p) continue;
        rawChildren.pb(sz[v]);
    }
    if (sz(rawChildren) == 0) return 0;
    int mx = 0; trav(v, rawChildren) MAX(mx, v);
    if (mx >= n/2) {
        ll x = mx;
        MAX(best, x*(n-x-1) + val[u] + parentVal);
    } else {
        sort(all(rawChildren));

        vi children;
        for (int i = 0; i < sz(rawChildren);) {
            int ct = 0;
            while (i + ct < sz(rawChildren) && rawChildren[i] == rawChildren[i + ct]) ct++;
            
            int ct2 = ct;
            for (int j = 1; ct >= j; j *= 2) {
                children.pb(rawChildren[i] * j);
                ct -= j;
            }
            if (ct > 0) children.pb(rawChildren[i] * ct);

            i += ct2;
        }

        vi nums; nums.assign(n, 0);
        nums[0] = true;
        trav(v, children) {
            F0Rd(i, n/2+1) {
                if (nums[i]) nums[i + v] = true;
            }
        }

        F0R(i, n) {
            if (nums[i] == true) {
                ll x = i;
                MAX(best, x*(n-x-1) + val[u] + parentVal);
            }
        }
    }

    trav(v, adj[u]) {
        if (v != p) {
            MAX(best, dfs(v, u, parentSize + sz[u] - sz[v], parentVal + val[u] - val[v] + n - sz[v] - sz[v]));
        }
    }
    return best;
}

int main() {
    setupIO();

    re(n);
    F0R(i, n-1) {
        int a, b; re(a, b);
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }

    dfsSz(0, 0);
    ps(n-1, dfs(0, 0, 0, 0));

    return 0;
}
