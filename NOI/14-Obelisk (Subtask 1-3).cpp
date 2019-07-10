/*
 * Note that your state can uniquely be defined as (x, y, orientation, floor)
 *
 * You can do a BFS from source to destination. However, this is too slow for subtask 3.
 *
 * The trick is to recognize that the distance from (1, 2) to (3, 4) is the same for each floor, so you only have
 * to run a single BFS from (0, 0) to all the other nodes. Make sure to give some padding (eg. allow negative
 * coordinates, allow >400 coordinates).
 *
 * Then you can run Dijkstra from each hole to the next hole.
 *
 * Why is this the case? After all, when moving from (1, 2) to (3, 4) you may encounter a hole that
 * doesn't exist in another floor. However, this doesn't actually matter because when encountering
 * that hole, you just drop down to the next floor and continue your same sequence of movements, and
 * you end up at (3, 4) in the same number of moves, just on the floor beneath you, so it doesn't really matter.
 *
 * Note that m = 1 is a special case and should be handled differently (orientation doesn't matter)
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
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

// Source: Benq (https://github.com/bqi343/USACO) [Modified]
namespace input {
    template<class T>
    void re(complex<T> &x);

    template<class T1, class T2>
    void re(pair<T1, T2> &p);

    template<class T>
    void re(vector<T> &a);

    template<class T, size_t SZ>
    void re(array<T, SZ> &a);

    template<class T>
    void reA(T A[], int sz);

    template<class T>
    void re(T &x) { cin >> x; }

    void re(double &x) {
        string t;
        re(t);
        x = stod(t);
    }

    void re(ld &x) {
        string t;
        re(t);
        x = stold(t);
    }

    template<class Arg, class... Args>
    void re(Arg &first, Args &... rest) {
        re(first);
        re(rest...);
    }

    template<class T1, class T2>
    void re(pair<T1, T2> &p) { re(p.pA, p.pB); }

    template<class T>
    void re(vector<T> &a) { F0R(i, sz(a)) re(a[i]); }

    template<class T, size_t SZ>
    void re(array<T, SZ> &a) { F0R(i, SZ) re(a[i]); }

    template<class T>
    void reA(T A[], int sz) { F0R(i, sz) re(A[i]); }

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
    template<class T1, class T2>
    void prD(const pair<T1, T2> &x);

    template<class T, size_t SZ>
    void prD(const array<T, SZ> &x);

    template<class T>
    void prD(const vector<T> &x);

    template<class T>
    void prD(const set<T> &x);

    template<class T1, class T2>
    void prD(const map<T1, T2> &x);

    template<class T1, class T2>
    void pr(const pair<T1, T2> &x);

    template<class T, size_t SZ>
    void pr(const array<T, SZ> &x);

    template<class T>
    void pr(const vector<T> &x);

    template<class T>
    void pr(const set<T> &x);

    template<class T1, class T2>
    void pr(const map<T1, T2> &x);

    template<class T>
    void prD(const T &x) { cout << x; }

    template<class Arg, class... Args>
    void prD(const Arg &first, const Args &... rest) {
        prD(first);
        prD(rest...);
    }

    template<class T1, class T2>
    void prD(const pair<T1, T2> &x) {
        prD("{", x.pA, ", ", x.pB, "}");
    }

    template<class T>
    void prDContain(const T &x) {
        prD("{");
        bool fst = 1;
        for (const auto &a: x) prD(!fst ? ", " : "", a), fst = 0; // const needed for vector<bool>
        prD("}");
    }

    template<class T, size_t SZ>
    void prD(const array<T, SZ> &x) { prDContain(x); }

    template<class T>
    void prD(const vector<T> &x) { prDContain(x); }

    template<class T>
    void prD(const set<T> &x) { prDContain(x); }

    template<class T1, class T2>
    void prD(const map<T1, T2> &x) { prDContain(x); }

    void psD() { prD("\n"); }

    template<class Arg>
    void psD(const Arg &first) {
        prD(first);
        psD(); // no space at end of line
    }

    template<class Arg, class... Args>
    void psD(const Arg &first, const Args &... rest) {
        prD(first, " ");
        psD(rest...); // print w/ spaces
    }


    template<class T>
    void pr(const T &x) { cout << x; }

    template<class Arg, class... Args>
    void pr(const Arg &first, const Args &... rest) {
        pr(first);
        pr(rest...);
    }

    template<class T1, class T2>
    void pr(const pair<T1, T2> &x) {
        pr(x.pA, " ", x.pB);
    }

    template<class T>
    void prContain(const T &x) {
        bool fst = 1;
        for (const auto &a: x) pr(!fst ? " " : "", a), fst = 0; // const needed for vector<bool>
    }

    template<class T, size_t SZ>
    void pr(const array<T, SZ> &x) { prContain(x); }

    template<class T>
    void pr(const vector<T> &x) { prContain(x); }

    template<class T>
    void pr(const set<T> &x) { prContain(x); }

    template<class T1, class T2>
    void pr(const map<T1, T2> &x) { prContain(x); }

    void ps() { pr("\n"); }

    template<class Arg>
    void ps(const Arg &first) {
        pr(first);
        ps(); // no space at end of line
    }

    template<class Arg, class... Args>
    void ps(const Arg &first, const Args &... rest) {
        pr(first, " ");
        ps(rest...); // print w/ spaces
    }
}
using namespace output;

/* ============================ */

