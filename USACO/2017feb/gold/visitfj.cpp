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
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
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

int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);

    int n, t; cin >> n >> t;
    int time[n][n]; F0R(i, n) F0R(j, n) cin >> time[i][j];

    ll dist[n][n][3]; F0R(i, n) F0R(j, n) F0R(k, 3) dist[i][j][k] = LL_INF;
    dist[0][0][0] = 0;

    priority_queue<pair<ll, pair<int, ii>>, vector<pair<ll, pair<int, ii>>>, greater<pair<ll, pair<int, ii>>>> pq;
    pq.push(mp(0, mp(0, mp(0, 0))));

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    while (!pq.empty()) {
        pair<ll, pair<int, ii>> next = pq.top(); pq.pop();
        ll curDist = next.A; int fields = next.B.A; ii coords = next.B.B;
        if (curDist > dist[coords.A][coords.B][fields]) continue;
        F0R(i, 4) {
            int x = coords.A + dx[i], y = coords.B + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= n) continue;
            int nextFields = (fields + 1)%3;
            ll nextDist = curDist + t + (nextFields == 0 ? time[x][y] : 0);
            if (nextDist < dist[x][y][nextFields]) {
                dist[x][y][nextFields] = nextDist;
                pq.push(mp(nextDist, mp(nextFields, mp(x, y))));
            }
        }
    }

    ll best = LL_INF;
    F0R(i, 3) best = min(best, dist[n-1][n-1][i]);
    cout << best << endl;

    return 0;
}
