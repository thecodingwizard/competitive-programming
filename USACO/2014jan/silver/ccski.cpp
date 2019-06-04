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

int m, n;
int elevations[500+10][500+10];
bool isWaypoint[501][501];
bool taken[501][501];
int waypointCt = 0;
priority_queue<pair<int, ii>> pq;

void process(ii node) {
    taken[node.A][node.B] = true;
    if (node.A + 1 < m) pq.push(mp(-abs(elevations[node.A+1][node.B]-elevations[node.A][node.B]), mp(node.A+1, node.B)));
    if (node.B + 1 < n) pq.push(mp(-abs(elevations[node.A][node.B+1]-elevations[node.A][node.B]), mp(node.A, node.B+1)));
    if (node.A - 1 >= 0) pq.push(mp(-abs(elevations[node.A-1][node.B]-elevations[node.A][node.B]), mp(node.A-1, node.B)));
    if (node.B - 1 >= 0) pq.push(mp(-abs(elevations[node.A][node.B-1]-elevations[node.A][node.B]), mp(node.A, node.B-1)));
}

int main() {
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);

    ii waypoint;
    cin >> m >> n;
    F0R(i, m) F0R(j, n) cin >> elevations[i][j];
    F0R(i, m) F0R(j, n) {
        int x; cin >> x;
        if (x == 1) {
            isWaypoint[i][j] = true;
            waypoint = mp(i, j);
            waypointCt++;
        } else {
            isWaypoint[i][j] = false;
        }
    }
    memset(taken, false, sizeof taken);
    process(waypoint); waypointCt--;

    int ans = 0;
    while (!pq.empty()) {
        pair<int, ii> next = pq.top(); pq.pop();
        if (taken[next.B.A][next.B.B]) continue;
        ans = max(ans, -next.A);
        if (isWaypoint[next.B.A][next.B.B]) {
            waypointCt--;
            if (waypointCt == 0) {
                cout << ans << endl;
                return 0;
            }
        }
        process(next.B);
    }

    return 0;
}
