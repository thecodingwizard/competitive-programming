/*
Covering the Corral
===================

The cows are so modest they want Farmer John to install covers
around the circular corral where they occasionally gather. The
corral has circumference C (1 <= C <= 1,000,000,000), and FJ can
choose from a set of M (1 <= M <= 100,000) covers that have fixed
starting points and sizes. At least one set of covers can surround
the entire corral.

Cover i can be installed at integer location x_i (distance from
starting point around corral) (0 <= x_i < C) and has integer length
l_i (1 <= l_i <= C).

FJ wants to minimize the number of segments he must install. What
is the minimum number of segments required to cover the entire
circumference of the corral?

Consider a corral of circumference 5, shown below as a pair of
connected line segments where both '0's are the same point on the
corral (as are both 1's, 2's, and 3's).

Three potential covering segments are available for installation:

           Start   Length
      i     x_i     l_i
      1      0       1
      2      1       2
      3      3       3

        0   1   2   3   4   0   1   2   3  ...
corral: +---+---+---+---+--:+---+---+---+- ...
        11111               1111
            22222222            22222222
                    333333333333
            |..................|

As shown, installing segments 2 and 3 cover an extent of (at least)
five units around the circumference. FJ has no trouble with the
overlap, so don't worry about that.

PROBLEM NAME: corral

INPUT FORMAT:

* Line 1: Two space-separated integers: C and M

* Lines 2..M+1: Line i+1 contains two space-separated integers: x_i
        and l_i

SAMPLE INPUT:

5 3
0 1
1 2
3 3

OUTPUT FORMAT:

* Line 1: A single integer that is the minimum number of segments
        required to cover all segments of the circumference of the
        corral

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

vector<pair<long, int>> segments;
int nextSegment[200000][18];

int main() {
    long long c, m; cin >> c >> m;
    for (int i = 0; i < m; i++) {
        long long s, l; cin >> s >> l;
        segments.emplace_back(s, s+l);
        segments.emplace_back(c+s, c+s+l);
        segments.emplace_back(c+c+s, c+c+s+l);
    }
    sort(segments.begin(), segments.end());
    int segmentIndex = 0;
    pair<long, int> best = mp(-1, -1);
    for (int i = 0; i < m; i++) {
        while (segmentIndex < segments.size() && segments[segmentIndex].A <= segments[i].B) {
            if (segments[segmentIndex].B > best.A) {
                best.A = segments[segmentIndex].B;
                best.B = segmentIndex;
            }
            segmentIndex++;
        }
        nextSegment[i][0] = best.B;
    }
    for (int i = 1; i <= 17; i++) {
        for (int j = 0; j < m; j++) {
            if (nextSegment[j][i - 1] >= m) nextSegment[j][i] = INF;
            else nextSegment[j][i] = nextSegment[nextSegment[j][i - 1]][i - 1];
        }
    }
    int ans = INF;
    for (int i = 0; i < m; i++) {
        int segmentsUsed = 1;
        int curSegment = i;
        int start = segments[curSegment].A;
        for (int j = 17; j >= 0; j--) {
            if (nextSegment[curSegment][j] == INF) continue;
            if (segments[nextSegment[curSegment][j]].B >= start + c) {
                segmentsUsed += pow(2, j);
                ans = min(ans, segmentsUsed);
                break;
            }
            if (segments[nextSegment[curSegment][j]].B <= segments[curSegment].A + c) {
                curSegment = nextSegment[curSegment][j];
                segmentsUsed += pow(2, j);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
