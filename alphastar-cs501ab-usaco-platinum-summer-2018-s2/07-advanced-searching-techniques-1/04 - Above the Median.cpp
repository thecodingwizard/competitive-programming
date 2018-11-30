/*
Above the Median
================

Farmer John has lined up his N (1 <= N <= 100,000) cows in a row to measure
their heights; cow i has height H_i (1 <= H_i <= 1,000,000,000)
nanometers--FJ believes in precise measurements! He wants to take a picture
of some contiguous subsequence of the cows to submit to a bovine
photography contest at the county fair.

The fair has a very strange rule about all submitted photos: a photograph
is only valid to submit if it depicts a group of cows whose median height
is at least a certain threshold X (1 <= X <= 1,000,000,000).

For purposes of this problem, we define the median of an array A[0...K-1] to
be A[floor(K/2)] after A is sorted, where floor(K/2) gives K/2 rounded
down to the nearest integer (or K/2 itself, if K/2 is an integer to begin
with). For example the median of {7, 3, 2, 6} is 6, and the median of {5,
4, 8} is 5.

Please help FJ count the number of different contiguous subsequences of his
cows that he could potentially submit to the photography contest.

PROBLEM NAME: median

INPUT FORMAT:

* Line 1: Two space-separated integers: N and X.

* Lines 2..N+1: Line i+1 contains the single integer H_i.

SAMPLE INPUT:

4 6
10
5
6
2

INPUT DETAILS:

FJ's four cows have heights 10, 5, 6, 2. We want to know how many
contiguous subsequences have median at least 6.

OUTPUT FORMAT:

* Line 1: The number of subsequences of FJ's cows that have median at
        least X. Note this may not fit into a 32-bit integer.

SAMPLE OUTPUT:

7

OUTPUT DETAILS:

There are 10 possible contiguous subsequences to consider. Of these, only 7
have median at least 7. They are {10}, {6}, {10, 5}, {5, 6}, {6, 2}, {10,
5, 6}, {10, 5, 6, 2}.
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

int main() {
    int n, x;
    cin >> n >> x;
    int sum[n+2];
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        sum[i] = sum[i - 1] + (a >= x ? 1 : -1);
    }
    FenwickTree ft = FenwickTree(2*n+10);
    long long counter = 0;
    ft.adjust(n, 1);
    for (int i = 1; i <= n; i++) {
        counter += ft.rsq(sum[i] + n);
        ft.adjust(sum[i] + n, 1);
    }
    cout << counter;
    return 0;
}
