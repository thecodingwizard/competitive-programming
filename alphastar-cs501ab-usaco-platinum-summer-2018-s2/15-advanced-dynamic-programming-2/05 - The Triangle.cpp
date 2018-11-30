/*
Note: The following code gives WA for one test case.

The Triangle
============

For her spectacular milk output for the previous month, Farmer John
has awarded Bessie a prize -- with a twist.  He has given her a
triangular grid with N (1 <= N <= 700) rows (whose lengths vary
from 1 through N, of course). Row i of the the grid has i values
labeled v_ij (-1,000,000,000 <= v_ij <= 1,000,000,000) where j is
in the range 1..i.

Bessie chooses a sub-triangle whose side length is at least K (1
<= K <= 20; 1 <= K <= N) within the triangular grid. The sub-triangle
is another triangular grid which might be oriented the same as the
original triangle or might be 'upside down' with its shorter rows
on the bottom instead of the top.

After she chooses her sub-triangle, Farmer John will take the average
of all the numbers in the sub-triangle, discarding the digits to
the right of the decimal point, and give her that many gold coins
(or take that many gold coins from her if the number is negative).
Naturally, Bessie would like to maximize her prize (or minimize her
loss). Help her solve this problem.

By way of example, Bessie is given this triangular grid with N = 3
rows and must choose a sub-triangle with a side length of at least
K = 2. A graphical representation of the triangle is shown below:

    / \
   / 5 \
  /-8  4\
 /2 -3  6\
 ---------

She could choose any of five valid sub-triangles (one of which is
the entire original triangle):
                                                   /\
    / \         / \        / \         / \        /5 \
   / 5 \       / \5\      / 5 \       / 5/\      /----\
  /-8  4\     /-8 \4\    /-8  4\     /-8/ 4\    /\-8 4/\
 /2 -3  6\   / 2 -3\6\  /-------\   / 2/-3 6\  / 2\-3/6 \
 ---------   ---------  -2  -3  6   ---------  ----------
  entire      lower        top          lower     upside
 triangle     left                      right      down

The one that is lined below is the one with the highest average:

    / \
   / 5/\
  /-8/ 4\
 / 2/-3 6\
 ---------

The average of this sub-triangle is (4+6-3)/3, which is about
2.3333...; without the fraction, the answer is 2.

Help Bessie calculate the maximum amount of coins which she could
receive.

PROBLEM NAME: tri

INPUT FORMAT:

* Line 1: Two space-separated integers: N and K

* Lines 2..N+1: Line i+1 will contain i space-separated integers: v_ij

SAMPLE INPUT:

3 2
5
-8 4
2 -3 6

OUTPUT FORMAT:

* Line 1: The maximum number of coins that Bessie can receive (or, if
        negative, the best she can do for her loss).

SAMPLE OUTPUT:

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
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    int n, k; cin >> n >> k;
    long long triangle[n][n];
    for (int i = 0; i < n; i++) for (int j = 0; j <= i; j++) cin >> triangle[i][j];
    long long ps[n][n];
    memset(ps, 0, sizeof ps);
    for (int i = 0; i < n; i++) for (int j = 0; j <= i; j++) {
            ps[i][j] = (j > 0 ? ps[i][j - 1] : 0) + triangle[i][j];
        }
    long long best = -LL_INF;
    for (int sideLength = k; sideLength <= min(n, 2*k); sideLength++) {
        // right side up
        long long maxSum = -LL_INF;
        for (int startRow = 0; startRow + sideLength <= n; startRow++) {
            for (int startCol = 0; startCol <= startRow; startCol++) {
                long long sum = 0;
                for (int row = startRow; row < startRow + k; row++) {
                    sum += ps[row][startCol + (row - startRow)] - (startCol > 0 ? ps[row][startCol - 1] : 0);
                }
                maxSum = max(maxSum, sum);
            }
        }

        // upside down
        for (int startRow = sideLength - 1; startRow + sideLength <= n; startRow++) {
            for (int startCol = 0; startCol <= (startRow + 1 - sideLength); startCol++) {
                long long sum = 0;
                for (int row = startRow; row < startRow + k; row++) {
                    sum += ps[row][startCol + sideLength - 1] - (startCol + (row - startRow) > 0 ? ps[row][startCol + (row - startRow) - 1] : 0);
                }
                maxSum = max(maxSum, sum);
            }
        }

        best = max(best, (long long) floor(double(maxSum)/(sideLength*(sideLength+1)/2.0)));
    }
    cout << best << endl;
    return 0;
}
