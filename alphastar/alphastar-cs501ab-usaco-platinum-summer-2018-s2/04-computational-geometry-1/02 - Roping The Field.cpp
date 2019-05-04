/*
Roping the Field
================

Farmer John is quite the nature artist: he often constructs large
works of art on his farm. Today, FJ wants to construct a giant
"field web". FJ's field is large convex polygon with fences along
the boundary and fence posts at each of the N corners (1 <= N <=
150). To construct his field web, FJ wants to run as many ropes as
possible in straight lines between pairs of non-adjacent fence posts
such that no two ropes cross.

There is one complication: FJ's field is not completely usable.
Some evil aliens have created a total of G (0 <= G <= 100) grain
circles in the field, all of radius R (1 <= R <= 100,000). FJ is
afraid to upset the aliens, and therefore doesn't want the ropes
to pass through, or even touch the very edge of a grain circle.
Note that although the centers of all the circles are contained
within the field, a wide radius may make it extend outside of the
field, and both fences and fence posts may be within a grain circle.

Given the locations of the fence posts and the centers of the
circles, determine the maximum number of ropes that FJ can use to
create his field web.

FJ's fence posts and the circle centers all have integer coordinates
X and Y each of which is in the range 0..1,000,000.

PROBLEM NAME: roping

INPUT FORMAT:

* Line 1: Three space-separated integers: N, G, and R

* Lines 2..N+1: Each line contains two space-separated integers that
        are the X,Y position of a fence post on the boundary of FJ's
        field.

* Lines N+2..N+G+1: Each line contains two space-separated integers
        that are the X,Y position of a circle's center inside FJ's
        field.

SAMPLE INPUT:

5 3 1
6 10
10 7
9 1
2 0
0 3
2 2
5 6
8 3

INPUT DETAILS:

A pentagonal field, in which all possible ropes are blocked by three
grain circles, except for the rope between fenceposts 2 and 4.

OUTPUT FORMAT:

* Line 1: A single integer that is the largest number of ropes FJ can
        use for his artistic creation.

SAMPLE OUTPUT:

1
*/

/*
 * Notes to solve:
 *
 * Solution 1: (Not implemented below)
 * To check whether a segment intersects/passes through a circle,
 * drop a perpendicular from a circle to the line segment (explained below).
 * If the perpendicular lies on the segment, then compute the length.
 * The segment passes through if the length is less than the radius.
 * If the perpendicular does not lie on the segment, move the perpendicular
 * to the closest endpoint on the segment and compute the distance.
 *
 * To compute the intersection of the perpendicular, first find the angle
 * between the center and the segment using dot product. Then compute the distance from
 * one of the endpoints to the center. Knowing angle and hypotenuse, compute one of
 * the legs. Then use ratios to determine the coordinate of the perpendicular intersection.
 *
 * Solution 2: (Implemented)
 * To check if a line segment intersects a circle:
 * 1. Find point of intersection between line and center of circle, as well as distance
 *
 * 3. If either endpoint is inside the circle, return (yes intersection)
 * 4. If the point lies within the line segment, and dist is less than radius, return (yes intersection)
 * To do this:
 * def distance(a,b):
 *     return sqrt((a.x - b.x)**2 + (a.y - b.y)**2)
 *
 * def is_between(a,c,b):
 *     return distance(a,c) + distance(c,b) == distance(a,b)
 * Make sure to use proper epsilon
 * 5. No intersction
 *
 * For each segment, find if it intersects a circle. Now we can solve the remaining problem via DP.
 * If there are three points, take the two non-adjacent points. If the line segment formed does not
 * intersect segment, the maximum number of segments is 1.
 * Consider two sections of the circle. If the endpoints of the sections can be connected, then
 * the max number of segments is the sections + 1.
 *
 * Implementation:
 * 1. Initialize dp[n][n] to 0.
 * 2. Base case: (0, 2), (1, 3), ... (x, x + 2) = 1 if (x, x + 2) is a valid segment, 0 otherwise
 * 3. DP: (l, r) = max(dp(l, k) + dp(k, r) + (1 if (l, r) is valid, 0 otherwise)) for every l <= k <= r
 * 4. Answer is (0, n - 1)
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

int n, g, r;
ii fence[151];
ii circles[101];
bool valid[151][151];

double length(ii a, ii center) {
    return (sqrt(double(a.first - center.first)*double(a.first - center.first)+double(a.second - center.first)*double(a.second - center.first)));
}
double dist(ii a, ii b) {
    return abs(sqrt(pow(double(a.first-b.first),2)+pow(double(b.second-a.second),2)));
}

bool isValid(ii a, ii b, ii c) { // endpoint, center of circle, endpoint
    if (a.first == c.first && a.second == c.second) return false;
    int dotProduct = (c.first - a.first) * (b.first - a.first) + (c.second - a.second) * (b.second - a.second);
    double cosVal = double(dotProduct)/(abs(length(c, a))*abs(length(b, a)));
    if (cosVal == 1) return false;
    double hypotenuse = dist(a, b);
    double distToPerp = cosVal*hypotenuse;
    double xDiff = c.first - a.first; double yDiff = c.second - a.second; double ratio = distToPerp/dist(a, c);
    double x = a.first + (xDiff*ratio), y = a.second + (yDiff*ratio);
    cout << x << " " << y << endl;
    if (x > c.first || y > c.second) { x = c.first; y = c.second; }
    cout << x << " " << y << endl;
    cout << sqrt(pow(double(b.first)-x,2)+pow(double(b.second)-y,2)) << " " << r << endl;
    return sqrt(pow(double(b.first)-x,2)+pow(double(b.second)-y,2)) > r;
}

int main() {
    cin >> n >> g >> r;
    for (int i = 0; i < n; i++) cin >> fence[i].first >> fence[i].second;
    for (int i = 0; i < g; i++) cin >> circles[i].first >> circles[i].second;
    for (int i = 0; i < n; i++) for (int k = 0; k < n; k++) for (int j = 0; j < g; j++) valid[i][k] = isValid(fence[i], circles[j], fence[k]);
    cout << isValid(make_pair(0,3),make_pair(2,2),make_pair(10,1));
    return 0;
}
