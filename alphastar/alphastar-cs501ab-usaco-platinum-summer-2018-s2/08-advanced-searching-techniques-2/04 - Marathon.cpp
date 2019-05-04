/*
Marathon
========

An avid marathon runner herself, Bessie enjoys creating marathon
courses for her fellow cows to run.  She has most recently designed a
route specified by N checkpoints (1 <= N <= 100,000) that must be
visited in sequence.

Unfortunately, Bessie realizes that the other cows may not have the
stamina to run the full route. She therefore wants to know how long
certain sub-routes take to run, where a sub-route is a contiguous
subsequence of the checkpoints from the full route.  To make matters
more complicated, Bessie knows that the other cows, being lazy, might
choose to skip one checkpoint any time they run a sub-route --
whichever one results in a minimum total travel time.  They are not
allowed to skip the first or last checkpoints in a sub-route, however.

In order to build the best possible marathon course, Bessie wants to
investigate the ramifications of making changes to the checkpoint
locations in her current course.  Please help her determine how
certain changes to checkpoint locations will affect the time required
to run different sub-routes (taking into account that the cows might
choose to omit one checkpoint any time they run a sub-route).

Since the course is set in a downtown area with a grid of streets, the
distance between two checkpoints at locations (x1, y1) and (x2, y2) is
given by |x1-x2| + |y1-y2|.

PROBLEM NAME: marathon

INPUT:

The first line gives N and Q (1 <= Q <= 100,000).

The next N lines contain (x, y) locations of N checkpoints in the
sequence they must be visited along the route.  All coordinates
are in the range -1000 .. 1000.

The next Q lines consist of updates and queries, one per line, to be
processed in the order they are given. Lines will either take the form
"U I X Y" or "Q I J".  A line of the form "U I X Y" indicates that the
location of checkpoint I (1 <= I <= N) is to be changed to location
(X, Y).  A line of the form "Q I J" asks for the minimum travel time
of the sub-route from checkpoint I to checkpoint J (I <= J), given
that the cows choose to skip one checkpoint along this sub-route (but
not the endpoints I and J).

SAMPLE INPUT:

5 5
-4 4
-5 -3
-1 5
-3 4
0 5
Q 1 5
U 4 0 1
U 4 -1 1
Q 2 4
Q 1 4

OUTPUT:

For each sub-route length request, output on a single line the desired
length.

SAMPLE OUTPUT:

11
8
8
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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A;            // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; }     // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R)                            // as L == R, either one is fine
            st[p] = L;                                         // store the index
        else {                                // recursively compute the values
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] >= A[p2]) ? p1 : p2;
        } }

    int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
        if (i >  R || j <  L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;   // if we try to access segment outside query
        if (p2 == -1) return p1;                               // same as above
        return (A[p1] >= A[p2]) ? p1 : p2; }          // as as in build routine

    int update_point(int p, int L, int R, int idx, int new_value) {
        // this update code is still preliminary, i == j
        // must be able to update range in the future!
        int i = idx, j = idx;

        // if the current interval does not intersect
        // the update interval, return this st node value!
        if (i > R || j < L)
            return st[p];

        // if the current interval is included in the update range,
        // update that st[node]
        if (L == i && R == j) {
            A[i] = new_value; // update the underlying array
            return st[p] = L; // this index
        }

        // compute the minimum pition in the
        // left and right part of the interval
        int p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        // return the pition where the overall minimum is
        return st[p] = (A[p1] >= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    // initialization: n + 1 zeroes, ignore index 0
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {                                     // returns RSQ(1, b)
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {                              // returns RSQ(a, b)
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
    void adjust(int k, int v) {                    // note: n = ft.size() - 1
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

int dist(ii a, ii b) {
    return abs(a.A - b.A) + abs(a.B - b.B);
}

int main() {
    int n, q; cin >> n >> q;
    ii coords[n];
    for (int i = 0; i < n; i++) cin >> coords[i].A >> coords[i].B;
    vector<int> distances; distances.resize(n);
    for (int i = 1; i < n; i++) {
        distances[i] = dist(coords[i - 1], coords[i]);
    }
    FenwickTree ft(n);
    for (int i = 1; i < n; i++) {
        ft.adjust(i, distances[i]);
    }
    vector<int> gainedByRemoving; gainedByRemoving.resize(n);
    for (int i = 1; i < n - 1; i++) {
        gainedByRemoving[i] = ft.rsq(i, i + 1) - dist(coords[i - 1], coords[i + 1]);
    }
    SegmentTree st(gainedByRemoving);

    for (int i = 0; i < q; i++) {
        char op; cin >> op;
        if (op == 'Q') {
            int a, b; cin >> a >> b; a--; b--;
            cout << ft.rsq(a+1, b) - gainedByRemoving[st.rmq(a + 1, b - 1)] << endl;
        } else {
            int idx, x, y; cin >> idx >> x >> y; idx--;
            coords[idx].A = x; coords[idx].B = y;
            if (idx != 0) {
                ft.adjust(idx, dist(coords[idx - 1], coords[idx]) - distances[idx]);
                distances[idx] = dist(coords[idx - 1], coords[idx]);
            }
            if (idx != n - 1) {
                ft.adjust(idx + 1, dist(coords[idx], coords[idx + 1]) - distances[idx + 1]);
                distances[idx+1] = dist(coords[idx], coords[idx + 1]);
            }

            if (idx != n - 1 && idx != 0) {
                gainedByRemoving[idx] = ft.rsq(idx, idx + 1) - dist(coords[idx - 1], coords[idx + 1]);
                st.update_point(idx, gainedByRemoving[idx]);
            }
            if (idx >= 2) {
                gainedByRemoving[idx - 1] = ft.rsq(idx - 1, idx) - dist(coords[idx - 2], coords[idx]);
                st.update_point(idx - 1, gainedByRemoving[idx - 1]);
            }
            if (idx + 2 < n) {
                gainedByRemoving[idx + 1] = ft.rsq(idx + 1, idx + 2) - dist(coords[idx], coords[idx + 2]);
                st.update_point(idx + 1, gainedByRemoving[idx + 1]);
            }
        }
    }
    return 0;
}
