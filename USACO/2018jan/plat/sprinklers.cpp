/*
 * My solution was rather difficult to implement... I'd recommend going with editorial's.
 *
 * Sort the sprinklers left to right and process in increasing x direction.
 * At each x location, calculate the number of rectangles that can be formed with left edge on this x location.
 * This can be done mathematically though it's really complicated... see implementation for details...
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
    setupIO("sprinklers");

    int n; re(n);
    int A[n];
    vii sortedA;
    deque<ii> sprinklers;

    F0R(i, n) {
        int a, b; re(a, b);
        A[a] = b;
        sortedA.pb({a,b});
    }
    sort(all(sortedA));
    F0R(i, n) {
        int a = sortedA[i].pA, b = sortedA[i].pB;
        while (!sprinklers.empty() && sprinklers.back().pB < b) sprinklers.pop_back();
        sprinklers.push_back({a, b});
    }
    ll maxHeight[n];
    int maxHeightIdx = 0;

    ll ans = 0;
    ll curLB = -1;
    ll curSum = 0;
    ll curAdd = 0;
    ll right = 0;

    for (int left = 0; left < n; left++) {
//        psD("left, ans, curLB, curSum, curAdd, right", left, ans, curLB, curSum, curAdd, right);
        // step one: process left
        if (curLB == -1 || curLB > A[left]) {
            if (curLB == -1) curLB = A[left];
            else {
                ll diff = (curLB - A[left]);
                curAdd += curSum*diff%MOD;
                curAdd %= MOD;
                curAdd += diff*(diff-1)/2%MOD*(right-left)%MOD;
                curSum += (right - left)*(curLB - A[left])%MOD;
                curAdd %= MOD;
                curSum %= MOD;
                curLB = A[left];
            }
        }
        // step two: add right sprinklers
        while (!sprinklers.empty() && sprinklers.front().pB >= curLB) {
            ll height = sprinklers.front().pB - curLB + 1;
            ll base = sprinklers.front().pA - right;
            ll heightc2 = height*(height-1)/2%MOD;

            curAdd += base * heightc2%MOD;
            curSum += base * height%MOD;
            curAdd %= MOD;
            curSum %= MOD;

            while (maxHeightIdx < n && A[maxHeightIdx] != sprinklers.front().pB) {
//                psD("maxHeight[", maxHeightIdx, "] = ", sprinklers.front().pB);
                maxHeight[maxHeightIdx++] = sprinklers.front().pB;
            }
//            psD("maxHeight[", maxHeightIdx, "] = ", sprinklers.front().pB);
            maxHeight[maxHeightIdx++] = sprinklers.front().pB;

            right = sprinklers.front().pA;
            sprinklers.pop_front();
        }
        // step three: update variables
        ans += curAdd;
        ans %= MOD;
        if (right <= left) right = left + 1;
        else {
            ll height = maxHeight[left+1] - curLB + 1;
            ll heightc2 = height*(height-1)/2%MOD;
//            psD("updating", left, right, height, curLB);
            curAdd -= heightc2;
            curSum -= height;
            curAdd = (curAdd + MOD) % MOD;
            curSum = (curSum + MOD) % MOD;
        }
    }
    ps(ans);

    return 0;
}
