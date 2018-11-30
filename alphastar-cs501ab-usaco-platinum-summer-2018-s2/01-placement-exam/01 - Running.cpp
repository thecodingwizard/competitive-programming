/*
Running
=======

The cows are trying to become better athletes, so Bessie is running
on a track for exactly N (1 <= N <= 10,000) minutes. During each
minute, she can choose to either run or rest for the whole minute.

The ultimate distance Bessie runs, though, depends on her 'exhaustion
factor', which starts at 0. When she chooses to run in minute i,
she will run exactly a distance of D_i (1 <= D_i <= 1,000) and her
exhaustion factor will increase by 1 -- but must never be allowed
to exceed M (1 <= M <= 500).  If she chooses to rest, her exhaustion
factor will decrease by 1 for each minute she rests. She cannot
commence running again until her exhaustion factor reaches 0. At
that point, she can choose to run or rest.

At the end of the N minute workout, Bessie's exaustion factor must
be exactly 0, or she will not have enough energy left for the rest
of the day.

Find the maximal distance Bessie can run.

PROBLEM NAME: cowrun

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M

* Lines 2..N+1: Line i+1 contains the single integer: D_i

SAMPLE INPUT:

5 2
5
3
4
2
10

OUTPUT FORMAT:

* Line 1: A single integer representing the largest distance Bessie
        can run while satisfying the conditions.

SAMPLE OUTPUT:

9

OUTPUT DETAILS:

Bessie runs during the first minute (distance=5), rests during the
second minute, runs for the third (distance=4), and rests for the
fourth and fifth. Note that Bessie cannot run on the fifth minute
because she would not end with a rest factor of 0.
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

int n, m;
int dist[10001];
int dp1[601][1001];
int dp2[601][1001];

int slidingWindow;
int getDPVal(int minute, int exhaustion) {
    if (minute - slidingWindow < 0) {
        slidingWindow -= 600;
        for (int i = 0; i <= 600; i++) for (int j = 0; j <= 600; j++) dp1[i][j] = dp2[i][j];
    }
    if (minute - slidingWindow >= 600) {
        return dp1[minute - slidingWindow - 600][exhaustion];
    } else {
        return dp2[minute - slidingWindow][exhaustion];
    }
}
int setDPVal(int minute, int exhaustion, int val) {
    if (minute - slidingWindow < 0) {
        slidingWindow -= 600;
        for (int i = 0; i <= 600; i++) for (int j = 0; j <= 600; j++) dp1[i][j] = dp2[i][j];
    }
    if (minute - slidingWindow >= 600) {
        return dp1[minute - slidingWindow - 600][exhaustion] = val;
    } else {
        return dp2[minute - slidingWindow][exhaustion] = val;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> dist[i];
    slidingWindow = n - 600;
    for (int minute = n; minute >= 0; minute--) for (int exhaustion = m; exhaustion >= 0; exhaustion--) {
            if (minute == n && exhaustion > 0) {
                setDPVal(minute, exhaustion, -INF);
                continue;
            }
            if (minute == n) {
                setDPVal(minute, exhaustion, 0);
                continue;
            }
            int rest = -INF;
            if (minute + max(exhaustion, 1) <= n) rest = getDPVal(minute + max(exhaustion, 1), 0);
            int run = -INF;
            if (exhaustion + 1 <= m) run = getDPVal(minute + 1, exhaustion + 1) + dist[minute];
            if (rest < 0) rest = -INF;
            if (run < 0) run = -INF;
            setDPVal(minute, exhaustion, max(rest, run));
        }
    cout << getDPVal(0, 0) << endl;
    return 0;
}
