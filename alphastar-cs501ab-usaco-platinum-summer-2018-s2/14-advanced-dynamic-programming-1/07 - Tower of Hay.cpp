/*
Note: The following greedy solution is *incorrect* and gives WA.

Tower of Hay
============

Cows so hate the dark. In order to change a lightbulb at the top
of the barn, Bessie must build a tower out of bales of hay to climb
so that she can reach it. The N (1 <= N <= 100,000) bales of hay
(conveniently numbered 1..N) enter the barn sequentially on a
conveyor belt. Bale i has integer width w_i (1 <= w_i <= 10,000);
all bales have the same depth and height.

Bessie must use all N hay bales to build the tower and must lay
them down in the order they arrive. She can lay as many bales as
she wishes (tightly packed in a line, of course) to create the
foundation of the tower. She can then lay some of the next bales
on top of the previous level to create the next level (no level can
be wider than the level beneath it). She continues this process
until all the bales are used. She must stack the bales in the order
they arrive, from the bottom to the top of the tower. To be clear:
she must not try to sneak a bale back on the foundation after a
bale is placed on the second layer.

Bessie's goal is to create the tallest tower possible -- and she
already knows how wide each every bale of hay will be as it comes
into the barn on the belt. How tall a tower can she construct?

PROBLEM NAME: tower

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains a single integer: w_i

SAMPLE INPUT:

3
1
2
3

OUTPUT FORMAT:

* Line 1: A single integer, the height of the tallest possible tower
        that can be built

SAMPLE OUTPUT:

2

OUTPUT DETAILS:

Use the first bales with width 1 and 2 for the bottom row (total
width: 3), then the next bale (width 3) for the top row:

            +----------+
            |    3     |
            +---+------+
            | 1 |   2  |
            +---+------+

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

int main() {
    int n; cin >> n;
    int cows[n]; for (int i = 0; i < n; i++) cin >> cows[i];
    int curWidth = cows[n - 1];
    int runningSum = 0;
    int curIdx = n - 2;
    int ans = 1;
    while (curIdx >= 0) {
        runningSum += cows[curIdx--];
        if (runningSum >= curWidth) {
            curWidth = runningSum;
            runningSum = 0;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
