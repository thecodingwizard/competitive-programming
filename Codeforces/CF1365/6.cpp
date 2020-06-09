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

ll ask(vi x) {
    if (x.size()==0)return 0;
    cout << "? " << x.size();
    for (int i : x) cout << " " << i;
    cout << endl;
    ll y; cin >> y;
    return y;
}

int main() {
    setupIO();

    int n; cin >> n;

    if (n==1) {
        cout << "! 0" << endl;
    }

    vi firstHalf, secondHalf;
    for (int i = 1; i <= n/2; i++) firstHalf.pb(i);
    for (int j = n/2+1; j <= n; j++) secondHalf.pb(j);

    ll x = ask(firstHalf), y = ask(secondHalf);
    int L[64], R[64];
    int check[64];
    F0R(i, 64) {
        bool xHas = (x&(1LL<<i)), yHas = (y&(1LL<<i));
        if (xHas == yHas) {
            if (xHas) L[i] = R[i] = -1;
            else L[i] = R[i] = -2;
            check[i] =-1;
        } else {
            if (xHas) {
                L[i] = 1, R[i] = n/2;
            } else {
                L[i] = n/2+1; R[i] = n;
            }
            check[i]=0;
        }
    }

    for (int queryCt = 3; queryCt <= 11; queryCt++) {
        set<int> toAsk;
        F0R(i, 64) {
            if (L[i] >= 0) {
                int a = L[i], b = R[i];
                if (a==b)continue;
                for (int x = a; x <= (a+b)/2; x++) {
                    toAsk.insert(x);
                }
            }
        }
        vi asdf; for (int x : toAsk) asdf.pb(x);
        ll res = ask(asdf);
        F0R(i, 64) {
            if (L[i] >= 0) {
                int a = L[i], b = R[i];
                bool has = res&(1LL<<i);
                if (has) {
                    R[i] = (a+b)/2;
                } else {
                    L[i] = (a+b)/2+1;
                }
                if (b-a==1) {
                    if (has) check[i]=b;
                    else check[i]=a;
                } else {
                }
            }
        }
    }
    vi checkAsk;
    F0R(i, 64) {
        if (check[i] > 0) {
            checkAsk.pb(check[i]);
        }
    }
    ll res = ask(checkAsk);
    F0R(i, 64) {
        if (check[i]>0) {
            if ((1LL<<i)&res) {
                L[i] = R[i] = -1;
            }
        }
    }
    set<int> bl;
    F0R(i, 64) {
        if (L[i]>0) {
            bl.insert(L[i]);
        }
    }
    vi finalAsk;
    for (int i = 1; i <= n; i++) {
        if (bl.count(i)) continue;
        finalAsk.pb(i);
    }
    res = ask(finalAsk);
    F0R(i, 64) {
        if (L[i]>0) {
            if ((1LL<<i)&&res) L[i] = R[i] = -1;
        }
    }

    cout << "!";
    F0R(i, n) {
        ll bad = x|y;
        F0R(j, 64) {
            if (L[j]==i)bad ^= (1LL<<j);
        }
        cout << " " << bad;
    }
    cout << endl;

    return 0;
}











