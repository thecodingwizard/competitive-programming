/*
 * Similar idea to editorial
 *
 * Define dp(i, j) to be the min length of code to encode everything from [0...i] and end with encoding number j
 * Transitions are same as described in editorial
 *
 * Note that dp(i, j) ==> dp(i+1, j): All dp values change by the same amount EXCEPT for when j = the number at index i
 *
 * We need to be able to find the minimum DP value fast
 *
 * Therefore instead of storing the actual DP value, we store the difference between the DP value and the "base"
 * dp value (ie the value that all DP values change by except one)
 *
 * We put all the DP values into a set in order to find the minimum DP value (Not very efficient but CSES is generous
 * and it passes in time)
 *
 * At each index we update dp(i, the number at index i) only; everything else changes by the same amount
 * so we can update the "base" dp value
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

int n, m;
vector<pair<int, ll>> sequence;
vl dp;
vi dpParent;

void addToSequence(int num, ll ct) {
    if (!sequence.empty() && sequence.back().pA == num) {
        sequence.back().pB += ct;
    } else {
        sequence.pb({num, ct});
    }
}
void readInput() {
    int repeater = 0;
    bool active = false;
    int target = -1;
    F0R(i, m) {
        int x; cin >> x;
        if (active) {
            if (target == -1) target = x;
            else {
                if (target == repeater) {
                    addToSequence(target, x+1);
                } else {
                    if (x == 0) {
                        repeater = target;
                    } else {
                        addToSequence(target, x + 3);
                    }
                }

                active = false;
                target = -1;
            }
        } else if (x != repeater) {
            addToSequence(x, 1);
        } else {
            active = true;
        }
    }
}

ll encCost(int num, ll ct, int repeater) {
    if (num != repeater) {
        ll blockSz = n + 2;
        ll remainder = ct % blockSz;
        if (remainder < 3) {
            return ct/blockSz*3 + remainder;
        } else {
            return ct/blockSz*3+3;
        }
    } else {
        ll blockSz = n;
        return (ct+blockSz-1)/blockSz*3;
    }
}

void addNumbers(pair<int, ll> seq, int rep, vi &arr) {
    int num = seq.pA; ll ct = seq.pB;
    while (ct > 0) {
        if (num == rep) {
            arr.pb(min((ll)n-1, ct-1));
            arr.pb(num);
            arr.pb(rep);
            ct -= min((ll)n-1, ct-1) + 1;
        } else {
            if (ct <= 3) {
                arr.pb(num);
                ct--;
            } else {
                arr.pb(min((ll)n-1, ct-3));
                arr.pb(num);
                arr.pb(rep);
                ct -= min((ll)n-1, ct-3) + 3;
            }
        }
    }
}

int main() {
    setupIO("rle");

    re(n, m);
    readInput();

    dp.assign(n, 0);
    dpParent.resz(sz(sequence));

    ll baseSum = 0;
    set<pair<ll, int>> vals;
    F0R(i, sz(sequence)) {
        int num = sequence[i].pA; ll ct = sequence[i].pB;
        baseSum += encCost(num, ct, -1);

        if (i == 0) {
            F0R(j, n) {
                if (num != j) {
                    dp[j] += (j==0?0:3);
                    vals.insert({dp[j], j});
                }
            }
        }

        if (i == 0) {
            dp[num] = 3; dpParent[i] = 0;

            ll v = (num==0?0:3) + encCost(num, ct, num) - encCost(num, ct, -1);
            if (v < dp[num]) {
                dp[num] = v;
                dpParent[i] = num;
            }

            vals.insert({ dp[num], num });
        } else {
            ll prevDPVal = dp[num];

            vals.erase({prevDPVal, num});

            ll prevMin = vals.begin()->pA;
            int prevMinParent = vals.begin()->pB;

            dp[num] = prevMin + 3;
            dpParent[i] = prevMinParent;

            ll v = prevDPVal + encCost(num, ct, num) - encCost(num, ct, -1);
            if (v < dp[num]) {
                dp[num] = v;
                dpParent[i] = num;
            }

            vals.insert({ dp[num], num });
        }
    }

    ll ans = LL_INF;
    int cur;
    F0R(i, n) {
        int val = dp[i] + baseSum;
        if (ans > val) {
            ans = val;
            cur = i;
        }
    }
    ps(ans);
    vi stuff;
    F0Rd(i, sz(sequence)) {
        int par = cur;
        if (par == sequence[i].pA) {
            par = dpParent[i];
        }
        if (cur != par) {
            stuff.pb(0);
            stuff.pb(cur);
            stuff.pb(par);
            cur = par;
        }
        addNumbers(sequence[i], cur, stuff);
//        psD(sequence[i], cur, stuff);
    }
    reverse(all(stuff));
    ps(stuff);

    return 0;
}