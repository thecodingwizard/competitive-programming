/*
 * This problem really has two parts: first, finding distance from each square to the nearest scarefrog,
 * and second, finding the maximum scarefrog distance.
 *
 * The second part can be done using dijkstra, where the "distance" to a node is the maximum scarefrog distance
 * on the optimal path to that node. Complexity O(xy log xy)
 *
 * The first part is more challenging. The editorial describes a neat, fast O(xy) algorithm,
 * where you calculate 1D distance along each row first, then calculate 1D distance along each column
 * with the distances from each row. See editorial for more details.
 *
 * The approach I used is easier to understand (kind of) but much, much slower and requires a lot of
 * sketchy optimizations. Basically you can BFS from each frog *in all 8 directions* one step at a time.
 * If your BFS runs into a square that is closer to another scarefrog, then stop BFS'ing in that direction.
 * With a lot of complicated optimizations, this passes in time.
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

    void fastscan(int &x) {
        bool neg=false;
        register int c;
        x =0;
        c=getchar();
        if(c=='-')
        {
            neg = true;
            c=getchar();
        }
        for(;(c>47 && c<58);c=getchar())
            x = (x<<1) + (x<<3) +c -48;
        if(neg)
            x *=-1;
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

int main() {
    setupIO();

    int n, m; fastscan(n); fastscan(m);
    int px, py, kx, ky; fastscan(px); fastscan(py); fastscan(kx); fastscan(ky); --px; --py; --kx; --ky;
    int frogCt; fastscan(frogCt);
    ii frogs[frogCt];
    F0R(i, frogCt) {
        fastscan(frogs[i].pA); frogs[i].pA--;
        fastscan(frogs[i].pB); frogs[i].pB--;
    }

    int distToFrog[1000][1000]; SET2D(distToFrog, INF, n, m);
    int dx[8] = { -1, 0, 1, 0, -1, -1, 1, 1 };
    int dy[8] = { 0, 1, 0, -1, -1, 1, -1, 1 };
    vector<pair<int,vi>> q[2];
    F0R(i, frogCt) {
        ii x = frogs[i];

        distToFrog[x.pA][x.pB] = 0;
        q[0].pb({i,{((x.pA*1000)+x.pB)*10 + 9}});
    }

    bool change = true;
    int iter = 0;
    while (change) {
        change = false;
        int idx = iter % 2;
        int nxt = (iter+1) % 2;
        F0R(qIdx, q[idx].size()) {
            int fi = q[idx][qIdx].pA;
            ii x = frogs[fi];
            vector<int> nextQueue;
            for (int targ : q[idx][qIdx].pB) {
                ii u = {targ / 10000, (targ/10) % 1000};
                int from = targ % 10;
                if (from == 9) {
                    F0R(i, 8) {
                        int a = u.pA + dx[i], b = u.pB + dy[i];
                        if (a < 0 || a >= n || b < 0 || b >= m) continue;
                        int tmp = (x.pB - b) * (x.pB - b) + (x.pA - a) * (x.pA - a);
                        if (distToFrog[a][b] > tmp) {
                            distToFrog[a][b] = tmp;
                            nextQueue.pb((a * 1000 + b) * 10 + i);
                            change = true;
                        }
                    }
                } else {
                    int a = u.pA + dx[from], b = u.pB + dy[from];
                    if (a < 0 || a >= n || b < 0 || b >= m) {}
                    else {
                        int tmp = (x.pB - b) * (x.pB - b) + (x.pA - a) * (x.pA - a);
                        if (distToFrog[a][b] > tmp) {
                            distToFrog[a][b] = tmp;
                            nextQueue.pb((a * 1000 + b) * 10 + from);
                            change = true;
                        }
                    }
                    if (from >= 4) {
                        a = u.pA, b = u.pB + dy[from];
                        int nextFrom = dy[from] == -1 ? 3 : 1;
                        if (a < 0 || a >= n || b < 0 || b >= m) {}
                        else {
                            int tmp = (x.pB - b) * (x.pB - b) + (x.pA - a) * (x.pA - a);
                            if (distToFrog[a][b] > tmp) {
                                distToFrog[a][b] = tmp;
                                nextQueue.pb((a * 1000 + b) * 10 + nextFrom);
                                change = true;
                            }
                        }

                        a = u.pA + dx[from], b = u.pB;
                        nextFrom = dx[from] == -1 ? 0 : 2;
                        if (a < 0 || a >= n || b < 0 || b >= m) {}
                        else {
                            int tmp = (x.pB - b) * (x.pB - b) + (x.pA - a) * (x.pA - a);
                            if (distToFrog[a][b] > tmp) {
                                distToFrog[a][b] = tmp;
                                nextQueue.pb((a * 1000 + b) * 10 + nextFrom);
                                change = true;
                            }
                        }
                    }
                }
            }
            if (!nextQueue.empty()) {
                q[nxt].eb(fi, nextQueue);
            }
        }
        q[idx].clear();
        iter++;
    }

    int realDist[1000][1000]; SET2D(realDist, INF, n, m);
    priority_queue<pair<int, ii>> pq; pq.push({distToFrog[px][py], {px, py}});
    realDist[px][py] = distToFrog[px][py];
    while (!pq.empty()) {
        pair<int, ii> u = pq.top(); pq.pop();
        if (u.pA < realDist[u.pB.pA][u.pB.pB]) continue;
        F0R(i, 4) {
            int a = u.pB.pA + dx[i], b = u.pB.pB + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            int newVal = min(u.pA, min(distToFrog[u.pB.pA][u.pB.pB], distToFrog[a][b]));
            if (realDist[a][b] == INF || newVal > realDist[a][b]) {
                realDist[a][b] = newVal;
                pq.push({newVal, {a, b}});
            }
        }
    }
    ps(realDist[kx][ky]);

    return 0;
}
