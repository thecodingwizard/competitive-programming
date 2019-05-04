/*
Light Switching
===============

Farmer John tries to keep the cows sharp by letting them play with
intellectual toys. One of the larger toys is the lights in the barn.
Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered
1..N has a colorful light above it.

At the beginning of the evening, all the lights are off. The cows
control the lights with a set of N pushbutton switches that toggle
the lights; pushing switch i changes the state of light i from off
to on or from on to off.
The cows read and execute a list of M (1 <= M <= 100,000) operations
expressed as one of two integers (0 <= operation <= 1).

The first kind of operation (denoted by a 0 command) includes two
subsequent integers S_i and E_i (1 <= S_i <= E_i <= N) that indicate
a starting switch and ending switch. They execute the operation by
pushing each pushbutton from S_i through E_i inclusive exactly once.

The second kind of operation (denoted by a 1 command) asks the cows
to count how many lights are on in the range given by two integers
S_i and E_i (1 <= S_i <= E_i <= N) which specify the inclusive range
in which the cows should count the number of lights that are on.

Help FJ ensure the cows are getting the correct answer by processing
the list and producing the proper counts.

PROBLEM NAME: lites

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Each line represents an operation with three
        space-separated integers: operation, S_i, and E_i

SAMPLE INPUT:

4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

INPUT DETAILS:

Four lights; five commands. Here is the sequence that should
be processed:

	    Lights
            1 2 3 4
  Init:     O O O O   O = off  * = on
  0 1 2 ->  * * O O  toggle lights 1 and 2
  0 2 4 ->  * O * *
  1 2 3 ->  1        count the number of lit lights in range 2..3
  0 2 4 ->  * * O O  toggle lights 2, 3, and 4
  1 1 4 ->  2        count the number of lit lights in the range 1..4

OUTPUT FORMAT:

* Lines 1..number of queries: For each output query, print the count
        as an integer by itself on a single line.

SAMPLE OUTPUT:

1
2
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

#define DONE 0
#define FLIP 1

int flip(int cur) {
    if (cur == DONE) return FLIP;
    return DONE;
}

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A, lazy;            // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; }     // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {                           // O(n log n)
        if (L == R)                            // as L == R, either one is fine
            st[p] = A[L];                                         // store the index
        else {                                // recursively compute the values
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = p1 + p2;
        } }

    int rmq(int p, int L, int R, int i, int j) {                  // O(log n)

        if (lazy[p] != DONE) {
            st[p] = R - L + 1 - st[p];

            if (L != R) { // this node has children
                lazy[left(p)] = flip(lazy[left(p)]);
                lazy[right(p)] = flip(lazy[right(p)]);
            }

            lazy[p] = DONE;
        }

        if (i >  R || j <  L) return 0; // current segment outside query range

        if (L >= i && R <= j) return st[p];               // inside query range

        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        return p1 + p2; }          // as as in build routine

    int update_tree(int p, int L, int R, int i, int j) {
        if (lazy[p] != DONE) { // this node needs to be updated
            st[p] = R - L + 1 - st[p];

            if (L != R) { // this node has children
                lazy[left(p)] = flip(lazy[left(p)]);
                lazy[right(p)] = flip(lazy[right(p)]);
            }

            lazy[p] = DONE;
        }

        if (L > R || L > j || R < i) return st[p]; // Current segment not in range

        if (L >= i && R <= j) { // segment fully in range
            st[p] = R - L + 1 - st[p];

            if (L != R) { // Not leaf node
                lazy[left(p)] = flip(lazy[left(p)]);
                lazy[right(p)] = flip(lazy[right(p)]);
            }

            return st[p];
        }

        int p1 = update_tree(left(p), L, (L + R) / 2, i, j);
        int p2 = update_tree(right(p), (L + R) / 2 + 1, R, i, j);

        return st[p] = p1 + p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();              // copy content for local usage
        st.assign(4 * n, 0);            // create large enough vector of zeroes
        lazy.assign(4 * n, DONE);
        build(1, 0, n - 1);                                  // recursive build
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

    int update_tree(int i, int j) {
        return update_tree(1, 0, n - 1, i, j); }
};


int main() {
    ios_base::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    vector<int> vec; vec.assign(n, 0);
    SegmentTree st = SegmentTree(vec);

    for (int i = 0; i < m; i++) {
        int op, a, b; cin >> op >> a >> b; a--; b--;
        if (op == 0) {
            st.update_tree(a, b);
        } else {
            cout << st.rmq(a, b) << endl;
        }
    }

    return 0;
}
