/*
 * String transformations ==> classes
 *
 * We can categorize molecules into "classes" such that a molecule will be able to be transformed into
 * any other molecule in its class, but won't be able to transform into a molecule that's not in it's class.
 *
 * We can write some brute force code to see if we can figure out some interesting properties about the classes.
 * We notice that there are at most 24 classes, and that each of the 24 classes has a molecule of length <= 4.
 *
 * See editorial for formal proof, but basically if all the molecules of length <= 5 are part of one of 24 classes,
 * and each of the 24 classes have at least one molecule of length <= 4, then for any molecule of length > 5
 * we can take the first five characters, transform the prefix of five characters into four characters, and repeat
 * until we end up in one of the 24 classes. And we can write brute force code to make sure that the first
 * two conditions are met.
 *
 * To solve the problem we just use the approach described above to convert a super long molecule into
 * a shorter molecule.
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

map<string, int> mClass;
string shortestMoleculeInClass[100]; // note that there are only 24 classes
set<string> seen;

void dfs(string s, int c) {
    if (s.length() > 8) return;
    if (seen.count(s)) return;
    seen.insert(s);
    if (sz(s) <= 5) {
        mClass[s] = c; // we only care about molecules length <= 5, helps save time + memory
        // note that this optimization might not be necessary oops :P
    }
    F0R(i, s.length() - 1) {
        string x; x += s[i]; x += s[i+1];
        if (x == "TC") {
            dfs(s.substr(0, i) + "A" + s.substr(i + 2), c);
        } else if (x == "AG") {
            dfs(s.substr(0, i) + "C" + s.substr(i + 2), c);
        } else if (x == "CT") {
            dfs(s.substr(0, i) + "G" + s.substr(i + 2), c);
        } else if (x == "GA") {
            dfs(s.substr(0, i) + "T" + s.substr(i + 2), c);
        }
    }
    F0R(i, s.length()) {
        char x = s[i];
        if (x == 'A') {
            dfs(s.substr(0, i) + "TC" + s.substr(i + 1), c);
        } else if (x == 'C') {
            dfs(s.substr(0, i) + "AG" + s.substr(i + 1), c);
        } else if (x == 'G') {
            dfs(s.substr(0, i) + "CT" + s.substr(i + 1), c);
        } else if (x == 'T') {
            dfs(s.substr(0, i) + "GA" + s.substr(i + 1), c);
        }
    }
}

int getClass(string s) {
    if (sz(s) <= 5) return mClass[s];
    string prefix = s.substr(0, 4);
    FOR(i, 4, sz(s)) {
        prefix = shortestMoleculeInClass[mClass[prefix + s[i]]];
    }
    return mClass[prefix];
}

int main() {
    setupIO();

    char c[4] = { 'A', 'C', 'T', 'G' };
    int ctr = 1;
    string s;
    F0R(xx, pow(4, 5)) {
        int i = xx;
        string s;
        while (true) {
            s += c[i % 4];
            i /= 4;
            if (i == 0) break;
        }
        if (mClass[s] == 0) {
            seen.clear();
            dfs(s, ctr++);
        }
    }

    // The following can help see interesting properties of classes
//    vector<string> classMolecules[100];
//    trav(x, mClass) {
//        classMolecules[x.pB].pb(x.pA);
//    }
//    FOR(i, 1, ctr) {
//        sort(all(classMolecules[i]), [](const string x, const string y) {
//            return x.length() < y.length();
//        });
//    }

    trav(x, mClass) {
        string s = shortestMoleculeInClass[x.pB];
        if (sz(s) == 0 || sz(s) > sz(x.pA)) shortestMoleculeInClass[x.pB] = x.pA;
    }

    int n; re(n);
    int classNum[n];
    F0R(i, n) {
        string s; re(s);
        classNum[i] = getClass(s);
    }
    F0R(i, n) {
        F0R(j, n) {
            if (classNum[i] == classNum[j]) {
                pr("1");
            } else {
                pr("0");
            }
        }
        ps();
    }

    return 0;
}