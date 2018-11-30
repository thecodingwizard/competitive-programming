/*
Cow Travelling
==============

Searching for the very best grass, the cows are travelling about
the pasture which is represented as a grid with N rows and M columns
(2 <= N <= 100; 2 <= M <= 100). Keen observer Farmer John has
recorded Bessie's position as (R1, C1) at a certain time and then
as (R2, C2) exactly T (0 < T <= 15) seconds later. He's not sure
if she passed through (R2, C2) before T seconds, but he knows she
is there at time T.

FJ wants a program that uses this information to calculate an integer
S that is the number of ways a cow can go from (R1, C1) to (R2, C2)
exactly in T seconds. Every second, a cow can travel from any
position to a vertically or horizontally neighboring position in
the pasture each second (no resting for the cows). Of course, the
pasture has trees through which no cow can travel.

Given a map with '.'s for open pasture space and '*' for trees,
calculate the number of possible ways to travel from (R1, C1) to
(R2, C2) in T seconds.

PROBLEM NAME: ctravel

INPUT FORMAT:

* Line 1: Three space-separated integers: N, M, and T

* Lines 2..N+1: Line i+1 describes row i of the pasture with exactly M
        characters that are each '.' or '*'

* Line N+2: Four space-separated integers: R1, C1, R2, and C2.

SAMPLE INPUT:

4 5 6
...*.
...*.
.....
.....
1 3 1 5

INPUT DETAILS:

The pasture is 4 rows by 5 colum. The cow travels from row 1, column
3 to row 1, column 5, which takes exactly 6 seconds.

OUTPUT FORMAT:

* Line 1: A single line with the integer S described above.

SAMPLE OUTPUT:

1

OUTPUT DETAILS:

There is only one way from (1,3) to (1,5) in exactly 6 seconds (and
it is the obvious one that travels around the two trees).
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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, m, t, r1, c1, r2, c2;
bool blocked[101][101];
int memo[101][101][16];

int dp(int x, int y, int time) {
    if (x < 0 || x >= n || y < 0 || y >= m || blocked[x][y]) return 0;
    if (time == t) {
        if (x == r2 && y == c2) return 1;
        else return 0;
    }
    if (memo[x][y][time] != -1) return memo[x][y][time];
    return memo[x][y][time] = dp(x + 1, y, time + 1) + dp(x, y + 1, time + 1) + dp(x, y - 1, time + 1) + dp(x - 1, y, time + 1);
}

int main() {
    cin >> n >> m >> t;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            char c; cin >> c;
            blocked[i][j] = c == '*';
        }
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;

    cout << dp(r1, c1, 0);

    return 0;
}
