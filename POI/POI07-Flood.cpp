/*
 * If we have something like   6  -1  4, we can place a pump on 4 to drain all the water in the city.
 * Make sure you see why.
 *
 * We can greedily assign pumps to the lowest city if it is not already covered by an existing pump.
 * Why? Well, we don't have to put any pumps on a square if it isn't part of the city.
 *
 * Let's say we put a pump on a square X with altitude x. This square isn't part of the city.
 * Let's say the lowest city Y it drains has altitude y > x. We can move our pump from square X
 * to square Y while still draining all the cities that the pump in square X drained, because
 * any city draining to square X is also going to drain to square Y.
 *
 * Iterate through the city squares in increasing altitude. If the city isn't covered yet,
 * add a pump to the city and the mark any city that can be drained from that pump as "covered."
 *
 * For implementation, it may be helpful to do the following:
 * For any non-city square X, we can increase its altitude
 * to be the same as the lowest city that drains to square X, then do the above.
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
bool covered[1000][1000];
bool vis[1000][1000];
int A[1000][1000];
bool city[1000][1000];
vii cities[1000];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
void cover(int i, int j) {
    if (covered[i][j]) return;
    covered[i][j] = true;
    F0R(x, 4) {
        int a = i + dx[x], b = j + dy[x];
        if (a < 0 || a >= n || b < 0 || b >= m) continue;
        if (A[a][b] < A[i][j]) continue;
        cover(a, b);
    }
}

int main() {
    setupIO();

    re(n, m);
    SET2D(covered, false, n, m);
    SET2D(vis, false, n, m);
    SET2D(city, false, n, m);
    min_heap<iii> pq;
    F0R(i, n) {
        F0R(j, m) {
            int x; re(x);
            A[i][j] = x;
            city[i][j] = x > 0;
            if (city[i][j]) pq.push({x,{i,j}});
        }
    }
    while (!pq.empty()) {
        iii u = pq.top(); pq.pop();
        if (vis[u.pB.pA][u.pB.pB]) continue; vis[u.pB.pA][u.pB.pB] = true;
        F0R(i, 4) {
            int a = u.pB.pA + dx[i], b = u.pB.pB + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (city[a][b]) continue;
            if (A[a][b] < 0 && abs(A[a][b]) <= A[u.pB.pA][u.pB.pB]) {
                A[a][b] = A[u.pB.pA][u.pB.pB];
                pq.push({A[a][b],{a,b}});
            }
        }
    }
    F0R(i, n) F0R(j, m) A[i][j] = abs(A[i][j]);

    F0R(i, n) {
        F0R(j, m) {
            if (city[i][j]) {
                cities[A[i][j]-1].pb(mp(i,j));
            }
        }
    }

    int ans = 0;
    F0R(i,1000){
        trav(x, cities[i]) {
            if (covered[x.pA][x.pB]) continue;
            cover(x.pA, x.pB);
            ans++;
        }
    }
    ps(ans);

    return 0;
}