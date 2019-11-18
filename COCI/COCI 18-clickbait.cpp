/*
 * The challenge in this problem is implementing the reading + parsing of input.
 *
 * Make each container a node. Make each "pipe" to the next container a directed edge.
 * Start from the root node and run a DFS. make sure to DFS children with a lower pipe before
 * children with a higher pipe. After all the children of a node are filled then the node itself
 * will be filled.
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

void lookForOtherContainers(int x, int y);

int n, m;
char A[1000][1000];
int containerID[1000][1000];
int xLoc[50000];
int yLoc[50000];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { -1, 1, 0, 0 };
void dfsContainer(int i, int j, int id) {
    containerID[i][j] = id;
    if (A[i][j] == '+' || A[i][j] == '|' || A[i][j] == '-') return;
    F0R(x, 4) {
        int a = i + dx[x], b = j + dy[x];
        if (a >= 0 && a < n && b >= 0 && b < m && containerID[a][b] == -1) {
            dfsContainer(a, b, id);
        }
    }
}

vi order; vii otherContainers;
void dfs2(int x, int y, int id) {
//    psD("processing", id);
    lookForOtherContainers(x, y);
    vii cc = otherContainers; otherContainers.clear();
    sort(all(cc));
    trav(x, cc) {
        dfs2(xLoc[x.pB], yLoc[x.pB], x.pB);
    }
    order.pb(id);
}

int followPipe(int x, int y, int px, int py) {
    if (containerID[x][y] != -1) return containerID[x][y];
    F0R(i, 4) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < m && A[a][b] != '.' && !(a == px && b == py)) {
            return followPipe(a, b, x, y);
        }
    }
//    psD("follow pipe didn't find a destination :(");
    assert(false);
}

bool vis[1000][1000];
void lookForOtherContainers(int x, int y) {
    vis[x][y] = true;
    if (A[x][y] == '-') {
        return;
    }
    if (A[x][y] == '|') {
        F0R(i, 2) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < n && b >= 0 && b < m && A[a][b] == '-') {
                int endContainer = followPipe(a, b, x, y);
//                psD("found container:", endContainer);
                otherContainers.pb({-a, endContainer});
            }
        }
        return;
    }
    F0R(i, 4) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < m && !vis[a][b]) {
            lookForOtherContainers(a, b);
        }
    }
}

int main() {
    setupIO();

    re(n, m);
    F0R(i, n) {
        F0R(j, m) {
            re(A[i][j]);
        }
    }

    SET2D(containerID, -1, 1000, 1000);
    SET2D(vis, false, 1000, 1000);

    F0R(i, n) {
        F0R(j, m) {
            if (A[i][j] >= '1' && A[i][j] <= '9') {
                int id = A[i][j] - '0';
                while (j + 1 < m && A[i][j+1] >= '0' && A[i][j+1] <= '9') {
                    id = id * 10 + A[i][++j] - '0';
                }
                xLoc[id] = i; yLoc[id] = j;

                if (id >= 50000) exit(1);

                dfsContainer(i, j, id);
            }
        }
    }

    dfs2(xLoc[1], yLoc[1], 1);
    trav(x, order) ps(x);

    return 0;
}
