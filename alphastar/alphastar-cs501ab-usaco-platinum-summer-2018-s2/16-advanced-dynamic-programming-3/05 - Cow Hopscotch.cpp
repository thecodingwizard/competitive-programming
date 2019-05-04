/*
Note: The following code gives TLE. It implements the (RC)^2 solution, able to solve silver but not gold.

Cow Hopscotch
=============

Just like humans enjoy playing the game of Hopscotch, Farmer John's
cows have invented a variant of the game for themselves to play.
Being played by clumsy animals weighing nearly a ton, Cow Hopscotch
almost always ends in disaster, but this has surprisingly not
deterred the cows from attempting to play nearly every afternoon.

The game is played on an R by C grid (2 <= R <= 750, 2 <= C <=
750), where each square is labeled with an integer in the range
1..K (1 <= K <= R*C). Cows start in the top-left square and move to
the bottom-right square by a sequence of jumps, where a jump is
valid if and only if

1) You are jumping to a square labeled with a different integer
than your current square,

2) The square that you are jumping to is at least one row below the
current square that you are on, and

3) The square that you are jumping to is at least one column to the
right of the current square that you are on.

Please help the cows compute the number of different possible
sequences of valid jumps that will take them from the top-left
square to the bottom-right square.

INPUT FORMAT:

The first line contains the integers R, C, and K. The next R lines
will each contain C integers, each in the range 1..K.

OUTPUT FORMAT:

Output the number of different ways one can jump from the top-left
square to the bottom-right square, mod 1000000007.

SAMPLE INPUT:

4 4 4
1 1 1 1
1 3 2 1
1 2 4 1
1 1 1 1

SAMPLE OUTPUT:

5
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
#include <unordered_map>
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

int n, c, k, grid[751][751];
long long dp[751][751];

int main() {
    cin >> n >> c >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < c; j++) cin >> grid[i][j];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < c; j++) for (int k = i + 1; k < n; k++) for (int l = j + 1; l < c; l++) {
                    if (grid[i][j] == grid[k][l]) continue;
                    dp[k][l] += dp[i][j];
                    dp[k][l] %= 1000000007;
                }
    cout << dp[n - 1][c - 1] << endl;
    return 0;
}
