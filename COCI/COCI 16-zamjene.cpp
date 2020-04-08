/*
 * Same solution as editorial
 *
 * You can hash a set of numbers as c_1*H^(n_1) + c_2*H(n_2) etc if the numbers (n_1, n_2, ...) appear (c_1, c_2, ...) times
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

int n, q;
vi A;
vi B;
int numUnsorted;
ll qryFour = 0;

ll H = 7261523;
vl powH;
vl values;
vl indices;
map<ll, int> ct;
vi pa;
vi sz;

ll getQryFourCt(int i) {
    if (values[i] == indices[i]) return 0;
    return (ll)ct[-(values[i] - indices[i])]*sz[i];
}

int find(int x) {
    if (pa[x] == x) return x;
    return pa[x] = find(pa[x]);
}

void unionSet(int a, int b) {
    if (a == b) return;
    if (sz[a] > sz[b]) return unionSet(b, a);
    if (values[a] != indices[a]) numUnsorted -= sz[a];
    if (values[b] != indices[b]) numUnsorted -= sz[b];

    qryFour -= getQryFourCt(a);
    ct[values[a]-indices[a]]-=sz[a];
    qryFour -= getQryFourCt(b);
    ct[values[b]-indices[b]]-=sz[b];

    pa[a] = b;
    sz[b] += sz[a];
    values[b] = values[a] + values[b];
    indices[b] = indices[a] + indices[b];

    if (values[b] != indices[b]) numUnsorted += sz[b];

    qryFour += getQryFourCt(b);
    ct[values[b]-indices[b]]+=sz[b];
}

int main() {
    setupIO();

    re(n, q);
    A.resz(n); re(A);
    F0R(i, n) A[i]--;
    F0R(i, n) {
        B.pb(A[i]);
    }
    sort(all(B));
    numUnsorted = n;
    powH.resz(n);
    powH[0] = H;
    FOR(i, 1, n) {
        powH[i] = powH[i-1]*H;
    }

    pa.resz(n); sz.resz(n);
    values.resz(n); indices.resz(n);
    F0R(i, n) {
        pa[i] = i;
        sz[i] = 1;
        values[i] = powH[A[i]];
        indices[i] = powH[B[i]];
        if (values[i] == indices[i]) numUnsorted--;
        qryFour += getQryFourCt(i);
        ct[values[i] - indices[i]]++;
    }
    F0R(i, q) {
        int cmd; re(cmd);
        if (cmd == 1) {
            int a, b; re(a, b); --a; --b;
            int x = find(a), y = find(b);
            if (x == y) {
                swap(A[a], A[b]);
                continue;
            }

            if (values[x] != indices[x]) numUnsorted -= sz[x];
            if (values[y] != indices[y]) numUnsorted -= sz[y];
            
            qryFour -= getQryFourCt(x);
            ct[values[x] - indices[x]]-=sz[x];
            qryFour -= getQryFourCt(y);
            ct[values[y] - indices[y]]-=sz[y];

            values[x] = values[x] - powH[A[a]] + powH[A[b]];
            values[y] = values[y] - powH[A[b]] + powH[A[a]];

            swap(A[a], A[b]);

            if (values[x] != indices[x]) numUnsorted += sz[x];
            if (values[y] != indices[y]) numUnsorted += sz[y];

            qryFour += getQryFourCt(x);
            ct[values[x] - indices[x]]+=sz[x];
            qryFour += getQryFourCt(y);
            ct[values[y] - indices[y]]+=sz[y];
        } else if (cmd == 2) {
            int a, b; re(a, b); --a; --b;
            int x = find(a), y = find(b);
            unionSet(x, y);
        } else if (cmd == 3) {
            ps(numUnsorted == 0 ? "DA" : "NE");
        } else {
            ps(qryFour);
        }
    }

    return 0;
}



























