/*
 * Note that all the guards return to the same location every 12 steps. Therefore
 * we can accurately describe our state as the location of both the robots + the number of
 * steps we've taken mod 12. our state size is 20*20*20*20*12 which fits in memory constraint
 *
 * Then we just run a BFS from each state to the next state, keeping parent pointers.
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

struct guard {
    int x, y, l, d;
    ii loc[12];
};

struct state {
    int x1, y1, x2, y2, t;
};

int r1, c1;
char A[22][22];
vector<guard> G1;
int r2, c2;
char B[22][22];
vector<guard> G2;

int dir[1000]; char dirs[4] = {'N', 'E', 'S', 'W'};
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int dist[21][21][21][21][12];
int parent[21][21][21][21][12];

ii getGuardLoc(guard g, int t) {
    int x = g.x, y = g.y;
    int l2 = g.l - 1;
    F0R(i, t) {
        x += dx[g.d]; y += dy[g.d];
        if (--l2 == 0) {
            l2 = g.l - 1;
            g.d = (g.d+2)%4;
        }
    }
    return {x, y};
}

ii move(int x, int y, char (&A)[22][22], vector<guard> &G, int t, int d) {
    if (x == 0 && y == 0) return {0, 0};
    int a = x + dx[d], b = y + dy[d];
    if (A[a][b] == '#') {
        a = x, b = y;
    }
    if (A[a][b] == '!') {
        return {0, 0};
    }

    // check guards
    trav(g, G) {
        ii ga = g.loc[t], gb = g.loc[(t+1)%12];
        if (gb.pA == a && gb.pB == b) return {-1, -1};
        if (gb.pA == x && gb.pB == y && ga.pA == a && ga.pB == b) return {-1, -1};
    }

    return {a, b};
}

int compress(int x1, int y1, int x2, int y2, int t, int d) {
    int multiplier = 1;
    int res = 0;
    res += x1*multiplier; multiplier *= 21;
    res += y1*multiplier; multiplier *= 21;
    res += x2*multiplier; multiplier *= 21;
    res += y2*multiplier; multiplier *= 21;
    res += t*multiplier; multiplier *= 12;
    res += d*multiplier; multiplier *= 2;
    return res;
}

pair<state, int> extract(int num) {
    int x1 = num % 21; num /= 21;
    int y1 = num % 21; num /= 21;
    int x2 = num % 21; num /= 21;
    int y2 = num % 21; num /= 21;
    int t = num % 12; num /= 12;
    int d = num;
    return {{x1, y1, x2, y2, t}, d};
}

int main() {
    setupIO();

    dir['N'] = 0, dir['E'] = 1, dir['S'] = 2, dir['W'] = 3;

    int x1, y1, x2, y2;

    SET2D(A, '!', 22, 22);
    SET2D(B, '!', 22, 22);

    re(r1, c1);
    F0R1(i, r1) {
        F0R1(j, c1) {
            re(A[i][j]);
            if (A[i][j] == 'X') {
                x1 = i; y1 = j;
            }
        }
    }
    int g1; re(g1);
    F0R(i, g1) {
        int x, y, l; char d; re(x, y, l, d);
        G1.pb({x, y, l, dir[d]});
        F0R(j, 12) G1.back().loc[j] = getGuardLoc(G1.back(), j);
    }

    re(r2, c2);
    F0R1(i, r2) {
        F0R1(j, c2) {
            re(B[i][j]);
            if (B[i][j] == 'X') {
                x2 = i; y2 = j;
            }
        }
    }
    int g2; re(g2);
    F0R(i, g2) {
        int x, y, l; char d; re(x, y, l, d);
        G2.pb({x, y, l, dir[d]});
        F0R(j, 12) G2.back().loc[j] = getGuardLoc(G2.back(), j);
    }

    F0R(i, 21) F0R(j, 21) F0R(k, 21) F0R(l, 21) F0R(m, 12) dist[i][j][k][l][m] = INF;

    queue<state> q; q.push({x1, y1, x2, y2, 0});
    dist[x1][y1][x2][y2][0] = 0;
    parent[x1][y1][x2][y2][0] = -1;
    while (!q.empty()) {
        state u = q.front(); q.pop();
        int x1 = u.x1, y1 = u.y1, x2 = u.x2, y2 = u.y2, t = u.t;
        int d = dist[x1][y1][x2][y2][t];
        if (d > 10000) {
            ps(-1);
            return 0;
        }

        bool done = false;
        F0R(i, 4) {
            ii a = move(x1, y1, A, G1, t, i);
            ii b = move(x2, y2, B, G2, t, i);
            if (a.pA != -1 && b.pA != -1) {
                if (d + 1 < dist[a.pA][a.pB][b.pA][b.pB][(t+1)%12]) {
                    dist[a.pA][a.pB][b.pA][b.pB][(t+1)%12] = d+1;
                    parent[a.pA][a.pB][b.pA][b.pB][(t+1)%12] = compress(x1, y1, x2, y2, t, i);
                    if (a.pA == 0 && a.pB == 0 && b.pA == 0 && b.pB == 0) {
                        done = true;
                        break;
                    }
                    q.push({a.pA,a.pB,b.pA,b.pB,(t+1)%12});
                }
            }
        }
        if (done) break;
    }

    int minDist = INF, minDistT = -1;
    F0R(i, 12) {
        if (dist[0][0][0][0][i] < minDist) {
            minDist = dist[0][0][0][0][i];
            minDistT = i;
        }
    }

    if (minDist == INF) {
        ps(-1);
        return 0;
    }

    ps(minDist);
    vi commands;
    state s = {0,0,0,0,minDistT};
    while (parent[s.x1][s.y1][s.x2][s.y2][s.t] != -1) {
        pair<state, int> p = extract(parent[s.x1][s.y1][s.x2][s.y2][s.t]);
        commands.pb(p.pB);
        s = p.pA;
    }
    reverse(all(commands));
    trav(x, commands) {
        ps(dirs[x]);
    }

    return 0;
}
