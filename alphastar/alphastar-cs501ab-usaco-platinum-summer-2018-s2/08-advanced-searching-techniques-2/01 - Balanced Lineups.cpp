/*
Balanced Lineup
===============

For the daily milking, Farmer John's N cows (1 <= N <= 50,000)
always line up in the same order. One day Farmer John decides to
organize a game of Ultimate Frisbee with some of the cows. To keep
things simple, he will take a contiguous range of cows from the
milking lineup to play the game. However, for all the cows to have
fun, they should not differ too much in height.

Farmer John has made a list of Q (1 <= Q <= 180,000) potential
groups of cows and their heights (1 <= height <= 1,000,000). For
each group, he wants your help to determine the difference in height
between the shortest and the tallest cow in the group.

Note: on the largest test case, I/O takes up the majority of the
runtime.

PROBLEM NAME: lineupg

INPUT FORMAT:

* Line 1: Two space-separated integers, N and Q.

* Lines 2..N+1: Line i+1 contains a single integer that is the height
        of cow i

* Lines N+2..N+Q+1: Two integers A and B (1 <= A <= B <= N),
        representing the range of cows from A to B inclusive.

SAMPLE INPUT:

6 3
1
7
3
4
2
5
1 5
4 6
2 2


OUTPUT FORMAT:

* Lines 1..Q: Each line contains a single integer that is an answer to
        an input query and tells the difference in height between the
        tallest and shortest cow in the input range.

SAMPLE OUTPUT:

6
3
0
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

class MinSegmentTree {         // the segment tree is stored like a heap array
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
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        } }

    int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
        if (i >  R || j <  L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;   // if we try to access segment outside query
        if (p2 == -1) return p1;                               // same as above
        return (A[p1] <= A[p2]) ? p1 : p2; }          // as as in build routine

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
        return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
    }

public:
    MinSegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

class MaxSegmentTree {         // the segment tree is stored like a heap array
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
    MaxSegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

int main() {
    ios_base::sync_with_stdio(false);

    int n, q; cin >> n >> q;
    vector<int> cows; cows.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }

    MinSegmentTree minST(cows);
    MaxSegmentTree maxST(cows);

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--; b--;
        cout << cows[maxST.rmq(a, b)] - cows[minST.rmq(a, b)] << endl;
    }

    return 0;
}
