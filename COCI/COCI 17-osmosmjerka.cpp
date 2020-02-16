/*
 * Same solution as editorial
 * - Use two mods (2e+9 + 11) and (1e+9 + 7), just one mod doesn't work
 * - Be careful with memory, O(n*m*8*18) is too much, must be O(n*m*8)
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

ll Hash[500][500][8];
ll Hash2[500][500][8];
ll nextHash[500][500][8];
ll nextHash2[500][500][8];
ll pw[(1 << 18)];
ll pw2[(1 << 18)];
ll curHash[500][500][8];
ll curHash2[500][500][8];

int main() {
    setupIO();

    int m, n, k; re(m, n, k); MIN(k, n*m);
    F0R(i, (1 << 18)) {
        if (i == 0) pw[i] = 1;
        else pw[i] = pw[i-1]*27%MOD;
        if (i == 0) pw2[i] = 1;
        else pw2[i] = pw2[i-1]*27%MOD2;
    }
    F0R(i, m) {
        F0R(j, n) {
            char c; re(c);
            F0R(k, 8) {
                Hash[i][j][k] = c - 'a' + 1;
                Hash2[i][j][k] = c - 'a' + 1;
            }
        }
    }
    F0R(i, m) {
        F0R(j, n) {
            F0R(l, 8) {
                curHash[i][j][l] = 0;
                curHash2[i][j][l] = 0;
            }
        }
    }
    int steps = 0;
    int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    F0R(x, 18) {
        if (x != 0) {
            int curSteps = (1 << (x-1));
            F0R(l, 8) {
                F0R(i, m) {
                    F0R(j, n) {
                        nextHash[i][j][l] = (Hash[i][j][l]*pw[curSteps]%MOD + Hash[((i+dx[l]*curSteps)%m+m)%m][((j+dy[l]*curSteps)%n+n)%n][l]) % MOD;
                        nextHash2[i][j][l] = (Hash2[i][j][l]*pw2[curSteps]%MOD2 + Hash2[((i+dx[l]*curSteps)%m+m)%m][((j+dy[l]*curSteps)%n+n)%n][l]) % MOD2;
                    }
                }
            }
            F0R(l, 8) {
                F0R(i, m) {
                    F0R(j, n) {
                        Hash[i][j][l] = nextHash[i][j][l];
                        Hash2[i][j][l] = nextHash2[i][j][l];
                    }
                }
            }
        }
        if ((1 << x) & k) {
            F0R(i, m) {
                F0R(j, n) {
                    F0R(l, 8) {
                        curHash[i][j][l] = (curHash[i][j][l] + pw[steps]*Hash[((i+dx[l]*steps)%m+m)%m][((j+dy[l]*steps)%n+n)%n][l]%MOD) % MOD;
                        curHash2[i][j][l] = (curHash2[i][j][l] + pw2[steps]*Hash2[((i+dx[l]*steps)%m+m)%m][((j+dy[l]*steps)%n+n)%n][l]%MOD2) % MOD2;
                    }
                }
            }
            steps += (1 << x);
        }
    }
    map<ll, int> hashes;
    F0R(i, m) {
        F0R(j, n) {
            F0R(l, 8) {
                hashes[curHash[i][j][l]*MOD2+curHash2[i][j][l]]++;
            }
        }
    }

    ll validHashes = 0, totHashes = (ll)n*m*8*n*m*8;
    trav(x, hashes) {
        validHashes += (ll)x.pB*x.pB;
    }
    ll den = __gcd(validHashes, totHashes);
    pr(validHashes/den, "/", totHashes/den, "\n");

    return 0;
}
