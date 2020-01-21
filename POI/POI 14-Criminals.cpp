/*
 * Let A[i] be the array of house colors
 *
 * Define startPosLeft[i] = the first house Bitie can rob and still end his robbing path at house i. startPosLeft[i] = -1
 * if A[i] is not the color of the final house the robbers can rob.
 *
 * Define startPosRight[i] similarly (for Bytie instead of Bitie).
 *
 * The robbers can end at i if there is a same color house in the range [0...startPosLeft[i]) and (startPosRight[i]...n-1].
 * We can precompute this in O(n).
 *
 * We can calculate startPosLeft[i] in O(n); Define startPos[i] for 0 <= i < k and initialize to -1.
 * Sweep A from left to right.
 * If A[i] is the first color, then startPos[A[i]] = i.
 * If A[i] is not the first color, then startPos[A[i]] = startPos[parent[A[i]], where parent is the house color
 * that will be robbed before A[i] is robbed.
 * If A[i] is the last color, then update startPosLeft[i] = startPos[A[i]].
 *
 * Similarly we can calculate startPosRight.
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

int main() {
    setupIO();

    int n, k; re(n, k);
    int A[n];
    vi positions[k];
    F0R(i, n) {
        re(A[i]); A[i]--;
        positions[A[i]].pb(i);
    }
    int m, l; re(m, l);
    int B[m], C[l], paB[k], paC[k]; SET(paB, -1, k); SET(paC, -1, k);
    F0R(i, m) {
        re(B[i]); B[i]--;
        paB[B[i]] = i == 0 ? -1 : B[i-1];
    }
    F0R(i, l) {
        re(C[i]); C[i]--;
        paC[C[i]] = i == 0 ? -1 : C[i-1];
    }

    int startPosLeft[n], startPosRight[n];
    SET(startPosLeft, -1, n); SET(startPosRight, -1, n);

    int startPos[k]; SET(startPos, -1, k);
    F0R(i, n) {
        if (A[i] == B[0]) {
            startPos[B[0]] = i;
        }
        if (paB[A[i]] != -1) startPos[A[i]] = startPos[paB[A[i]]];
        if (A[i] == B[m-1]) {
            startPosLeft[i] = startPos[A[i]];
        }
    }
    SET(startPos, -1, k);
    F0Rd(i, n) {
        if (A[i] == C[0]) {
            startPos[C[0]] = i;
        }
        if (paC[A[i]] != -1) startPos[A[i]] = startPos[paC[A[i]]];
        if (A[i] == C[l-1]) {
            startPosRight[i] = startPos[A[i]];
        }
    }

    int farthestHouseB[n], farthestHouseC[n];
    F0R(i, n) {
        farthestHouseB[i] = positions[A[i]].back();
        farthestHouseC[i] = positions[A[i]].front();
    }
    FOR(i, 1, n) {
        farthestHouseB[i] = max(farthestHouseB[i], farthestHouseB[i-1]);
    }
    F0Rd(i, n-1) {
        farthestHouseC[i] = min(farthestHouseC[i], farthestHouseC[i+1]);
    }

    vi ans;
    F0R(i, n) {
        if (startPosLeft[i] != -1 && startPosRight[i] != -1) {
            int l = startPosLeft[i], r = startPosRight[i];
            if (farthestHouseB[l-1] > r && farthestHouseC[r+1] < l) ans.pb(i+1);
        }
    }
    ps(sz(ans));
    ps(ans);

    return 0;
}