int dist[600][600][3]; // 0 = upright, 1 = horizontal, 2 = vertical
min_heap<array<int, 4>> pq;
map<array<int, 3>, int> dist2;
queue<array<int, 3>> q;
vector<vii> holes;

int main() {
    setupIO();

    int k, m;
    re(k, m);
    int x1, y1, x2, y2;
    re(x1, y1, x2, y2);
    F0R(i, k - 1) {
        vii x;
        int n;
        re(n);
        F0R(j, n) {
            int a, b;
            re(a, b);
            x.pb(mp(a, b));
        }
        holes.pb(x);
    }
    SET3D(dist, INF, 600, 600, 3);
    dist[100][100][0] = 0;
    q.push({100, 100, 0});
    while (!q.empty()) {
        array<int, 3> aa = q.front();
        q.pop();
        int x = aa[0], y = aa[1], z = aa[2];
        vi dx, dy, dz;
        if (m == 1) {
            dx = {1, -1, 0, 0};
            dy = {0, 0, 1, -1};
            dz = {0, 0, 0, 0};
        } else {
            if (z == 0) {
                dx = {1, -m, 0, 0};
                dy = {0, 0, 1, -m};
                dz = {1, 1, 2, 2};
            } else if (z == 1) {
                dx = {-1, m, 0, 0};
                dy = {0, 0, 1, -1};
                dz = {0, 0, 1, 1};
            } else if (z == 2) {
                dx = {1, -1, 0, 0};
                dy = {0, 0, -1, m};
                dz = {2, 2, 0, 0};
            }
        }
        F0R(j, 4) {
            int a = x + dx[j], b = y + dy[j], c = dz[j];
            if (a >= 0 && a < 600 && b >= 0 && b < 600) {
                if (dist[a][b][c] > dist[x][y][z] + 1) {
                    dist[a][b][c] = dist[x][y][z] + 1;
                    q.push({a, b, c});
                }
            }
        }
    }

    pq.push({0, x1, y1, 0});
    dist2[{x1, y1, 0}] = 0;
    int bAns = INF;
    while (!pq.empty()) {
        array<int, 4> aa = pq.top(); pq.pop();
        int x = aa[1], y = aa[2], d = aa[0];
        int floor = aa[3];
        if (dist2[{x, y, floor}] < d) continue;
        if (floor == k - 1) {
            int dx = abs(x2 - x), dy = abs(y2 - y);
            MIN(bAns, dist[100+dx][100+dy][0] + d);
            continue;
        }
        for (ii hole : holes[floor]) {
            int dx = abs(hole.pA - x), dy = abs(hole.pB - y);
            int dd = dist[100 + dx][100 + dy][0];
            if (dist2.count({hole.pA, hole.pB, floor + 1}) == 0 || dist2[{hole.pA, hole.pB, floor + 1}] > dd + d) {
                dist2[{hole.pA, hole.pB, floor + 1}] = dd + d;
                pq.push({dd+d, hole.pA, hole.pB, floor + 1});
            }
        }
    }
    ps(bAns);

    return 0;
}