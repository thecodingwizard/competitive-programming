/*
Route Designing
===============

After escaping from the farm, Bessie has decided to start a travel agency
along the Amoozon river.  There are several tourist sites located on both
sides of the river, each with an integer value indicating how interesting
the tourist site is.

These sites are connected by routes that cross the river (i.e. there are no
routes connecting a site with a site on the same side of the river).
Bessie wants to design a tour for her customers and needs your help.  A
tour is a sequence of tourist sites with adjacent sites connected by a
route. In order to best serve her customers she wants to find the route
that maximizes the sum of the values associated with each visited site.

However, Bessie may be running several of these tours at the same time.
Therefore it's important that no two routes on a tour intersect.  Two routes
(a <-> x) and (b <-> y) intersect if and only if (a < b and y < x) or (b <
a and x < y) or (a = b and x = y).

Help Bessie find the best tour for her agency.  Bessie may start and end at
any site on either side of the Amoozon.

PROBLEM NAME: route

INPUT FORMAT:

* Line 1: Three space separated integers N (1 <= N <= 40,000), M (1 <= M <=
        40,000), and R (0 <= R <= 100,000) indicating respectively the
        number of sites on the left side of the river, the number of sites
        on the right side of the river, and the number of routes.

* Lines 2..N+1: The (i+1)th line has a single integer, L_i (0 <= L_i
        <= 40,000), indicating the value of the ith tourist site on
        the left side of the river.

* Lines N+2..N+M+1: The (i+N+1)th line has a single integer, R_i (0 <=
        R_i <= 40,000), indicating the value of the ith tourist site
        on the right side of the river.

* Lines N+M+2..N+M+R+1: Each line contains two space separated
        integers I (1 <= I <= N) and J (1 <= J <= M) indicating there
        is a bidirectional route between site I on the left side of
        the river and site J on the right side of the river.

SAMPLE INPUT:

3 2 4
1
1
5
2
2
1 1
2 1
3 1
2 2

INPUT DETAILS:

There are three sites on the left side of the Amoozon with values 1, 1, and 5.
There are two sites on the right side of the Amoozon with values 2, and 2.
There are four routes connecting sites on both sides of the river.

OUTPUT FORMAT:

* Line 1: A single integer indicating the maximum sum of values attainable on a tour.

SAMPLE OUTPUT:

8

OUTPUT DETAILS:

The optimal tour goes from site 1 on the left, site 1 on the right, and
ends at site 3 on the left.  These respectively have values 1, 2, and 5
giving a total value of the trip of 8.
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

int n, m, r, lval[40001], rval[40001];
vii paths;

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> r;
    lval[0] = 0, rval[0] = 0;
    for (int i = 1; i <= n; i++) cin >> lval[i];
    for (int i = 1; i <= m; i++) cin >> rval[i];
    for (int i = 0; i < r; i++) {
        int a, b; cin >> a >> b;
        paths.push_back(mp(a, b));
    }
    sort(paths.begin(), paths.end());
    long long dpLeft[100001];
    long long dpRight[100001];
    memset(dpLeft, 0, sizeof dpLeft);
    memset(dpRight, 0, sizeof dpRight);
    long long best = 0;
    for (int i = 1; i <= n; i++) {
        dpLeft[i] = lval[i];
        best = max(best, dpLeft[i]);
    }
    for (int i = 1; i <= m; i++) {
        dpRight[i] = rval[i];
        best = max(best, dpRight[i]);
    }
    for (int i = r - 1; i >= 0; i--) {
        int start = paths[i].A, end = paths[i].B;

        long long newDPRight = rval[end] + dpLeft[start], newDPLeft = lval[start] + dpRight[end];
        dpRight[end] = max(dpRight[end], newDPRight);
        dpLeft[start] = max(dpLeft[start], newDPLeft);

        best = max(best, dpRight[end]);
        best = max(best, dpLeft[start]);
    }

    cout << best << endl;
    return 0;
}
