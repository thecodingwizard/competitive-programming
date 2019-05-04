/*
Building a Ski Course
=====================

Farmer John is helping to turn his large field into a ski course for the
upcoming winter Moolympics.  The field has dimensions M x N (1 <= M,N <=
100), and its intended final composition is described by an M x N grid of
characters like this:

RSRSSS
RSRSSS
RSRSSS

Each character describes how the snow in a unit square of the field should
be groomed: either 'R' for 'rough' or 'S' for 'smooth' (the Moolympics
organizers think that a course is more interesting if it has a mixture of
rough and smooth patches).

To build the desired course, Farmer John plans to modify his tractor so
that it can stamp any B x B patch of the field (B <= M, B <= N) with either
entirely smooth snow or entirely rough snow.  Since it takes a long time to
reset the tractor between each of these stamps, FJ wants to make B as large
as possible.  With B = 1, he can clearly create the desired ski course by
stamping each individual square with either R or S, as intended.  However,
for larger values of B, it may no longer be possible to create the desired
course design.  Every unit square of the course must at some point be
stamped by FJ's tractor; it cannot be left in its default state.

Please help FJ determine the largest possible value of B he can
successfully use.

PROBLEM NAME: skicourse

INPUT FORMAT:

* Line 1: Two space-separated integers M and N.

* Lines 2..M+1: M lines of exactly N characters (each R or S),
        describing the desired ski course design.

SAMPLE INPUT:

3 6
RSRSSS
RSRSSS
RSRSSS

OUTPUT FORMAT:

* Line 1: The maximum value of B Farmer John can use to create the
        desired course pattern.

SAMPLE OUTPUT:

3

OUTPUT DETAILS:

FJ can stamp a rough patch spanning columns 1-3, followed by a smooth patch
spanning columns 2-4, then a rough patch spanning columns 3-5, and finally
a smooth patch spanning columns 4-6.
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

#define ROUGH 0
#define SMOOTH 1
#define STAMPED 2
int main() {
    int n, m; cin >> n >> m;
    int grid[n][m];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'R') grid[i][j] = ROUGH;
            else grid[i][j] = SMOOTH;
        }

    int dpRough[n+1][m+1];
    int dpSmooth[n+1][m+1];
    int dpStamped[n+1][m+1];
    int ans = INF;
    while (true) {
        memset(dpRough, 0, sizeof dpRough);
        memset(dpSmooth, 0, sizeof dpSmooth);
        memset(dpStamped, 0, sizeof dpStamped);
        int best = -1;
        int endX, endY;
        // stamped
        if (grid[0][0] == STAMPED) {
            dpStamped[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
                dpStamped[i][j] = min(dpStamped[i - 1][j], min(dpStamped[i][j - 1], dpStamped[i - 1][j - 1])) + 1;
                if (grid[i - 1][j - 1] != STAMPED) dpStamped[i][j] = 0;
            }
        // rough
        if (grid[0][0] == ROUGH) {
            dpRough[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
                dpRough[i][j] = min(dpRough[i - 1][j], min(dpRough[i][j - 1], dpRough[i - 1][j - 1])) + 1;
                if (grid[i - 1][j - 1] == SMOOTH) dpRough[i][j] = 0;
                if (best < dpRough[i][j] && dpRough[i][j] != dpStamped[i][j]) {
                    best = dpRough[i][j];
                    endX = i; endY = j;
                }
            }
        // smooth
        if (grid[0][0] == SMOOTH) {
            dpSmooth[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
                dpSmooth[i][j] = min(dpSmooth[i - 1][j], min(dpSmooth[i][j - 1], dpSmooth[i - 1][j - 1])) + 1;
                if (grid[i - 1][j - 1] == ROUGH) dpSmooth[i][j] = 0;
                if (best < dpSmooth[i][j] && dpSmooth[i][j] != dpStamped[i][j]) {
                    best = dpSmooth[i][j];
                    endX = i; endY = j;
                }
            }

        if (best == -1) break;

        ans = min(ans, best);

        for (int i = endX - best; i < endX; i++) for (int j = endY - best; j < endY; j++) {
                grid[i][j] = STAMPED;
            }
    }

    cout << ans << endl;
    return 0;
}
