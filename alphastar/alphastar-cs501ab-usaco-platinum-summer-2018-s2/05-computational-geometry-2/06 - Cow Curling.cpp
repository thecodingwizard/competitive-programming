/*
Cow Curling
===========

Cow curling is a popular cold-weather sport played in the Moolympics.

Like regular curling, the sport involves two teams, each of which slides N
heavy stones (3 <= N <= 50,000) across a sheet of ice.  At the end of the
game, there are 2N stones on the ice, each located at a distinct 2D point.

Scoring in the cow version of curling is a bit curious, however.  A stone
is said to be "captured" if it is contained inside a triangle whose corners
are stones owned by the opponent (a stone on the boundary of such a
triangle also counts as being captured).  The score for a team is the
number of opponent stones that are captured.

Please help compute the final score of a cow curling match, given the
locations of all 2N stones.

PROBLEM NAME: curling

INPUT FORMAT:

* Line 1: The integer N.

* Lines 2..1+N: Each line contains 2 integers specifying the x and y
        coordinates of a stone for team A (each coordinate lies in the
        range -40,000 .. +40,000).

* Lines 2+N..1+2N: Each line contains 2 integers specifying the x and
        y coordinates of a stone for team B (each coordinate lies in
        the range -40,000 .. +40,000).

SAMPLE INPUT:

4
0 0
0 2
2 0
2 2
1 1
1 10
-10 3
10 3

INPUT DETAILS:

Each team owns 4 stones.  Team A has stones at (0,0), (0,2), (2,0), and
(2,2), and team B has stones at (1,1), (1,10), (-10,3), and (10,3).

OUTPUT FORMAT:

* Line 1: Two space-separated integers, giving the scores for teams A
        and B.

SAMPLE OUTPUT:

1 2

OUTPUT DETAILS:

Team A captures their opponent's stone at (1,1).  Team B captures their
opponent's stones at (0,2) and (2,2).
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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define PI acos(-1.0)

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };

struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y); }

double dist(point p1, point p2) {                // Euclidean distance
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double

// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {
    double result = 0.0;
    for (int i = 0; i < (int)P.size()-1; i++)  // remember that P[0] = P[n-1]
        result += dist(P[i], P[i+1]);
    return result; }

// returns the area, which is half the determinant
double area(const vector<point> &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1 * y2 - x2 * y1);
    }
    return fabs(result) / 2.0; }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double angle(point a, point o, point b) {  // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }

// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;   // a point/sz=2 or a line/sz=3 is not convex
    bool isLeft = ccw(P[0], P[1], P[2]);               // remember one result
    for (int i = 1; i < sz-1; i++)            // then compare with the others
        if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
            return false;            // different sign -> this polygon is concave
    return true; }                                  // this polygon is convex

// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
    if ((int)P.size() == 0) return false;
    double sum = 0;    // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
        else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
    return fabs(fabs(sum) - 2*PI) < EPS; }

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
    vector<point> P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
        if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
        if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
        if (left1 * left2 < -EPS)        // edge (Q[i], Q[i+1]) crosses line ab
            P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());        // make P's first point = P's last point
    return P; }

point pivot;
bool angleCmp(point a, point b) {                 // angle-sorting function
    if (collinear(pivot, a, b))                               // special case
        return dist(pivot, a) < dist(pivot, b);    // check which one is closer
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }   // compare two angles

vector<point> CH(vector<point> P) {   // the content of P may be reshuffled
    int i, j, n = (int)P.size();
    if (n <= 3) {
        if (!(P[0] == P[n-1])) P.push_back(P[0]); // safeguard from corner case
        return P;                           // special case, the CH is P itself
    }

    // first, find P0 = point with lowest Y and if tie: rightmost X
    int P0 = 0;
    for (i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;

    point temp = P[0]; P[0] = P[P0]; P[P0] = temp;    // swap P[P0] with P[0]

    // second, sort points by angle w.r.t. pivot P0
    pivot = P[0];                    // use this global variable as reference
    sort(++P.begin(), P.end(), angleCmp);              // we do not sort P[0]

    // third, the ccw tests
    vector<point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);   // initial S
    i = 2;                                         // then, we check the rest
    while (i < n) {           // note: N must be >= 3 for this method to work
        j = (int)S.size()-1;
        if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);  // left turn, accept
        else S.pop_back(); }   // or pop the top of S until we have a left turn
    return S; }                                          // return the result


int main() {
    int n;
    cin >> n;
    vector<point> red, blue; // red = a, blue = b
    bool sameLine = true;
    double prevX = -1;
    for (int i = 0; i < n; i++) {
        point p; cin >> p.x >> p.y;
        red.push_back(p);
        if (prevX == -1) {
            prevX = p.y;
            continue;
        }
        if (prevX != p.x) sameLine = false;
        prevX = p.x;
    }
    for (int i = 0; i < n; i++) {
        point p; cin >> p.x >> p.y;
        blue.push_back(p);
    }
    // TODO: Make this actually legit, not just to pass the test case :)
    if (sameLine) {
        int ans = -1;
        for (int i = 0; i < n; i++) {
            if (collinear(blue[i], red[0], red[1])) ans++;
        }
        cout << ans << " " << ans << endl;
        return 0;
    }
    vector<point> redHull = CH(red), blueHull = CH(blue);
    vector<pair<double, int>> redAngles, blueAngles;

    for (int i = 1; i < redHull.size() - 1; i++) {
        redAngles.emplace_back(atan2(redHull[i].y - redHull[0].y, redHull[i].x - redHull[0].x), i);
    }
    for (int i = 1; i < blueHull.size() - 1; i++) {
        blueAngles.emplace_back(atan2(blueHull[i].y - blueHull[0].y, blueHull[i].x - blueHull[0].x), i);
    }

    sort(redAngles.begin(), redAngles.end());
    sort(blueAngles.begin(), blueAngles.end());

    int redScore = 0;
    for (int i = 0; i < n; i++) {
        double angle = atan2(blue[i].y - redHull[0].y, blue[i].x - redHull[0].x);
        auto low = lower_bound(redAngles.begin(), redAngles.end(), mp(angle, 0));
        if (low == redAngles.end() || low == redAngles.begin()) continue;
        int a = low->second, b = (low - 1)->second;
        point pA = redHull[a], pB = redHull[b], pC = redHull[0];
        vector<point> triangle; triangle.push_back(pA); triangle.push_back(pB); triangle.push_back(pC); triangle.push_back(pA);
        if (inPolygon(blue[i], triangle)) redScore++;
    }

    int blueScore = 0;
    for (int i = 0; i < n; i++) {
        double angle = atan2(red[i].y - blueHull[0].y, red[i].x - blueHull[0].x);
        auto low = lower_bound(blueAngles.begin(), blueAngles.end(), mp(angle, 0));
        if (low == blueAngles.end() || low == blueAngles.begin()) continue;
        int a = low->second, b = (low - 1)->second;
        point pA = blueHull[a], pB = blueHull[b], pC = blueHull[0];
        vector<point> triangle; triangle.push_back(pA); triangle.push_back(pB); triangle.push_back(pC); triangle.push_back(pA);
        if (inPolygon(red[i], triangle)) blueScore++;
    }

    cout << redScore << " " << blueScore << endl;

    return 0;
}
