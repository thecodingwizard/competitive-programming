/*
 * 1. Set all starting wires and logic elements to one.
 * 2. For every logic element that is zero, run a dfs to set all of its parents, its parents' parents, etc to zero as well
 * 3. Now, update the value of all of the elements given these changes.
 *
 * All of the above can be done in O(N^2) time. Any element that is currently zero must be zero.
 *
 * Next, we will loop through each of the logic elements that are currently set to one, and we will try
 * setting it to zero.
 * 1. Set the logic element to zero, and all of its parents, its parents' parents, etc
 * 2. Update the value of all of the other elements given these changes
 * 3. Check to see if there are any conflicts with the initial state given by the input. If so, then the logic
 *    element must be one. If not, then it can be either zero or one.
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
vi parents[20000];
int initState[20000];
int finalState[10000];
bool val[20000];
bool val2[20000];

bool canChange = true;
void setZero(int u) {
    if (!canChange) return;
    if (initState[u] == 1) {
        canChange = false;
        return;
    }
    val2[u] = false;
    trav(x, parents[u]) setZero(x);
}

void forceSetZero(int u) {
    val[u] = false;
    initState[u] = 0;
    trav(x, parents[u]) forceSetZero(x);
}

vi topo;
bool visited[20000];
void toposort(int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (int v : parents[u]) {
        toposort(v);
    }
    topo.pb(u);
}

int main() {
    setupIO();

    re(n, m);
    SET(initState, -1, 20000);
    F0R(i, m) {
        char c; re(c);
        if (c == '1') initState[i] = 1;
        else if (c == '0') initState[i] = 0;
        else initState[i] = -1;
    }
    F0R(i, m) {
        char c; re(c);
        int x; re(x); x--;
        if (c == 'x') x += 10000;

        re(c);
        int y; re(y); y--;
        if (c == 'x') y += 10000;
        parents[i].pb(x);
        parents[i].pb(y);
    }

    SET(val, true, 20000)
    F0R(i, m) {
        if (initState[i] == 0) {
            forceSetZero(i);
        }
    }

    SET(visited, false, 20000);
    F0R(i, m) {
        toposort(i);
    }
    trav(x, topo) {
        if (x >= 10000) continue;
        val[x] = 0;
        for (int k : parents[x]) {
            if (val[k] == 1) {
                val[x] = 1;
                break;
            }
        }
    }

    F0R(i, m) {
        canChange = true;
        if (val[i] == 1) {
            if (initState[i] == 1) {
                finalState[i] = 1;
                continue;
            }
            F0R(i, 20000) val2[i] = val[i];

            setZero(i);
            trav(x, topo) {
                if (x >= 10000) continue;
                val2[x] = 0;
                for (int k : parents[x]) {
                    if (val2[k] == 1) {
                        val2[x] = 1;
                    }
                }
                if (initState[x] != -1 && initState[x] != val2[x]) {
                    canChange = false;
                    break;
                }
            }
            if (canChange) {
                finalState[i] = -1;
            } else {
                finalState[i] = 1;
            }
        } else {
            finalState[i] = 0;
        }
    }

    F0R(i, m) {
        if (finalState[i] == -1) pr('?');
        else pr(finalState[i]);
    }

    return 0;
}