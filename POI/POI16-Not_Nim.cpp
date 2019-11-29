/*
 * Same solution as editorial
 *
 * Player A wants to end game in fewest moves, player B wants to stall
 * - With pen and paper we get that if player A repeatedly removes stones from one pair until it's gone,
 *   a pair of n stones will take him floor(log2(n))*2 + 4 steps
 * - However, after one stack of stones is gone, player B will have to "upset" the balance of one stack of stones.
 *   This can reduce the number of moves it takes to remove that stack of stones. For example, if our
 *   stones was (1 1) (1 1) it would take only 5 moves, not 7, because after the first pair of stones is gone
 *   Player B will be forced to change the second set from (1 1) to (2 0) reducing the answer by 2
 * - Our strategy is: Create a "base" answer by summing floor(log2(A_i))*2 + 4 for all A_i. Subtract one from
 *   this base answer since player A gets the last move. Then we need to figure out how many moves we can subtract from
 *   this base answer.
 * - If there's a pair of 1 stone (1 1) and player B is forced to rebalance it, then we can subtract two from our answer.
 * - Note that prior to the first rebalancing, player A can remove stones s.t. each stack's new value is just
 *   the leading ones. ie if the original number was 111001101 in base 2, player A can remove stones from that stack
 *   until the number is just 111 in base 2. Therefore the only important part about each stack's number is the
 *   number of leading ones in that number.
 * - Now consider a rebalancing. Let's take the number 7 as an example. If player B rebalances (7 7), then it will
 *   eventually become (3 3):  (7 7) -> (8 6) -> (0 6) -> (3 3) In other words, rebalancing a stack of stones with n
 *   leading ones will result in a new stack with (n-1) leading stacks. However, if there is only one leading one (ie
 *   if player B is rebalancing a stack with only one stone) then we can subtract two from the answer.
 * - Player B must rebalance once after each stack of stones is removed completely.
 * - Note that Player B will always rebalance the stack of stones with the most number of leading ones since that
 *   prolongs the time until it reaches (1 1)
 * - Note that Player A will always choose to remove the stack of stone with the most number of leading ones since
 *   that stack takes lots of rebalancings before it reaches (1 1)
 *
 * Therefore, our solution is:
 * 1. Calculate the base answer
 * 2. Create a priority queue. Each stack is represented as the number of leading ones of the number of stones in that stack.
 *    Pop the biggest number from the priority queue since player A must remove one stack of stones before player B does
 *    the first rebalancing.
 * 3. While the priority queue is not empty, take the pair of stones with the most number of leading ones and process it:
 *    3a. If that pair of stones has one leading ones, then the rebalancing will lead 2 fewer moves. answer -= 2.
 *    3b. If the pair of stones has more than one leading ones, then the rebalancing will result in a new stack with
 *        one fewer leading one. Insert a new element into the priority queue with value n-1. Then, pop the biggest
 *        element from the priority queue since player A will have to remove another set of stones before the next rebalancing.
 *
 * Also see code comments
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

int main() {
    setupIO();

    int n; re(n);
    ll A[n]; reA(A, n);

    /* Generate the base answer */
    ll ans = -1; // Since player A gets the last move we subtract one from the base answer
    F0R(i, n) {
        ans += floor(log2(A[i])) * 2 + 4;
    }

    priority_queue<int> pq;

    // For each input number, insert the number of leading ones into the priority queue
    F0R(i, n) {
        int numLeading = 0;
        F0Rd(j, 32) {
            if (A[i] & (1 << j)) {
                numLeading++;
            } else if (numLeading > 0) {
                break;
            }
        }
        pq.push(numLeading);
    }

    pq.pop(); // Remove the first stack in order to trigger the first rebalancing
    while (!pq.empty()) {
        // Within this loop, player B must rebalance one stack, and player A must completely remove one stack.
        // This continues until there are no more stacks.

        int u = pq.top(); pq.pop();
        if (u == 1) {
            // If the only stack player B can rebalance are stacks with one leading one, then we can subtract
            // 2 from the answer
            ans -= 2;
        } else {
            // Otherwise, player B will rebalance the stack with the most number of leading ones,
            // leading to a new stack with one less leadnig one
            pq.push(u - 1);

            // Then player A will have to completely remove one stack in order to trigger the next rebalancing.
            // Obviously player A will choose to remove the stack with the most number of leading ones.
            pq.pop();
        }
    }

    ps(ans);

    return 0;
}