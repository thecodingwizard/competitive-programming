/*
 * Official solution is different... They seemed to manage to do the problem w/o lazy seg tree :P
 *
 * You can do prefix sums: for each shape, starting from the bottom left corner, each vertex has value +1, -1, +1, -1, etc
 *
 * By looking at a few examples, you can see that ps[a][b] = the depth at (a, b), so we just need to generate these prefix
 * sums and find the max value.
 *
 * However there are at most 200,000 points which means normal prefix sums are too slow.
 *
 * Instead we can sort all the points by increasing x then increasing y, and use a lazy max seg tree to store
 * the values at the particular x we are processing.
 *
 * Overkill, probably a neat way to do it without seg tree...
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

#define DONE 0
class MaxSegTree {
private: vi st, lazy, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = A[L];
        else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = max(p1, p2);
        } }

    int rmq(int p, int L, int R, int i, int j) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p];

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return INF;
        if (L >= i && R <= j) return st[p];

        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return max(p1, p2); }

    int update_point(int p, int L, int R, int idx, int new_value) {
        int i = idx, j = idx;

        if (i > R || j < L)
            return st[p];

        if (L == i && R == j) {
            A[i] = new_value;
            return st[p] = L;
        }

        int p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
    }

    int update_range(int p, int L, int R, int i, int j, int val) {
        if (lazy[p] != DONE) {
            st[p] += lazy[p];

            if (L != R) {
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p];

        if (L >= i && R <= j) {
            st[p] += val;

            if (L != R) {
                lazy[left(p)] += val;
                lazy[right(p)] += val;
            }

            return st[p];
        }

        int p1, p2;
        p1 = update_range(left(p) , L              , (L + R) / 2, i, j, val);
        p2 = update_range(right(p), (L + R) / 2 + 1, R          , i, j, val);

        return st[p] = max(p1, p2);
    }

public:
    MaxSegTree(const vi &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }

    // note: adds val to all elements within range
    //       does not override elements
    int update_range(int start, int end, int val) {
        return update_range(1, 0, n - 1, start, end, val); }
};

//int A[1000][1000];
int main() {
    setupIO();

//    SET2D(A, 0, 1000, 1000);
    int n; re(n);
    set<int> yCmp;
    map<int, map<int, int>> points;
    vector<vii> allpts;
    F0R(i, n) {
        int k; re(k);
        int prev = -1;
        int first;
        vii pts;
        F0R(j, k) {
            int x; re(x);
            yCmp.insert(x);
            if (prev == -1) {
                first = x;
                prev = x; continue;
            }
            if (j & 1) {
                pts.pb(mp(prev, x));
            } else {
                pts.pb(mp(x, prev));
            }
            prev = x;
        }
        pts.pb(mp(first, prev));
        allpts.pb(pts);
    }
    map<int, int> yMap;
    int c = 0;
    for (int x : yCmp) yMap[x] = c++;
    for (auto pts : allpts) {
        int smallest = -1;
        F0R(i, sz(pts)) {
            if (smallest == -1) {
                smallest = i;
            }
            if (pts[i] < pts[smallest]) smallest = i;
        }
        F0R(i, sz(pts)) {
            int x = pts[(i + smallest) % sz(pts)].pA, y = pts[(i + smallest) % sz(pts)].pB;
            y = yMap[y];
            points[x][y] += (i & 1 ? -1 : 1);
//            A[x][y] += (i & 1 ? -1 : 1);
        }
    }

    vi dd; dd.resz(c);
    MaxSegTree st(dd);
    int ans = 0;
    for (auto x : points) {
        for (auto yy : x.pB) {
            int y = yy.pA, v = yy.pB;
            st.update_range(y, c - 1, v);
        }
        MAX(ans, st.rmq(0, c - 1));
    }
    ps(ans);

//    ans = 0;
//    F0R(i, 1000) {
//        F0R(j, 1000) {
//            A[i][j] += (i > 0 ? A[i - 1][j] : 0) + (j > 0 ? A[i][j - 1] : 0) - (i > 0 && j > 0 ? A[i - 1][j - 1] : 0);
//            MAX(ans, A[i][j]);
//        }
//    }
//    if (n >= 1000) {
//        ps("Check:", ans);
//    } else {
//        ps(ans);
//    }

    return 0;
}