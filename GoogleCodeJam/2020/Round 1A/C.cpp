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

struct node {
    int idx, val;
    node *before, *after;
};

int ct = 0;

void solve() {
    int r, c;
    re(r, c);
    // ct++;
    // if (ct <= 10) {
        // r = rand()%300 + 1;
        // c = 100000/r;
    // } else {
        // r = 10, c = 10;
    // }
    int A[r][c];
    int B[r][c];
    node* rowNodes[r][c];
    node* colNodes[r][c];
    vector<ii> needsUpdating[2];
    ll toAdd = 0;
    F0R(i, r) {
        F0R(j, c) {
            int v;
            re(v);
            // v = rand() % 1000000 + 1;
            A[i][j] = v;
            rowNodes[i][j] = new node();
            rowNodes[i][j]->idx = j; rowNodes[i][j]->val = v;
            colNodes[i][j] = new node();
            colNodes[i][j]->idx = i; colNodes[i][j]->val = v;
            needsUpdating[0].pb({i,j});
            toAdd += v;
            B[i][j] = -1;
        }
    }
    F0R(i, r) {
        F0R(j, c) {
            rowNodes[i][j]->before = (j-1<0?nullptr:rowNodes[i][j-1]);
            rowNodes[i][j]->after = (j+1>=c?nullptr:rowNodes[i][j+1]);
            colNodes[i][j]->before = (i-1<0?nullptr:colNodes[i-1][j]);
            colNodes[i][j]->after = (i+1>=r?nullptr:colNodes[i+1][j]);
        }
    }
    ll ans = 0;
    int curIdx = 0;
    vii toErase;
    int iteration = 0;
    while (sz(needsUpdating[curIdx]) != 0) {
        ans += toAdd;
        iteration++;

        needsUpdating[!curIdx].clear();
        trav(cell, needsUpdating[curIdx]) {
            if (A[cell.pA][cell.pB] == -1) continue;
            if (B[cell.pA][cell.pB] == iteration) continue;
            B[cell.pA][cell.pB] = iteration;

            int up = colNodes[cell.pA][cell.pB]->before == nullptr ? -1 : colNodes[cell.pA][cell.pB]->before->idx;
            int down = colNodes[cell.pA][cell.pB]->after == nullptr ? INF : colNodes[cell.pA][cell.pB]->after->idx;
            int left = rowNodes[cell.pA][cell.pB]->before == nullptr ? -1 : rowNodes[cell.pA][cell.pB]->before->idx;
            int right = rowNodes[cell.pA][cell.pB]->after == nullptr ? INF : rowNodes[cell.pA][cell.pB]->after->idx;
            
            int ct = (up == -1 ? 0 : 1) + (down == INF ? 0 : 1) + (left == -1 ? 0 : 1) + (right == INF ? 0 : 1);
            ll sum = (up == -1 ? 0 : A[up][cell.pB]) + (down == INF ? 0 : A[down][cell.pB]) + (left == -1 ? 0 : A[cell.pA][left]) + (right == INF ? 0 : A[cell.pA][right]);

            if (ct > 0 && (ll)A[cell.pA][cell.pB]*ct < sum) {
                toAdd -= A[cell.pA][cell.pB];

                toErase.pb(cell);

                if (up != -1) needsUpdating[!curIdx].pb(mp(up, cell.pB));
                if (down != INF) needsUpdating[!curIdx].pb(mp(down, cell.pB));
                if (left != -1) needsUpdating[!curIdx].pb(mp(cell.pA, left));
                if (right != INF) needsUpdating[!curIdx].pb(mp(cell.pA, right));
            }
        }

        trav(cell, toErase) {
            if (colNodes[cell.pA][cell.pB]->before != nullptr) colNodes[cell.pA][cell.pB]->before->after = colNodes[cell.pA][cell.pB]->after;
            if (colNodes[cell.pA][cell.pB]->after != nullptr) colNodes[cell.pA][cell.pB]->after->before = colNodes[cell.pA][cell.pB]->before;
            if (rowNodes[cell.pA][cell.pB]->before != nullptr) rowNodes[cell.pA][cell.pB]->before->after = rowNodes[cell.pA][cell.pB]->after;
            if (rowNodes[cell.pA][cell.pB]->after != nullptr) rowNodes[cell.pA][cell.pB]->after->before = rowNodes[cell.pA][cell.pB]->before;
            A[cell.pA][cell.pB] = -1;
        }
        toErase.clear();

        curIdx = !curIdx;
    }
    ps(ans);
    // psD("time:", time(0));
}

int main() {
    setupIO();

    int t; re(t);
    F0R1(i, t) {
        pr("Case #", i, ": ");
        solve();
    }

    return 0;
}











