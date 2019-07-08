/*
 * Batch 1:
 * - You can brute force (a+b)*l
 * - A guard can see a vault if and only if the x-distance and the y-distance from the guard to the vault is relatively prime
 * - (Some edge cases to above rule when x-distance is 1 or y-distance is 0)
 *
 * Batch 2:
 * - You can brute force (a+b)*(a*b)
 * - The vaults that can be seen by each guard repeat at a*b
 * - Hence for every y-coordinate you don't have to loop all the way to l, you can stop at a*b
 *
 * Batch 3:
 * - Same as editorial
 * - Basically, let's assume we have a function calc(a, b) that returns the number of numbers from 1...b
 *   that are relatively prime to a. So calc(6, 9) = 3. (1, 5, 7)
 * - We handle each y-coordinate from -A to B
 * - Let's call the y-distance to guard (0, -A) = da, (0, B) = db
 * - Define:
        ll relPrimeA = calc(da, l);
        ll relPrimeB = calc(db, l);
        ll relPrimeAB = calc(da*db, l);
 * - Note that super secure = relPrimeAB
 * - semi secure = relPrimeA + relPrimeB - 2*relPrimeAB
 * - not secure = l - relPrimeA - relPrimeB + rePrimeAB
 *
 * - Now we have to implement calc, which we can do using principle of inclusion exclusion on the factors of a.
 * - For example, if a = 24, then factors = 2, 3. Let's say l = 100.
 * - The answer will be 100/2 + 100/3 - 100/6
 *
 * - Make sure to handle edge cases (x-distance 1, y-distance 0)
 *
 * Contains code for:
 * - Principle of Inclusion Exclusion (PIE)
 * - Finding prime factors of a number
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

/* ============================ */

// finds prime factors of a
vi getFactors(int a) {
    vi factors;
    if (a % 2 == 0) {
        factors.pb(2);
        while (a % 2 == 0) a /= 2;
    }
    for (int f = 3; f <= sqrt(a); f += 2) {
        if (a % f == 0) {
            factors.pb(f);
            while (a % f == 0) a /= f;
        }
    }
    if (a > 2) factors.pb(a);
    return factors;
}

// Principle of Inclusion Exclusion (PIE)
// returns number of numbers from 1...b that are relatively prime to a
ll calc(ll a, ll b) {
    if (a == 0) return 0;
    if (a == 1) return b;
    ll x = 0;
    vi factors = getFactors(a);
    int n = sz(factors);
    F0R(i, (1 << n)) {
        if (i == 0) continue;
        int mult = __builtin_popcount(i) % 2 == 0 ? -1 : 1;
        int curF = 1;
        F0R(j, n) {
            if (i & (1 << j)) curF *= factors[j];
        }
        x += mult*b/curF;
    }
    return b - x;
}

int main() {
    setupIO();

    int a, b; ll l; re(a, b, l);
    ll ax, ay, az; ax = ay = az = 0;
    FOR(i, -a, b+1) {
        int da = i - (-a);
        int db = b - i;
        ll relPrimeA = calc(da, l);
        ll relPrimeB = calc(db, l);
        ll relPrimeAB = calc(da*db, l);
        az += relPrimeAB;
        ay += relPrimeA + relPrimeB - 2*relPrimeAB;
        ax += l - relPrimeA - relPrimeB + relPrimeAB;
    }
    // Edge case: (1, -A) and (1, B) are super secure
    ay -= 2;
    az += 2;
    ps(ax); ps(ay); ps(az);

    return 0;
}