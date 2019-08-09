/*
 * Same ideas as editorial.
 *
 * Process the tiles in decreasing order of height. Maintain a union find data structure. Union adjacent tiles that
 * have already been "processed" (eg. the height of neighbor tile is >= the height of the tile currently being processed)
 *
 * For each union set, keep track of its highest "peak" and the number of times that peak occurs. When merging
 * two sets A, B:
 * - If max peak height of A < max peak height of B: for every max peak in A, the min cost is the cost of the tile
 * that was just processed.
 * - Likewise for B > A
 * - If A == B, then update the number of times the max peak occurs
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
int A[2000][2000];
bool active[2000][2000];
int size[100000];
int p[100000];
int mx[100000];
int peak[100000];
int isPeak[2000][2000];
map<int, vii> nodes;
vii ans;
int dx[8] = { 1, 1, 1, -1, -1, -1, 0, 0 };
int dy[8] = { 0, 1, -1, 0, 1, -1, 1, -1 };

int enc(ii x) {
    return x.pA*m + x.pB;
}

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void merge(int x, int y, int c) {
    int a = find(x), b = find(y);
    if (a == b) return;
    if (size[a] > size[b]) {
        return merge(b, a, c);
    }
    size[b] += size[a];
    p[a] = b;


    if (mx[a] > mx[b]) {
        F0R(i, peak[b]) ans.pb(mp(mx[b], c));
        peak[b] = peak[a];
    } else if (mx[b] > mx[a]) {
        F0R(i, peak[a]) ans.pb(mp(mx[a], c));
    } else {
        peak[b] += peak[a];
    }
    MAX(mx[b], mx[a]);
}

int main() {
    setupIO();

    re(n, m);
    F0R(i, n) reA(A[i], m);
    int mxVal = 0;
    F0R(i, n) {
        F0R(j, m) {
            nodes[A[i][j]].pb(mp(i, j));
            mx[enc({ i, j })] = A[i][j];
            MAX(mxVal, A[i][j]);
        }
    }

    // Calculating peaks
    SET2D(isPeak, -1, n, m);
    F0R(i, n) {
        F0R(j, m) {
            if (isPeak[i][j] != -1) continue;
            queue<ii> search; search.push(mp(i, j));
            set<ii> final;
            while (!search.empty()) {
                ii u = search.front(); search.pop();
                if (final.count(u)) continue;
                final.insert(u);
                F0R(i, 8) {
                    ii y = { u.pA + dx[i], u.pB + dy[i] };
                    if (y.pA >= 0 && y.pA < n && y.pB >= 0 && y.pB < m) {
                        if (A[y.pA][y.pB] == A[u.pA][u.pB]) search.push(y);
                    }
                }
            }
            isPeak[i][j] = 1;
            trav(x, final) {
                if (x.pA == i && x.pB == j) {}
                else isPeak[x.pA][x.pB] = 0;
                F0R(aa, 8) {
                    ii y = {x.pA + dx[aa], x.pB + dy[aa]};
                    if (y.pA >= 0 && y.pA < n && y.pB >= 0 && y.pB < m) {
                        if (A[y.pA][y.pB] > A[x.pA][x.pB]) isPeak[i][j] = 0;
                    }
                }
            }
            if (A[i][j] == mxVal) {
                ans.pb(mp(mxVal, 0));
            }
        }
    }
    F0R(i, n) {
        F0R(j, m) {
            peak[enc({ i, j })] = isPeak[i][j];
        }
    }
    // End calculating peaks

    SET2D(active, false, n, m);
    SET(size, 1, n*m);
    F0R(i, n*m) p[i] = i;
    auto it = nodes.rbegin();
    while (it != nodes.rend()) {
        trav(x, it->pB) {
            active[x.pA][x.pB] = true;
            F0R(i, 8) {
                ii y = { x.pA + dx[i], x.pB + dy[i] };
                if (y.pA >= 0 && y.pA < n && y.pB >= 0 && y.pB < m) {
                    if (active[y.pA][y.pB]) {
                        merge(enc(x), enc(y), A[x.pA][x.pB]);
                    }
                }
            }
        }
        it++;
    }
    ps(sz(ans));
    RSORT(ans);
    trav(x, ans) ps(x);

    return 0;
}