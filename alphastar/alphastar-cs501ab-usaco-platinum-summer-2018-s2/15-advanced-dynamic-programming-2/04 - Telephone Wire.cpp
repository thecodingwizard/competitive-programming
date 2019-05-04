/*
Telephone Wire
==============

Farmer John's cows are getting restless about their poor telephone
service; they want FJ to replace the old telephone wire with new,
more efficient wire. The new wiring will utilize N (2 <= N <=
100,000) already-installed telephone poles, each with some height_i
meters (1 <= height_i <= 100). The new wire will connect the tops
of each pair of adjacent poles and will incur a penalty cost C *
the two poles' height difference for each section of wire where the
poles are of different heights (1 <= C <= 100). The poles, of course,
are in a certain sequence and can not be moved.

Farmer John figures that if he makes some poles taller he can reduce
his penalties, though with some other additional cost. He can add
an integer X number of meters to a pole at a cost of X^2.

Help Farmer John determine the cheapest combination of growing pole
heights and connecting wire so that the cows can get their new and
improved service.

PROBLEM NAME: telewire

INPUT FORMAT:

* Line 1: Two space-separated integers: N and C

* Lines 2..N+1: Line i+1 contains a single integer: height_i

SAMPLE INPUT:

5 2
2
3
5
1
4

INPUT DETAILS:

There are 5 telephone poles, and the vertical distance penalty is
$2/meter. The poles initially have heights of 2, 3, 5, 1, and 4,
respectively.

OUTPUT FORMAT:

* Line 1: The minimum total amount of money that it will cost Farmer
        John to attach the new telephone wire.

SAMPLE OUTPUT:

15

OUTPUT DETAILS:

The best way is for Farmer John to raise the first pole by 1 unit and the
fourth pole by 2 units, making the heights (in order) 3, 3, 5, 3, and 4.
This costs $5. The remaining wiring will cost $2*(0+2+2+1) = $10, for a
total of $15.
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

int heights[100001];
int dp[2][101];

int main() {
    int n, c; cin >> n >> c;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    int curDP = 0;
    for (int i = 0; i <= 100; i++) dp[curDP][i] = (i >= heights[0] ? (heights[0]-i)*(heights[0]-i) : INF);
    curDP = !curDP;
    for (int i = 1; i < n; i++) {
        int best = INF;

        for (int j = 0; j <= 100; j++) {
            best = min(best, dp[!curDP][j] - j*c);
            dp[curDP][j] = best + j*c;
        }

        best = INF;
        for (int j = 100; j >= 0; j--) {
            best = min(best, dp[!curDP][j] + j*c);
            dp[curDP][j] = min(dp[curDP][j], best - j*c);
        }

        for (int j = 0; j <= 100; j++) {
            if (j < heights[i]) {
                dp[curDP][j] = INF;
                continue;
            }
            dp[curDP][j] = dp[curDP][j] + (j-heights[i])*(j-heights[i]);
        }

        curDP = !curDP;
    }

    int ans = INF;
    for (int i = heights[n - 1]; i <= 100; i++) {
        ans = min(ans, dp[!curDP][i]);
    }
    cout << ans << endl;

    return 0;
}
