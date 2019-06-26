/*
 * The problem is basically: Come up with a list of numbers such that the lcm of these numbers is
 * maximized and the sum of the numbers is <= Q.
 *
 * Observe that the numbers should all be relatively prime to each other, and that the biggest
 * number in that list isn't very big (I found this intuitively, for a formal proof look at POI editorial).
 *
 * You can solve this problem using DP but the numbers get too big too fast. So either implement
 * biginteger or:
 *
 * You need to support following operations:
 * 1. comparison
 * 2. multiplication
 * 3. factorization
 *
 * instead of using long long, you can use long double which stores up to 10^308 with good enough
 * precision to do the first two operations. To handle the third operation, just make a list
 * of factors as you do your DP.
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
}

using namespace input;

namespace output {
    template<class T1, class T2> void prD(const pair<T1,T2>& x);
    template<class T, size_t SZ> void prD(const array<T,SZ>& x);
    template<class T> void prD(const vector<T>& x);
    template<class T> void prD(const set<T>& x);
    template<class T1, class T2> void prD(const map<T1,T2>& x);

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

/* ============================ */

vi primes = {       2  , 3,   5,   7,  11,  13,  17,  19,  23,  29
        , 31,  37,  41,  43,  47,  53,  59,  61,  67,  71
        , 73,  79,  83,  89,  97, 101, 103, 107, 109, 113
        , 127, 131, 137, 139, 149, 151, 157, 163, 167, 173
        , 179, 181, 191, 193, 197, 199, 211, 223, 227, 229
        , 233, 239, 241, 251, 257, 263, 269, 271, 277, 281
        , 283, 293, 307, 311, 313, 317, 331, 337, 347, 349
        , 353, 359, 367, 373, 379, 383, 389, 397, 401, 409
        , 419, 421, 431, 433, 439, 443, 449, 457, 461, 463
        , 467, 479, 487, 491, 499, 503, 509, 521, 523, 541
        , 547, 557, 563, 569, 571, 577, 587, 593, 599, 601
        , 607, 613, 617, 619, 631, 641, 643, 647, 653, 659
        , 661, 673, 677, 683, 691, 701, 709, 719, 727, 733
        , 739, 743, 751, 757, 761, 769, 773, 787, 797, 809
        , 811, 821, 823, 827, 829, 839, 853, 857, 859, 863
        , 877, 881, 883, 887, 907, 911, 919, 929, 937, 941
        , 947, 953, 967, 971, 977, 983, 991, 997  , 1009  , 1013
        , 1019,   1021 ,  1031  , 1033  , 1039 ,  1049  , 1051  , 1061 ,  1063   };

ld dp[2][10001];
vi nums[2][10001];

int main() {
    cout << fixed << setprecision(0);
    setupIO();

    int d; re(d);
    int A[d]; reA(A, d);
    SET2D(dp, 0, 2, 10001);
    dp[0][0] = 1;

    int mxQ = 0; F0R(i, d) MAX(mxQ, A[i]);

    F0R(i, primes.size()) {
        int cur = i % 2, nxt = (i + 1) % 2;
        F0R(j, mxQ + 1) {
            if (dp[nxt][j] < dp[cur][j]) {
                dp[nxt][j] = dp[cur][j];
                nums[nxt][j] = vi(nums[cur][j]);
            }
        }
        F0R(j, mxQ + 1) {
            int xx = primes[i];
            while (xx + j <= mxQ) {
                if (xx + j <= mxQ) {
                    if (dp[nxt][j + xx] < dp[cur][j]*xx) {
                        dp[nxt][j + xx] = dp[cur][j]*xx;
                        nums[nxt][j + xx] = vi(nums[cur][j]);
                        nums[nxt][j + xx].pb(xx);
                    }
                }
                xx *= primes[i];
            }
        }
    }

    int final = (primes.size()) % 2;
    FOR(j, 1, mxQ + 1) {
        if (dp[final][j] < dp[final][j-1]) {
            dp[final][j] = dp[final][j-1];
            nums[final][j] = vi(nums[final][j-1]);
        }
    }
    F0R(i, d) {
        vi ans = nums[final][A[i]];
        int done = 0; trav(x, ans) done += x;
        int ctr = 1;
        F0R(x, A[i] - done) {
            pr(ctr++, " ");
        }
        SORT(ans);
        for (int x : ans) {
            F0R(i, x) {
                if (i == x - 1) pr(ctr, " ");
                else pr(ctr + i + 1, " ");
            }
            ctr += x;
        }
        ps();
    }

    return 0;
}