/*
 * Same solution as editorial. Note that if a square is a killer square, then a smaller square sharing
 * the same center is also a killer square. Therefore, we brute force all 1x1 squares as the center, and also
 * all 2x2 squares as the center, of a possible killer square and just keep expanding.
 *
 * Naively this takes O(N^4) but we can optimize by: For each cell (x, y), in each of the four directions,
 * we store a 64 bit integer representing 64 cells in each of the four directions. Therefore we can speed
 * up the checking process by a factor of 64.
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

int r, c;
int A[300][300];
ll mask[300][300][4]; // stores 60 bits in the four directions
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int ans = -1;

void init() {
    F0R(i, r) {
        F0R(j, c) {
            F0R(k, 4) {
                int x = i, y = j;
                int ctr = 0;
                ll num = 0;
                while (x >= 0 && x < r && y >= 0 && y < c && ctr < 60) {
                    num += ((ll)A[x][y] << ctr);
                    x += dx[k]; y += dy[k];
                    ctr++;
                }
                mask[i][j][k] = num;
            }
        }
    }
}

void solve(int x, int y, int size) {
    if (size == 1) {
        if (x+1<r && y+1<c && A[x][y] == A[x+1][y+1] && A[x+1][y] == A[x][y+1]){}
        else return;
    }
    int expand = 0;
    while (true) {
        expand++;
        if (x+size+expand >= r || y+size+expand >= c || x-expand < 0 || y-expand < 0) {
            break;
        }
        bool bad = false;
        // top row: A[x-expand][y-expand] to A[x-expand][y+size+expand]
        // bottom row: A[x+size+expand][y-expand] to A[x+size+expand][y+size+expand]
        int mx = y+size+expand - (y-expand);
        for (int i = 0; i <= mx; i += 60) {
            ll topRow = mask[x-expand][y-expand+i][1];
            ll botRow = mask[x+size+expand][y+size+expand-i][3];
            int length = min(60, mx - i) + 1;
            ll m = (1LL << length) - 1;
            if ((topRow & m) != (botRow & m)) {
                bad = true;
                break;
            }
        }
        // left row: A[x-expand][y-expand] to A[x+size+expand][y-expand]
        // right row: A[x-expand][y+size+expand] to A[x+size+expand][y+size+expand]
        mx = x+size+expand - (x-expand);
        for (int i = 0; i <= mx; i += 60) {
            ll leftRow = mask[x-expand+i][y-expand][2];
            ll rightRow = mask[x+size+expand-i][y+size+expand][0];
            int length = min(60, mx - i) + 1;
            ll m = (1LL << length) - 1;
            if ((leftRow & m) != (rightRow & m)) {
                bad = true;
                break;
            }
        }
        if (bad) break;
    }
    int newAns = 1 + size + (expand-1)*2;
    if (newAns <= 1) return;
    MAX(ans, newAns);
}

int main() {
    setupIO();

    re(r, c);
    F0R(i, r) {
        F0R(j, c) {
            char c; re(c);
            A[i][j] = c-'0';
        }
    }

    init();
    F0R(i, r) {
        F0R(j, c) {
            F0R(k, 2) {
                solve(i, j, k);
            }
        }
    }
    ps(ans);

    return 0;
}