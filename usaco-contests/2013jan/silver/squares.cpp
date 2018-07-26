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
#include <fstream>
#include <cassert>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Point {
    int x, y; bool isEnd;
    bool operator<(const Point &other) const {
        return y < other.y;
    }
};

int main() {
    freopen("squares.in", "r", stdin);
    freopen("squares.out", "w", stdout);

    int n, k; cin >> n >> k;
    vector<Point> points;
    F0R(i, n) {
        int x, y; cin >> x >> y;
        points.push_back(Point{x-k/2, y, false});
        points.push_back(Point{x+k/2, y, true});
    }
    sort(points.begin(), points.end(), [](Point a, Point b) {
        if (a.isEnd == b.isEnd && a.x == b.x) return a.y < b.y;
        return a.x == b.x ? a.isEnd > b.isEnd : a.x < b.x;
    });

    set<Point> curPoints;
    vector<Point> overlap;
    for (Point p : points) {
        if (p.isEnd) curPoints.erase(Point{p.x-k, p.y, false});
        else {
            auto it = curPoints.lower_bound(Point{p.x, p.y-k+1, false});
            if (it != curPoints.end() && it->y < p.y+k) {
                overlap.push_back(*it);
                overlap.push_back(p);
            }
            curPoints.insert(p);
        }
    }

    if (overlap.size() == 0) cout << "0";
    else if (overlap.size() > 2) cout << "-1";
    else {
        cout << ((k-abs(overlap[0].y - overlap[1].y))*(k-abs(overlap[0].x-overlap[1].x))) << endl;
    }

    return 0;
}
