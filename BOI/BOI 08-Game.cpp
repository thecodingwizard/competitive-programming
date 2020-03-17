/*
 * Same solution as https://github.com/MetalBall887/Competitive-Programming/blob/master/Olympiad/Baltic/Baltic%2008-Game.cpp
 *
 * DP[ax][ay][bx][by], at each step you must go closer to your destination
 *
 * To optimize, make a list of all possible locations that A can be in after t units of time
 * Make a list for B too
 *
 * define DP[t][i][j] = at time = t, A is on the ith location in the list of possible locations,
 * B is on the jth location in the list of possible locations, return true if A wins, false if B wins
 *
 * Solve iteratively
 *
 * Memory limit is really lax on CSES I think...
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
char A[300][300];

int distA[300][300], distB[300][300];
vii locA[300*300], locB[300*300];
bool dp[2][600][600];
int idxA[300][300];
int idxB[300][300];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int D;

//bool dp(int ax, int ay, int bx, int by) {
//    if (memo[ax][ay][bx][by] != -1) return memo[ax][ay][bx][by];
//    if (ax==bx&&ay==by) return false;
//    if (distB[ax][ay] <= D/2) return true;
//    F0R(i, 4) {
//        ii a = {ax + dx[i], ay + dy[i]};
//        if (a.pA<0||a.pA>=n||a.pB<0||a.pB>=n)continue;
//        if (distB[ax][ay] != distB[a.pA][a.pB]+1) continue;
//        bool good = true;
//        F0R(j, 4) {
//            ii b = {bx + dx[j], by + dy[j]};
//            if (b.pA<0||b.pA>=n||b.pB<0||b.pB>=n)continue;
//            if (distA[bx][by] != distA[b.pA][b.pB]+1) continue;
//            if (!dp(a.pA,a.pB,b.pA,b.pB)) good = false;
//        }
//        if (good) return memo[ax][ay][bx][by] = true;
//    }
//    return memo[ax][ay][bx][by] = false;
//}

void bfs(int arr[300][300], int x, int y) {
    SET2D(arr, INF, n, n);
    arr[x][y] = 0;
    queue<ii> q; q.push({x, y});
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        F0R(i, 4) {
            ii v = {u.pA+dx[i], u.pB+dy[i]};
            if (v.pA<0||v.pA>=n||v.pB<0||v.pB>=n||A[v.pA][v.pB]=='#')continue;
            if (arr[v.pA][v.pB] == INF) {
                arr[v.pA][v.pB] = arr[u.pA][u.pB]+1;
                q.push(v);
            }
        }
    }
}

void solve() {
    re(n);
    ii startA, startB;
    F0R(i, n) {
        F0R(j, n) {
            re(A[i][j]);
            if (A[i][j] == 'A') {
                startA = { i, j };
            } else if (A[i][j] == 'B') {
                startB = { i, j };
            }
        }
    }
    F0R(i, n*n) {
        locA[i].clear();
        locB[i].clear();
    }
    bfs(distA, startA.pA, startA.pB);
    bfs(distB, startB.pA, startB.pB);
    D = distA[startB.pA][startB.pB];
    if (D % 2 == 1) ps('A');
    else {
        F0R(i, n) {
            F0R(j, n) {
                if (distB[i][j] != INF && D-distB[i][j]<=D/2 && D-distB[i][j]>=0) {
                    locA[D-distB[i][j]].pb({i, j});
                    idxA[i][j] = sz(locA[D-distB[i][j]])-1;
                }
                if (distA[i][j] != INF && D-distA[i][j]<=D/2 && D-distA[i][j]>=0) {
                    locB[D-distA[i][j]].pb({i, j});
                    idxB[i][j] = sz(locB[D-distA[i][j]])-1;
                }
            }
        }
        F0Rd(time, D/2+1) {
            locA[time+1].clear();
            locB[time+1].clear();
            F0R(i, sz(locA[time])) {
                F0R(j, sz(locB[time])) {
                    if (locA[time][i] == locB[time][j]) {
                        dp[time%2][i][j] = false;
                    } else if (time == D/2) {
                        dp[time%2][i][j] = true;
                    } else {
                        int ax = locA[time][i].pA, ay = locA[time][i].pB, bx = locB[time][j].pA, by = locB[time][j].pB;
                        bool res = false;
                        F0R(x, 4) {
                            ii a = {ax + dx[x], ay + dy[x]};
                            if (a.pA<0||a.pA>=n||a.pB<0||a.pB>=n)continue;
                            if (distB[ax][ay] != distB[a.pA][a.pB]+1) continue;
                            bool good = true;
                            F0R(y, 4) {
                                ii b = {bx + dx[y], by + dy[y]};
                                if (b.pA<0||b.pA>=n||b.pB<0||b.pB>=n)continue;
                                if (distA[bx][by] != distA[b.pA][b.pB]+1) continue;
                                if (!dp[(time+1)%2][idxA[a.pA][a.pB]][idxB[b.pA][b.pB]]) good = false;
                            }
                            if (good) {
                                res = true;
                                break;
                            }
                        }
                        dp[time%2][i][j] = res;
                    }
                }
            }
        }
        ps(dp[0][idxA[startA.pA][startA.pB]][idxB[startB.pA][startB.pB]] ? 'A' : 'B');
    }
}

int main() {
    setupIO();

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}