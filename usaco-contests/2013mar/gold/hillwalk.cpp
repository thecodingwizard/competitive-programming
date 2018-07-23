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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Hill {
    int x1, y1, x2, y2, id;

    bool operator<(Hill other) const {
        if (x2 < other.x2) {
            return (long long) (y2 - other.y1) * (long long) (other.x2 - other.x1) <
                   (long long) (other.y2 - other.y1) * (long long) (x2 - other.x1);
        } else {
            return (long long) (other.y2 - y1) * (long long) (x2 - x1) >
                   (long long) (y2 - y1) * (long long) (other.x2 - x1);
        }
    }
};

struct Point {
    int x, y, hillId;
    bool end;

    bool operator==(Point other) const {
        return hillId == other.hillId;
    }
    bool operator<(Point other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
};

int main() {
    freopen("hillwalk.in", "r", stdin);
    freopen("hillwalk.out", "w", stdout);

    int n; cin >> n;
    Hill hills[n];
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        hills[i] = Hill{x1, y1, x2, y2, i};
        points.push_back(Point{x1, y1, i, false});
        points.push_back(Point{x2, y2, i, true});
    }
    sort(points.begin(), points.end());
    set<Hill> curHills;
    Hill curHill; curHill.x1 = -1;
    int ans = 0;
    for (Point p : points) {
        if (curHill.x1 == -1) {
            curHills.insert(hills[p.hillId]);
            curHill = hills[p.hillId];
            ans++;
        } else {
            if (p.end) {
                if (p.hillId == curHill.id) {
                    auto it = curHills.find(curHill);
                    if (it == curHills.begin()) {
                        cout << ans << endl;
                        return 0;
                    }
                    curHill = *(--it);
                    ans++;
                }
                curHills.erase(hills[p.hillId]);
            } else {
                curHills.insert(hills[p.hillId]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
