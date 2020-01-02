/*
 * When thinking of the collisions, it's easier to think of it as the left and right ants passing through each other.
 * The right moving ant will keep the original color, but the left moving ant will change into a new color of (a+b)%k.
 *
 * A n^2 solution can be achieved as follows (untested): For each ant, figure out how much it adds to the answer.
 * If the ant is right moving, it adds (L - loc) to its color. If it is left moving, then we simulate its movement
 * by looping from right to left through all the right moving ants it will hit. We can calculate how far it travels
 * in each color.
 *
 * To speed this up, we can do one single sweep from right to left. When we reach a right moving ant, we process as before.
 * When we reach a left moving ant, instead of sweeping through right moving ants again, we store its distance based on color:
 * we can define colorDist[i] = sum of locations of left moving ants of color i that we have encountered so far.
 * Then, when we reach the next right moving ant, we know that all the left moving ants we reached previously will
 * collide with this right moving ant at some point. For every color, we can mathematically calculate how far the
 * ants of that color will move before hitting the right moving ant. Then we update colorDist to account for color changes.
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

struct ant {
    ll loc, color, dir; // dir = 0 means left, dir = 1 means right
};

int main() {
    setupIO();

    int n, k, l; re(n, k, l); l = l*2;
    vector<ant> ants;
    int lastRightAnt = -1;
    F0R(i, n) {
        int a, b; char c; re(a, b, c);
        ants.pb({a*2, b, c == 'D' ? 1 : 0});
        if (c == 'D' && lastRightAnt == -1) lastRightAnt = i;
    }
    ll prevColorDist[k]; ll nextPrevColorDist[k]; SET(prevColorDist, 0, k);
    ll colorDist[k]; int colorCt[k]; SET(colorDist, 0, k); SET(colorCt, 0, k);
    ll nextColorDist[k]; int nextColorCt[k];
    ll ans[k+1]; SET(ans, 0, k);
    F0Rd(i, n) {
        ant x = ants[i];
        if (x.dir == 1) {
            ans[x.color] += l-x.loc;
            F0R(j, k) {
                ans[j] += (colorDist[j]-x.loc*colorCt[j])/2 - prevColorDist[j];
                if (i == lastRightAnt) {
                    ans[(j + x.color) % k] += x.loc*colorCt[j] + (colorDist[j]-x.loc*colorCt[j])/2;
                }
                nextPrevColorDist[(j + x.color) % k] = (colorDist[j]-x.loc*colorCt[j])/2;
                nextColorDist[(j + x.color) % k] = colorDist[j];
                nextColorCt[(j + x.color) % k] = colorCt[j];
            }
            F0R(j, k) {
                colorDist[j] = nextColorDist[j];
                colorCt[j] = nextColorCt[j];
                prevColorDist[j] = nextPrevColorDist[j];
            }
        } else {
            if (i < lastRightAnt) {
                ans[x.color] += x.loc;
            }
            colorDist[x.color] += x.loc;
            colorCt[x.color]++;
        }
    }

    cout << fixed << setprecision(1);
    F0R(i, k) ps(ans[i]/2.0);

    return 0;
}