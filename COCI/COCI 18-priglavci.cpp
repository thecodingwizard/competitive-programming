/*
 * Binary search for the maximum distance.
 *
 * Construct a flow network, source connected to each of the students with capacity 1.
 *
 * Each of the bus lines is a node; they are connected to the sink with capacity c.
 *
 * There is a connection between a student and a bus line if there exists a stop of that bus line
 * that can be reached by sthe student within the maximum distance.
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

int n, m, c, k; 
vii A; 
vii M;
vi busID; 

int d(ii a, ii b) {
    return (a.pA-b.pA)*(a.pA-b.pA)+(a.pB-b.pB)*(a.pB-b.pB);
}

int f;
int res[220][220];
vi adj[220];

vi parent;

int getPath() {
    parent.assign(1+n+m+1, -1);
    queue<int> q; q.push(0); parent[0] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        trav(v, adj[u]) {
            if (res[u][v] != 0) {
                if (parent[v] != -1) continue;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    if (parent[1+n+m] == -1) return 0;
    int i = 1+n+m;
    int flow = INF;
    while (i != 0) {
        MIN(flow, res[parent[i]][i]);
        i = parent[i];
    }
    return flow;
}

void solve(int mxDist) {
    F0R(i, n+m+4) {
        adj[i].clear();
    }

    F0R(i, n) {
        adj[0].pb(i+1);
        adj[i+1].pb(0);
        res[0][i+1] = 1;
        res[i+1][0] = 0;
    }
    F0R(j2, m) {
        int j = busID[j2];
        adj[1+n+j].pb(1+n+m);
        adj[1+n+m].pb(1+n+j);
        res[1+n+j][1+n+m] = c;
        res[1+n+m][1+n+j] = 0;
    }
    F0R(i, n) {
        F0R(j, m) {
            if (d(A[i], M[j]) <= mxDist) {
                int a = 1+i, b = 1+n+busID[j];
                adj[a].pb(b); adj[b].pb(a);
                res[a][b] = 1;
                res[b][a] = 0;
            }
        }
    }

    f = 0;
    int newFlow = 0;
    while (newFlow = getPath()) {
        f += newFlow;
        int i = 1+n+m;
        while (i != 0) {
            res[parent[i]][i] -= newFlow;
            res[i][parent[i]] += newFlow;
            i = parent[i];
        }
    }
}

int main() {
    setupIO();

    re(n, m, c, k);
    A.resz(n); re(A);
    M.resz(m); re(M);
    busID.resz(m);
    F0R(i, k) {
        int k_i; re(k_i);
        F0R(j, k_i) {
            int stop; re(stop);
            busID[stop-1] = i;
        }
    }
    
    int lo = 0, hi = 2000*2000*2, mid, ans = -1;
    vi optimal_assignment; optimal_assignment.resz(n);
    while (lo < hi) {
        mid = (lo + hi)/2;
        solve(mid);
        if (f == n) {
            ans = mid;
            hi = mid;
            F0R(i, n) {
                F0R(j, m) {
                    if (d(A[i], M[j]) <= mid && res[1+i][1+n+busID[j]] == 0) {
                        optimal_assignment[i] = j;
                    }
                }
            }
        } else {
            lo = mid + 1;
        }
    }
    ps(ans);
    if (ans != -1) {
        F0R(i, n) {
            ps(optimal_assignment[i] + 1);
        }
    }

    return 0;
}











