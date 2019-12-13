/*
 * Same solution as editorial
 *
 * - Don't calculate angles, the precision isn't good enough. Use long double + use cross products to sort points
 * - Sort all points by angle from A. Sweep in increasing angle. When we hit a point, update all the queries
 *   for the point's tribe
 * - The above will time out if there are a lot of queries of the form (a, tribe_thats_not_a). Therefore,
 *   if there are more than sqrt(Q) queries of the form (a, tribe_thats_not_a), then we instead process
 *   it as (tribe_thats_not_a, a), basically a reverse query. We will need a slightly different sweep
 *   algorithm in order to process these types of queries. In total there are two sweeps
 * - My implementation is pretty terrible oops
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

struct point { ld x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(ld _x, ld _y) : x(_x), y(_y) {}        // user-defined
    bool operator == (point other) const {
        return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); }
    bool operator <(const point &p) const {
        return x < p.x || (abs(x-p.x) < EPS && y < p.y); } };

struct vec { ld x, y;  // name: `vec' is different from STL vector
    vec(ld _x, ld _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x-a.x, b.y-a.y); }

ld cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    void adjust(int k, int v) {
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int n, m;
pair<point, int> A[30000];
pair<point, pair<int, int>> A2[30000];
pair<point, ii> B2[30000];
int bSweepIdx[30000];
int ct[30000];
int qryAns[100000];
point a, b;
vi dragonsByTribe[30000];
FenwickTree below(30000), above(30000);
FenwickTree below2(30000), above2(30000);

// returns true if x < y in angle sweep about point a
bool cmp(point x, point y, point a, point b) {
    bool isBelowX = ccw(b, a, x), isBelowY = ccw(b, a, y);
    if (isBelowX == isBelowY) {
        return ccw(a, x, y);
    } else if (isBelowX && !isBelowY) {
        return !ccw(x, y, a);
    } else {
        return ccw(y, x, a);
    }
}

int main() {
    setupIO();

    re(n, m); SET(ct, 0, m);
    F0R(i, n) {
        int a, b, c; re(a, b, c);
        A2[i] = B2[i] = {point(a, b), {c-1, i}};
        ct[c-1]++;
    }
    re(a.x, a.y, b.x, b.y);

    sort(A2, A2+n, [](const pair<point, ii> &x, const pair<point, ii> &y) {
        return cmp(x.pA, y.pA, a, b);
    });
    F0R(i, n) {
        A[i] = {A2[i].pA, A2[i].pB.pA};
    }

    F0R(i, n) {
        dragonsByTribe[A[i].pB].pb(i);
    }

    sort(B2, B2+n, [](const pair<point, ii> &x, const pair<point, ii> &y) {
        return cmp(x.pA, y.pA, b, a);
    });

    int mappedAIdx[n];
    F0R(i, n) mappedAIdx[A2[i].pB.pB] = i;
    F0R(i, n) bSweepIdx[mappedAIdx[B2[i].pB.pB]] = i;

    int q; re(q); int SQRT = sqrt(q);
    vii queries[m];
    vi queryAns[m];
    vii queries2[m];
    vi queryAns2[m];
    int queryCt[m]; SET(queryCt, 0, m);
    vii rawQueries;
    F0R(i, q) {
        int a, b; re(a, b); --a; --b;
        rawQueries.pb({a, b});
        queryCt[a]++;
    }
    F0R(i, sz(rawQueries)) {
        int a = rawQueries[i].pA, b = rawQueries[i].pB;
        if (queryCt[a] <= SQRT) {
            queries[a].pb({b,i});
            queryAns[a].pb(0);
        } else {
            queries2[b].pb({a,i});
            queryAns2[b].pb(0);
        }
    }

    sort(B2, B2+n, [](const pair<point, ii> &x, const pair<point, ii> &y) {
        if (x.pB.pA == y.pB.pA) return cmp(x.pA, y.pA, b, a);
        return x.pB.pA < y.pB.pA;
    });
    vii tribe_sweepIdx[m];
    int bSweepIdx2[n];
    F0R(i, n) {
        bSweepIdx2[mappedAIdx[B2[i].pB.pB]] = i;
        tribe_sweepIdx[B2[i].pB.pA].eb(bSweepIdx[mappedAIdx[B2[i].pB.pB]], i);
    }
    F0R(i, m) sort(all(tribe_sweepIdx[i]));


    // FIRST SWEEP //
    F0R(i, n) {
        if (ccw(b, a, A[i].pA)) {
            below.adjust(bSweepIdx2[i]+1, 1);
        }
    }
    F0R(x, n) {
        F0R(i, sz(queries[A[x].pB])) {
            int t2 = queries[A[x].pB][i].pA;

            if (sz(tribe_sweepIdx[t2]) != 0) {
                ii lo = *lb(all(tribe_sweepIdx[t2]), mp(-1, -1));
                ii mx = *tribe_sweepIdx[t2].rbegin();
                ii hi;
                auto it = lb(all(tribe_sweepIdx[t2]), mp(bSweepIdx[x], -1));
                if (it != tribe_sweepIdx[t2].end()) hi = *it;
                else {
                    hi = {0, mx.pB + 1};
                }

                queryAns[A[x].pB][i] += below.rsq(lo.pB + 1, hi.pB);
                queryAns[A[x].pB][i] += above.rsq(hi.pB + 1, mx.pB + 1);
            }
        }

        if (ccw(b, a, A[x].pA)) {
            below.adjust(bSweepIdx2[x]+1, -1);
        } else {
            above.adjust(bSweepIdx2[x]+1, 1);
        }
    }

    F0R(i, m) {
        F0R(j, sz(queries[i])) {
            qryAns[queries[i][j].pB] = queryAns[i][j];
        }
    }
    // END FIRST SWEEP //

    // SECOND SWEEP //
    F0R(i, n) {
        below2.adjust(bSweepIdx2[i]+1, 1);
    }
    F0R(x, n) {
        F0R(i, sz(queries2[A[x].pB])) {
            int t2 = queries2[A[x].pB][i].pA;

            if (sz(tribe_sweepIdx[t2]) != 0) {
                ii lo = *lb(all(tribe_sweepIdx[t2]), mp(-1, -1));
                ii mx = *tribe_sweepIdx[t2].rbegin();
                ii hi;
                auto it = lb(all(tribe_sweepIdx[t2]), mp(bSweepIdx[x], -1));
                if (it != tribe_sweepIdx[t2].end()) hi = *it;
                else {
                    hi = {0, mx.pB + 1};
                }

                if (!ccw(b, a, A[x].pA)) queryAns2[A[x].pB][i] += below2.rsq(lo.pB + 1, hi.pB);
                if (ccw(b, a, A[x].pA)) queryAns2[A[x].pB][i] += above2.rsq(hi.pB + 1, mx.pB + 1);
            }
        }

        below2.adjust(bSweepIdx2[x]+1, -1);
        above2.adjust(bSweepIdx2[x] + 1, 1);
    }

    F0R(i, m) {
        F0R(j, sz(queries2[i])) {
            qryAns[queries2[i][j].pB] = queryAns2[i][j];
        }
    }
    // END SECOND SWEEP

    F0R(i, q) ps(qryAns[i]);

    return 0;
}