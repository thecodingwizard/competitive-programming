/*
Line of Sight
=============

Farmer John's N cows (1 <= N <= 50,000) are located at distinct points in
his two-dimensional pasture.  In the middle of the pasture is a large
circular grain silo.  Cows on opposite sides of the silo cannot see
each-other, since the silo blocks their view.  Please determine the number
of pairs of cows that can see each-other via a direct line of sight.

The grain silo is centered at the origin (0,0) and has radius R.  No cow is
located on or inside the circle corresponding to the silo, and no two cows
lie on a tangent line to the silo.  The value of R is in the range
1..1,000,000, and each cow lives at a point with integer coordinates in the
range -1,000,000..+1,000,000.

PROBLEM NAME: sight

INPUT FORMAT:

* Line 1: Two integers: N and R.

* Lines 2..1+N: Each line contains two integers specifying the (x,y)
        coordinates of a cow.

SAMPLE INPUT:

4 5
0 10
0 -10
10 0
-10 0

INPUT DETAILS:

There are 4 cows at positions (0,10), (0,-10), (10,0), and (-10,0).  The
silo is centered at (0,0) and has radius 5.

OUTPUT FORMAT:

* Line 1: The number of pairs of cows who can see each-other.

SAMPLE OUTPUT:

4

OUTPUT DETAILS:

All 6 pairs of cows can see each-other, except for the pairs situated on
opposite sides of the silo: the cows at (-10,0) and (10,0) cannot see
each-other, and the cows at (0,-10) and (0,10) cannot see each-other.
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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
struct point_i {
    int x, y;
    point_i() { x = y = 0; }
    point_i(int _x, int _y) : x(_x), y(_y) {}
};

struct point {
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS) return x < other.x;
        return y < other.y;
    }
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS) && (fabs(y - other.y) < EPS);
    }
    void toNearestInt() {
        if (abs(ceil(x) - x) < EPS) x = (int) ceil(x);
        if (abs(floor(x) - x) < EPS) x = (int) floor(x);
        if (abs(ceil(y) - y) < EPS) y = (int) ceil(y);
        if (abs(floor(y) - y) < EPS) y = (int) floor(y);
    };
};
double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}
point rotate(point p, double theta) {
    double rad = theta * 3.141592653589793238462643383279502884L / 180.0;
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad));
}
// rotates point p about point o
point rotateAboutPoint(point p, point o, double theta) {
    double rad = theta * 3.141592653589793238462643383279502884L / 180.0;
    return point((p.x - o.x) * cos(rad) - (p.y - o.y) * sin(rad) + o.x,
                 (p.x - o.x) * sin(rad) + (p.y - o.y) * cos(rad) + o.y);
}
struct line {
    double a, b, c; // ax + by + c = 0
    bool operator == (line other) const {
        return (fabs(a - other.a) < EPS) && (fabs(b - other.b) < EPS) && (fabs(c - other.c) < EPS);
    }
    // used only to sort & remove duplicates, implementation is bad
    bool operator < (line other) const {
        if (fabs(a - other.a) < EPS) {
            if (fabs(b - other.b) < EPS) return (other.c < c);
            return other.b < b;
        }
        return (other.a < a);
    }
};
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) { // vertical line
        l.a = 1.0; l.b = 0.0; l.c = -p1.x;
    } else {
        l.a = -(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(l.a * p1.x) - p1.y;
    }
    if (abs(l.c) < EPS) l.c  = 0.0;
}
bool areParallel(line l1, line l2) {
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}
bool areSame(line l1, line l2) {
    return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}
bool areIntersect(line l1, line l2, point &p) { // point p is the intersection point
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l2.b - l1.a * l2.b);
    // check for vertical line
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else p.y = -(l2.a * p.x + l2.c);
    return true;
}
struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}
vec scale(vec v, double s) {
    return vec(v.x * s, v.y * s);
}
point translate(point p, vec v) {
    return point(p.x + v.x, p.y + v.y);
}
double dot(vec a, vec b) {
    return (a.x * b.x + a.y * b.y);
}
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter
double distToLine(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

int n, r;
point cows[50001];
struct sweepPoint {
    double x;
    bool end;
    int id;
    sweepPoint(double _x, bool _end, int _id) : x(_x), end(_end), id(_id) {}
};

bool howToSort(sweepPoint a, sweepPoint b) {
    return a.x < b.x;
}

int main() {
    cin >> n >> r;
    for (int i = 0; i < n; i++) cin >> cows[i].x >> cows[i].y;
    vector<sweepPoint> points;
    bool special[n];
    memset(special, false, sizeof special);
    for (int i = 0; i < n; i++) {
        double x = cows[i].x, y = cows[i].y, d = hypot(x, y);
        double angleToHorizontal = atan2(y, x)*180/M_PI;
        double angle = acos(r/d)*180/M_PI;
        double top = angle + angleToHorizontal;
        double bottom = angleToHorizontal - angle;
        if (bottom < 0) {
            points.emplace_back(bottom + 360, false, i);
            points.emplace_back(top + 360, true, i);
            special[i] = true;
        } else {
            points.emplace_back(bottom, false, i);
            points.emplace_back(top, true, i);
            points.emplace_back(bottom + 360, false, i);
            points.emplace_back(top + 360, true, i);
        }
    }

    sort(points.begin(), points.end(), howToSort);

    int n = 0;
    int tot = 0;
    for (sweepPoint point : points) {
        if (point.end) {
            if (point.x < 360 || special[point.id]) n--;
        } else {
            tot += n;
            if (point.x < 360 || special[point.id]) n++;
        }
    }

    cout << tot << endl;


    return 0;
}
