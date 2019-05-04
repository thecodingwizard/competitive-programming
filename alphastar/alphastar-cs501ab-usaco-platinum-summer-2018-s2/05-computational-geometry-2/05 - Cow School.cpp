/*
Cow School
==========

Bessy is going to school and doing well. She has taken N (1 <= N
<= 5000 -- except one case where 1 <= N <= 50,000) tests and recorded
the scores (T_i points out of P_i points for test i; 0 <= T_i <=
P_i < 40,000; 0 < P_i) as this task's input.

Her teacher will drop the D tests with the lowest percentage (T_i/P_i)
before calculating Bessie's final grade (which is the sum of the
remaining test score points over the sum of the remaining total
test points). Bessy is good at math and quickly realizes that this
does not benefit her as much as it might.

To prove her point, Bessy wants to find all values of D for which
she could have ended up with a higher grade by choosing to drop
different tests than the teacher would have. Help her by finding
and printing all values of D for which this is possible.

Bessy has noted that, amazingly, she has never scored the same
percentage on two different tests.

PROBLEM NAME: schul

INPUT FORMAT:

* Line 1: A single integer, N

* Lines 2..N+1: Line i+1 contains two space-separated integers: T_i
        and P_i

SAMPLE INPUT:

5
1 2
5 9
3 8
4 10
1 3


INPUT DETAILS:

Bessy has taken 5 tests so far and has scores of 1/2, 5/9, 3/8, 4/10, and 1/3.

OUTPUT FORMAT:

* Line 1: A single integer K (0 <= K <= N) that is the number of
        values of D for which Bessy could have ended up with a higher
        grade by dropping a different set of D tests than the teacher.

* Lines 2..K+1: The values of D for which this is true, in ascending
        numerical order.

SAMPLE OUTPUT:

2
1
2

OUTPUT DETAILS:

For D = 1, dropping 1/3 leads to a final grade of 13/29. A higher
final grade of 11/24 can be achieved if Bessy drops 3/8.

For D = 2, dropping 1/3 and 3/8 lead to a final grade of 10/21. A
higher final grade of 7/14 can be achieved if Bessy drops 3/8 and
4/10.
*/

/* Note: The following code gives TLE on larger cases. It runs in O(n^2). */
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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    int n;
    cin >> n;
    int t[n], p[n];
    for (int i = 0; i < n; i++) cin >> t[i] >> p[i];

    int totT = 0; for (int i = 0; i < n; i++) totT += t[i];
    int totP = 0; for (int i = 0; i < n; i++) totP += p[i];

    vector<pair<long double, int>> percentages; // long double = percentage, int = id
    for (int i = 0; i < n; i++) {
        percentages.emplace_back(double(t[i])/p[i], i);
    }
    sort(percentages.begin(), percentages.end());

    vector<int> ans;
    bool dropped[n];
    memset(dropped,false,sizeof dropped);
    long double dropVal[n];
    long double worst;
    for (int i = 0; i < n; i++) {
        pair<long double, int> nextToDrop = percentages[i];
        dropped[nextToDrop.B] = true;
        int top = t[nextToDrop.B], bottom = p[nextToDrop.B];
        totT -= top; totP -= bottom;
        for (int j = 0; j < n; j++) dropVal[j] = t[j] - double(totT)*p[j]/totP;
        worst = -INF;
        long double best = INF;
        for (int j = 0; j < n; j++) {
            if (dropped[j]) {
                worst = max(worst, dropVal[j]);
            } else {
                best = min(best, dropVal[j]);
            }
        }
        if (worst > best) ans.push_back(i+1);
    }

    cout << ans.size() << endl;
    for (int i : ans) cout << i << endl;

    return 0;
}
