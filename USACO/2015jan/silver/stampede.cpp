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
#include <unordered_set>

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

bool visited[1000001];
int main() {
    freopen("stampede.in", "r", stdin);
    freopen("stampede.out", "w", stdout);

    int n; cin >> n;
    vector<pair<ii, bool>> points;
    memset(visited, false, sizeof visited);
    F0R(i, n) {
        int x, y, r; cin >> x >> y >> r;
        int start = (-x-1)*r, end = -x*r;
        points.push_back(mp(mp(start, y), false));
        points.push_back(mp(mp(end, y), true));
    }
    sort(points.begin(), points.end());

    set<int> cur;
    int curPos = -INF;
    int ans = 0;
    for (pair<ii, bool> point : points) {
        if (curPos != point.A.A && !cur.empty() && !visited[*cur.begin()]) {
            visited[*cur.begin()] = true;
            ans++;
        }
        curPos = point.A.A;
        if (point.B) {
            cur.erase(point.A.B);
        } else {
            cur.insert(point.A.B);
        }
    }
    cout << ans << endl;

    return 0;
}
