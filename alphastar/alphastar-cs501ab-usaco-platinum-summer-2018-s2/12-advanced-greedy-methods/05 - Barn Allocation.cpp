/*
Barn Allocation
===============

Farmer John recently opened up a new barn and is now accepting stall
allocation requests from the cows since some of the stalls have a
better view of the pastures.

The barn comprises N (1 <= N <= 100,000) stalls conveniently numbered
1..N; stall i has capacity C_i cows (1 <= C_i <= 100,000). Cow i
may request a contiguous interval of stalls (A_i, B_i) in which to
roam (1 <= A_i <= N; A_i <= B_i <= N), i.e., the cow would like to
wander among all the stalls in the range A_i..B_i (and the stalls
must always have the capacity for her to wander).

Given M (1 <= M <= 100,000) stall requests, determine the maximum
number of them that can be satisfied without exceeding stall
capacities.

Consider both a barn with 5 stalls that have the capacities shown
and a set cow requests:

Stall id:    1   2   3   4   5
           +---+---+---+---+---+
Capacity:  | 1 | 3 | 2 | 1 | 3 |
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)

FJ can't satisfy all four cows, since there are too many requests
for stalls 3 and 4.

Noting that Cow 2 requests an interval that includes stalls 3 and
4, we test the hypothesis that cows 1, 3, and 4 can have their
requested stalls. No capacity is exceeded, so the answer for this
set of data is 3 -- three cows (1, 3, and 4) can have their requests
satisfied.

PROBLEM NAME: balloc

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M
* Lines 2..N+1: Line i+1 contains a single integer: C_i
* Lines N+2..N+M+1: Line i+N+1 contains two integers: A_i and B_i

SAMPLE INPUT:

5 4
1
3
2
1
3
1 3
2 5
2 3
4 5

OUTPUT FORMAT:

* Line 1: The maximum number of requests that can be satisfied

SAMPLE OUTPUT:

3
*/

#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define DONE 0

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A, lazy;            // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; }     // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R)                            // as L == R, either one is fine
            st[p] = A[L];                                       // store the value
        else {                                // recursively compute the values
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = min(p1, p2);
        } }

    int rmq(int p, int L, int R, int i, int j) {                  // O(log n)

        if (lazy[p] != DONE) {
            st[p] += lazy[p];

            if (L != R) { // this node has children
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return INF; // current segment outside query range

        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        return min(p1, p2); }          // as as in build routine

    int update_tree(int p, int L, int R, int i, int j, int val) {
        if (lazy[p] != DONE) { // this node needs to be updated
            st[p] += lazy[p];

            if (L != R) { // this node has children
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p]; // Current segment not in range

        if (L >= i && R <= j) { // segment fully in range
            st[p] += val;

            if (L != R) { // Not leaf node
                lazy[left(p)] += val;
                lazy[right(p)] += val;
            }

            return st[p];
        }

        int p1 = update_tree(left(p), L, (L + R) / 2, i, j, val);
        int p2 = update_tree(right(p), (L + R) / 2 + 1, R, i, j, val);

        return st[p] = min(p1, p2);
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        lazy.assign(4 * n, DONE);
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_tree(int i, int j, int adjust) {
        return update_tree(1, 0, n - 1, i, j, adjust); }
};

int n, m;
vi capacity;
vii cows;

int main() {
    cin >> n >> m;
    capacity.resize(n);
    for (int i = 0; i < n; i++) cin >> capacity[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cows.push_back(mp(--a, --b));
    }
    sort(cows.begin(), cows.end(), [](ii a, ii b) {
        if (a.B == b.B) return (a.B - a.A) < (b.B - b.A);
        return a.B < b.B;
    });
    SegmentTree st(capacity);
    long long requests = 0;
    for (ii cow : cows) {
        int minInRange = st.rmq(cow.A, cow.B);
        if (minInRange < 1) continue;
        requests++;
        st.update_tree(cow.A, cow.B, -1);
    }
    cout << requests << endl;
    return 0;
}
