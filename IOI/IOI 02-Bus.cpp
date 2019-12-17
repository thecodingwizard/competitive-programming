/*
 * Same solution as editorial
 *
 * Brute force the two hubs h1 and h2. Calculate distance from each hub to every node: d1[x] = dist from h1 to x, likewise for d2
 *
 * Let's say we have assigned each node to one of the two hubs. Then our answer for this assignment is
 * max(max_h1 + second_max_h1, max_h2 + second_max_h2, max_h1 + max_h2 + dist_h1_to_h2)
 *
 * Note that our assignment only depends on max_h1, second_max_h1, max_h2, and second_max_h2 (this is assuming h1 and h2 are fixed).
 * If we brute force all possible options for max_h1 and second_max_h1, then the optimal strategy is:
 * - For every node x, if d1[x] <= second_max_h1, assign it to the first hub. Otherwise, assign it to the second hub.
 *
 * This algorithm is O(n^5), but we can optimize it. We can fix max_h1. Start by assigning all nodes to h1.
 * Sort all the nodes by their distance to h1. In decreasing order of their distance, we will process each node, setting
 * that node as second_max_h1. After we finish updating the best answer, we move that node to h2 and continue. This is O(n^4).
 *
 * Now notice that, for a fixed max_h1, if moving second_max_h1 to h2 leads to a worse answer than what we had before,
 * then we shouldn't change second_max_h1, and we can exit early. Further note that if we process max_h1 in decreasing
 * order, then when we hit the second_max_h1 that will lead to a worse answer, second_max_h1 is the next max_h1 we should
 * process. Therefore we have O(n^3)
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

int n;
ii A[500];
int best = INF;
int d1[500], d2[500];

int getDist(ii a, ii b) {
    return abs(b.pA - a.pA) + abs(b.pB - a.pB);
}

void run(int h1, int h2) {
    vii d1Vals;
    F0R(i, n) {
        d1[i] = getDist(A[i], A[h1]);
        if (i != h2 && i != h1) d1Vals.pb({d1[i], i});
        d2[i] = getDist(A[i], A[h2]);
    }
    sort(all(d1Vals));

    int maxD2 = 0, secondMaxD2 = 0, d_12 = d1[h2];

    // Strategy: Set largest d1val as the max d1.
    // Keep decreasing the second largest d1val until our answer gets bigger.
    // Then set that as the largest d1val and go again.
    for (int maxD1Idx = sz(d1Vals)-1; maxD1Idx >= 0; maxD1Idx--) {
        int curAns = maxD2 + secondMaxD2;
        MAX(curAns, d1Vals[maxD1Idx].pA + maxD2 + d_12);
        if (maxD1Idx - 1 >= 0) {
            MAX(curAns, d1Vals[maxD1Idx].pA + d1Vals[maxD1Idx - 1].pA);
        }

        int numBusesToMove = 0;
        while (true) {
            int curAns2 = maxD2 + secondMaxD2;
            int newSecondIdx = maxD1Idx - numBusesToMove - 1;
            if (newSecondIdx < 0) break;
            if (newSecondIdx - 1 >= 0) {
                MAX(curAns2, d1Vals[maxD1Idx].pA + d1Vals[newSecondIdx - 1].pA);
            }
            int removedIdx = d1Vals[newSecondIdx].pB;
            MAX(curAns2, d1Vals[maxD1Idx].pA + max(maxD2, d2[removedIdx]) + d_12);
            if (curAns2 > curAns) break;

            // add removedIdx to d2
            if (d2[removedIdx] > maxD2) {
                secondMaxD2 = maxD2;
                maxD2 = d2[removedIdx];
            } else if (d2[removedIdx] > secondMaxD2) {
                secondMaxD2 = d2[removedIdx];
            }

            curAns = curAns2;
            numBusesToMove++;
        }

        MIN(best, curAns);

        // add maxD1Idx to d2
        int idxToAdd = d1Vals[maxD1Idx].pB;
        if (d2[idxToAdd] > maxD2) {
            secondMaxD2 = maxD2;
            maxD2 = d2[idxToAdd];
        } else if (d2[idxToAdd] > secondMaxD2) {
            secondMaxD2 = d2[idxToAdd];
        }

        maxD1Idx -= numBusesToMove;
    }
}

int main() {
    setupIO();

    re(n);
    F0R(i, n) re(A[i]);

    F0R(i, n) {
        FOR(j, i, n) {
            run(i, j);
        }
    }

    ps(best);

    return 0;
}