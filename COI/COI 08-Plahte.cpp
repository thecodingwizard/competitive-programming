/*
 * Same solution as editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2009/olympiad_solutions/solutions.pdf
 *
 * I would not recommend looking at my code implementation ;)
 */

//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

#include <utility>

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
// @formatter:on

/* ============================ */

map<ll, vector<pll>> events;

pll calc(int x1, int y1, int x2, int y2, int t) {
    if (t < x1 || t < y1) return {0,0};
    if (t >= y2 && t >= x2) return {0,0};
    int x = 0, y = 0;
    if (t < y2 && t < x2) y = 2;
    x = ((t + 1) - x1)*((t+1)-y1)-max(((t) - x1)*((t)-y1),0);
    if (t >= y2) x = y2-y1+1;
    if (t >= x2) x = x2-x1+1;
    return {x,y};
}

void process(int x1, int y1, int x2, int y2) {
    if (x1 < 0) {
        if (x2 <= 0) {
            return process(abs(x2), y1, abs(x1), y2);
        } else {
            process(0, y1, x2, y2);
            process(1, y1, abs(x1), y2);
            return;
        }
    } else if (y1 < 0) {
        if (y2 <= 0) {
            return process(x1, abs(y2), x2, abs(y1));
        } else {
            process(x1, 0, x2, y2);
            process(x1, 1, x2, abs(y1));
            return;
        }
    }
    if (x1 == x2 && y1 == y2) {
        int t = max(x1, y1);
        events[t-1].pb({1,0});
        events[t].pb({-1,0});
        return;
    }
    if (x1 == x2) {
        process(y1, x1, y2, x2);
        return;
    }
    if (y1 == y2) {
        int t = y1;
        int initial = max(min(t, x2) - x1 + 1, 0);
        if (initial > 0) {
            events[t - 1].pb({initial,0});
            events[t].pb({-initial,0});
        }
        if (t < x2) {
            events[max(t,x1-1)].pb({1, 0});
            events[x2].pb({-1, 0});
        }
        return;
    }
    vi times = {x1,y1,x2,y2}; sort(all(times));
    pll prv = { 0, 0 };
    bool second = false;
    bool first = false;
    bool alreadySecond = false;
    FOR(i, 1, sz(times)) {
        first = prv.pA == 0 && prv.pB == 0;
        if (!first && !alreadySecond) {
            second = true;
            alreadySecond = true;
        }
        if (!first) {
            prv.pA += (ll)prv.pB*(times[i]-times[i-1]);
            if (second) prv.pA += prv.pB;
            events[times[i]].pb(prv);
        }
        prv = calc(x1, y1, x2, y2, times[i]);
        events[first?times[i]-1:times[i]].pb(prv);
        prv.pA *= -1; prv.pB *= -1;
    }
}

int main() {
    setupIO();

    int n; re(n);
    F0R(i, n) {
        int x1, y1, x2, y2; re(x1, y1, x2, y2);
        process(x1, y1, x2, y2);
    }
    int m; re(m);
    ll ans = 0;
    auto it = events.begin();
    int curTime = 0;
    ll x = 0, y = 0;
    F0R(i, m) {
        int t; re(t);
        while (it != events.end() && it->pA <= t) {
            ll elapsed = it->pA - curTime;
            ans += elapsed*x; ans += (elapsed)*(elapsed-1)/2*y; x += y*(elapsed);
            trav(xx, it->pB) {
                x += xx.pA; y += xx.pB;
            }
            curTime = it->pA;
            it++;
        }
        ll elapsed = t - curTime;
        ans += elapsed*x; ans += (elapsed)*(elapsed-1)/2*y; x+=y*(elapsed);
        curTime = t;
        ps(ans);
    }

    return 0;
}