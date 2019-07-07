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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

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

/* ============================ */

map<ii, int> roadIdx;
struct City {
    int x, y; int rIdxOne, rIdxTwo;
};

vector<City> cities;

vi children[200000];

struct Road {
    int a, b; int depth;
};
vector<Road> roads;

int parent[200000][18];
double dist[200000][18][2][2];

double gd(int a, int b) {
    City A = cities[a], B = cities[b];
    return hypot(B.y - A.y, B.x - A.x);
}

double cd(int ridx) {
    City a = cities[roads[ridx].a], b = cities[roads[ridx].b];
    return hypot(b.y - a.y, b.x - a.x);
}

void setParent(int rId) {
    int p = parent[rId][0];
    dist[rId][0][0][0] = 0;
    dist[rId][0][0][1] = cd(p);
    dist[rId][0][1][0] = gd(roads[rId].b, roads[p].a);
    dist[rId][0][1][1] = gd(roads[rId].b, roads[p].b);
    FOR(i, 1, 18) {
        dist[rId][i][0][0] = min(dist[rId][i - 1][0][0] + dist[p][i - 1][0][0], dist[rId][i - 1][0][1] + dist[p][i - 1][1][0]);
        dist[rId][i][0][1] = min(dist[rId][i - 1][0][0] + dist[p][i - 1][0][1], dist[rId][i - 1][0][1] + dist[p][i - 1][1][1]);
        dist[rId][i][1][0] = min(dist[rId][i - 1][1][0] + dist[p][i - 1][0][0], dist[rId][i - 1][1][1] + dist[p][i - 1][1][0]);
        dist[rId][i][1][1] = min(dist[rId][i - 1][1][0] + dist[p][i - 1][0][1], dist[rId][i - 1][1][1] + dist[p][i - 1][1][1]);
        parent[rId][i] = p = parent[p][i - 1];
    }
}

double getDist(int r1, int r2) {
    // return distance from road r1 to road r2
    if (roads[r1].depth < roads[r2].depth) {
        int tmp = r2;
        r2 = r1;
        r1 = tmp;
    }
    pair<double, double> d1 = { cd(r1), 0 };
    pair<double, double> d2 = { cd(r2), 0 };
    F0Rd(i, 18) {
        int par = parent[r1][i];
        if (roads[par].depth >= roads[r2].depth) {
            pair<double, double> nd1;
            nd1.pA = min(dist[r1][i][0][0] + d1.pA, dist[r1][i][1][0] + d1.pB);
            nd1.pB = min(dist[r1][i][0][1] + d1.pA, dist[r1][i][1][1] + d1.pB);
            d1 = nd1;
            r1 = par;
        }
    }
    F0Rd(i, 18) {
        int p1 = parent[r1][i], p2 = parent[r2][i];
        if (p1 != p2) {
            pair<double, double> nd1;
            nd1.pA = min(dist[r1][i][0][0] + d1.pA, dist[r1][i][1][0] + d1.pB);
            nd1.pB = min(dist[r1][i][0][1] + d1.pA, dist[r1][i][1][1] + d1.pB);
            d1 = nd1;
            r1 = p1;
            pair<double, double> nd2;
            nd2.pA = min(dist[r2][i][0][0] + d2.pA, dist[r2][i][1][0] + d2.pB);
            nd2.pB = min(dist[r2][i][0][1] + d2.pA, dist[r2][i][1][1] + d2.pB);
            d2 = nd2;
            r2 = p2;
        }
    }
    return d1.pB + d2.pB + gd(roads[r1].b, roads[r2].b);
}

int main() {
    setupIO();
    cout << fixed << setprecision(6);

    int x1, y1, x2, y2; re(x1, y1, x2, y2);
    cities.pb(City{x1, y1, 0, 0}); cities.pb(City{x2, y2, 0, 0});
    roadIdx[mp(0, 1)] = 0;
    parent[0][0] = 0;
    setParent(0);
    int n; re(n);
    F0R(i, n) {
        char cmd; re(cmd);
        if (cmd == 'd') {
            int x, y, a, b; re(x, y, a, b); a--; b--;
            int par = roadIdx[mp(min(a, b), max(a, b))];
            int rsz = sz(roadIdx);
            children[par].pb(rsz); roadIdx[mp(a, sz(cities))] = rsz;
            children[par].pb(rsz + 1); roadIdx[mp(b, sz(cities))] = rsz + 1;
            roads.pb(Road{a, sz(cities), roads[par].depth + 1});
            roads.pb(Road{b, sz(cities), roads[par].depth + 1});
            cities.pb(City{x, y, rsz, rsz + 1});
            parent[rsz][0] = par;
            parent[rsz + 1][0] = par;
            setParent(rsz); setParent(rsz + 1);
        } else {
            int a, b; re(a, b); a--; b--;
            double best = LL_INF;
            MIN(best, getDist(cities[a].rIdxOne, cities[b].rIdxOne));
            MIN(best, getDist(cities[a].rIdxTwo, cities[b].rIdxOne));
            MIN(best, getDist(cities[a].rIdxOne, cities[b].rIdxTwo));
            MIN(best, getDist(cities[a].rIdxTwo, cities[b].rIdxTwo));
            ps(best);
        }
    }

    return 0;
}