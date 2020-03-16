/*
 * Same solution as editorial
 *
 * Time limit is a bit tight; use int instead of long long and cast to long long when necessary
 *
 * Make each node of the seg tree an array of 11 integers; don't make 11 seg trees
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

ll ncr[11][11];
int n, K;

struct SegTree {
public:
    vector<array<int, 11>> st;
    vl lazy;

    void init(int sz) {
        st.resize(4*sz);
        F0R(i, 4*sz) {
            F0R(j, K+1) st[i][j] = 0;
        }
        lazy.assign(4*sz, 1);
    }

    void down(int p, int L, int R) {
        if (lazy[p] == 1) return;
        F0R(i, K+1) st[p][i] = ((ll)st[p][i]*lazy[p]) % MOD;
        if (L != R) {
            lazy[(p << 1)] = lazy[(p << 1)] * lazy[p] % MOD;
            lazy[(p << 1) + 1] = lazy[(p << 1) + 1] * lazy[p] % MOD;
        }
        lazy[p] = 1;
    }

    void pointUpd(int p, int L, int R, int k, array<int, 11> v) {
        down(p, L, R);
        if (R < k || L > k) return;
        if (L == R && L == k) {
            st[p] = v;
        } else {
            pointUpd(p << 1, L, (L+R)/2, k, v);
            pointUpd((p << 1) + 1, (L+R)/2+1, R, k, v);
            F0R(i, K+1) {
                ll tmp = (ll)st[p << 1][i] + st[(p<<1)+1][i];
                st[p][i] = tmp >= MOD ? tmp-MOD : tmp;
            }
        }
    }

    void pointAdj(int p, int L, int R, int k, array<int, 11> v) {
        down(p, L, R);
        if (R < k || L > k) return;
        if (L == R && L == k) {
            F0R(i, K+1) {
                ll tmp = (ll)st[p][i] + v[i];
                st[p][i] = tmp >= MOD ? tmp-MOD : tmp;
            }
        } else {
            pointAdj(p << 1, L, (L+R)/2, k, v);
            pointAdj((p << 1) + 1, (L+R)/2+1, R, k, v);
            F0R(i, K+1) {
                ll tmp = (ll)st[p << 1][i] + st[(p<<1)+1][i];
                st[p][i] = tmp >= MOD ? tmp-MOD : tmp;
            }
        }
    }

    array<int, 11> pointQry(int p, int L, int R, int k) {
        assert(L <= k && k <= R);
        down(p, L, R);
        if (L == R && L == k) return st[p];
        int mid = (L+R)/2;
        if (k <= mid) return pointQry(p << 1, L, mid, k);
        else return pointQry((p << 1) + 1, mid+1, R, k);
    }

    array<int, 11> rangeQry(int p, int L, int R, int i, int j) {
        down(p, L, R);
        if (R < i || L > j) {
            array<int, 11> toReturn;
            F0R(x, K+1) toReturn[x] = 0;
            return toReturn;
        }
        if (i <= L && R <= j) return st[p];
        array<int, 11> tmp = rangeQry(p << 1, L, (L+R)/2, i, j);
        array<int, 11> tmp2 = rangeQry((p << 1) + 1, (L+R)/2+1, R, i, j);
        array<int, 11> final;
        F0R(i, K+1) {
            ll x = tmp[i] + tmp2[i];
            final[i] = x >= MOD ? x-MOD : x;
        }
        return final;
    }

    void rangeMultiply(int p, int L, int R, int i, int j, int mult) {
        if (R < i || L > j) return;
        if (i <= L && R <= j) {
            lazy[p] = (lazy[p] * mult) % MOD;
        } else {
            rangeMultiply((p << 1), L, (L+R)/2, i, j, mult);
            rangeMultiply((p << 1) + 1, (L+R)/2+1, R, i, j, mult);
            down(p << 1, L, (L+R)/2); down((p << 1) + 1, (L+R)/2+1, R);
            F0R(x, K+1) {
                ll tmp = st[p << 1][x] + st[(p << 1) + 1][x];
                st[p][x] = tmp > MOD ? tmp-MOD : tmp;
            }
        }
    }
};

SegTree dp;
SegTree adv;

int main() {
    setupIO("help");

    re(n, K);
    vector<pair<ll, ll>> A;
    F0R(i, n) {
        int a, b; re(a, b); A.pb({a,b});
    }
    sort(all(A));

    SET2D(ncr, 0, 11, 11);
    F0R(i, 11) {
        ncr[i][0] = 1;
        F0R1(j, i) {
            ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
            if (ncr[i][j] >= MOD) ncr[i][j] -= MOD;
        }
    }

    dp.init(2*n);
    adv.init(2*n);
    array<int, 11> initArr; F0R(i, K+1) initArr[i] = 1;
    adv.pointUpd(1, 0, 2*n, 0, initArr);

    trav(x, A) {
        dp.pointAdj(1, 0, 2*n, x.pB, adv.rangeQry(1, 0, 2*n, 0, x.pA-1));
        dp.pointAdj(1, 0, 2*n, x.pB, dp.rangeQry(1, 0, 2*n, x.pA, x.pB-1));

        array<int, 11> dpvals = dp.pointQry(1, 0, 2*n, x.pB);
        array<int, 11> toUpd;
        F0R(i, K+1) {
            ll val = 0;
            F0R(j, i+1) {
                val = (val + ncr[i][j]*dpvals[j]) % MOD;
            }
            toUpd[i] = val;
        }
        adv.pointUpd(1, 0, 2*n, x.pB, toUpd);
        dp.rangeMultiply(1, 0, 2*n, x.pB+1, 2*n, 2);
        adv.rangeMultiply(1, 0, 2*n, x.pB+1, 2*n, 2);
    }

    ps(dp.rangeQry(1, 0, 2*n, 1, 2*n)[K]);

    return 0;
}