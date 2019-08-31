/*
 * Same as editorial.
 *
 * First, construct a binary tree from the input data. From each node, going right = 1, going left = 0.
 * Leaves = code word. Going from root node to the leaf = one code word.
 *
 * Note that since the prefix of the message may be cut off, the message is really some suffix of a word,
 * followed by 0+ complete words. Imagine a "decoder": It starts at the root node. As it reads in the message,
 * it goes left if it reads a 0, and right if it reads a 1. If the message is not corrupted, at the end of every word,
 * it will reach a leaf node and move back to the root node.
 *
 * Define the set of "important vertices" as vertices in the binary tree that the decoder can end up in if the
 * decoder reads a suffix of a word, followed by 0+ complete words. Note that for a word to be "synchronizing,"
 * for every vertex in the set of "important vertices," if the decoder starts at that vertex and reads a synchronizing
 * word, it will always end up at the root node.
 *
 * To find the set of important vertices, we do two steps: First, we find the set of "very important" vertices,
 * or vertices that can be reached if the decoder starts at the root node and reads some suffix of a word. (dfs1)
 * Then, we find the set of "important" vertices -- we initialize the set to contain all "very important" vertices.
 * Then for every vertex in the set of important vertices, we run dfs2.
 *
 * After finding the set of "important" vertices, we run a final dfs3 to determine all the synchronizing words.
 *
 * The explanation and pseudocode of dfs1, dfs2, and dfs3 can be found in the editorial.
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

int n;
bool leaf[3000000], important[3000000];
int L[3000000], R[3000000];
bool visited[3000000];
bool synchronizing[3000000];
int id[3000000];
queue<int> nodesToProcess;

void dfs1(int x, int y) {
    if (leaf[x]) return;
    if (leaf[y]) {
        important[x] = true;
    } else {
        dfs1(L[x], L[y]);
        dfs1(R[x], R[y]);
    }
}

void dfs2(int x, int y) {
    if (leaf[x]) {
        return dfs2(0, y);
    } else {
        if (x == 0) {
            if (visited[y]) return;
            visited[y] = true;
        }
        if (leaf[y]) {
            if (!important[x]) {
                important[x] = true;
                nodesToProcess.push(x);
            }
        } else {
            dfs2(L[x], L[y]);
            dfs2(R[x], R[y]);
        }
    }
}

void dfs3(int x, int y) {
    if (leaf[y]) {
        if (!leaf[x]) {
            synchronizing[y] = false;
        }
    } else {
        if (leaf[x]) {
            if (visited[y]) return;
            visited[y] = true;
            dfs3(0, y);
        } else {
            dfs3(L[x], L[y]);
            dfs3(R[x], R[y]);
        }
    }
}

int main() {
    setupIO();

    re(n);
    vi S; S.pb(0);
    int idx = 1;
    SET(leaf, false, n);
    SET(important, false, n);
    SET(visited, false, n);
    SET(synchronizing, true, n);
    important[0] = true;
    int ctr = 1;
    F0R(i, n) {
        char c; re(c);
        if (c == 'B') {
            S.pop_back();
        } else if (c == 'X') {
            leaf[S.back()] = true;
            id[S.back()] = ctr++;
        } else {
            if (c == '1') {
                R[S.back()] = idx;
            } else {
                L[S.back()] = idx;
            }
            S.pb(idx);
            idx++;
        }
    }

    F0R(i, idx) {
        dfs1(0, i);
    }

    F0R(i, idx) {
        if (!leaf[i] && important[i]) nodesToProcess.push(i);
    }

    while (!nodesToProcess.empty()) {
        int u = nodesToProcess.front(); nodesToProcess.pop();
        dfs2(u, 0);
    }

    SET(visited, false, n);
    F0R(i, idx) {
        if (important[i] && !leaf[i]) dfs3(i, 0);
    }

    vi ans;
    F0R(i, idx) {
        if (leaf[i] && synchronizing[i]) ans.pb(i);
    }
    ps(sz(ans));
    trav(x, ans) ps(id[x]);
}