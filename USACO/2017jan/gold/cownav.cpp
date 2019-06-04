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

int n;
bool blocked[20][20];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int dist[20][20][4][20][20][4];
bool visited[20][20][4][20][20][4];

struct State {
    int x1, y1, d1, x2, y2, d2;
};

int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);

    cin >> n;
    F0Rd(i, n) F0R(j, n) { char x; cin >> x; blocked[i][j] = x == 'H'; }

    queue<State> q;
    F0R(i, n) F0R(j, n) F0R(k, 4) F0R(l, n) F0R(m, n) F0R(o, 4) dist[i][j][k][l][m][o] = INF;
    memset(visited, false, sizeof visited);
    dist[0][0][0][0][0][1] = 0;
    q.push(State{0, 0, 0, 0, 0, 1});
    while (!q.empty()) {
        State next = q.front(); q.pop();
        int x1 = next.x1, y1 = next.y1, d1 = next.d1, x2 = next.x2, y2 = next.y2, d2 = next.d2;
        if (visited[x1][y1][d1][x2][y2][d2]) continue;
        visited[x1][y1][d1][x2][y2][d2] = true;
        int curDist = dist[x1][y1][d1][x2][y2][d2];
        int X1 = x1+dx[d1], Y1 = y1+dy[d1], X2 = x2+dx[d2], Y2 = y2+dy[d2];
        if (x1 == n-1 && y1 == n-1 || X1 < 0 || X1 >= n || Y1 < 0 || Y1 >= n || blocked[X1][Y1]) {
            X1 = x1; Y1 = y1;
        }
        if (x2 == n-1 && y2 == n-1 || X2 < 0 || X2 >= n || Y2 < 0 || Y2 >= n || blocked[X2][Y2]) {
            X2 = x2; Y2 = y2;
        }
        if (dist[X1][Y1][d1][X2][Y2][d2] > curDist + 1) {
            dist[X1][Y1][d1][X2][Y2][d2] = curDist + 1;
            q.push(State{X1, Y1, d1, X2, Y2, d2});
        }
        if (dist[x1][y1][(d1+1)%4][x2][y2][(d2+1)%4] > curDist + 1) {
            dist[x1][y1][(d1+1)%4][x2][y2][(d2+1)%4] = curDist + 1;
            q.push(State{x1,y1,(d1+1)%4,x2,y2,(d2+1)%4});
        }
        if (dist[x1][y1][(d1-1+4)%4][x2][y2][(d2-1+4)%4] > curDist + 1) {
            dist[x1][y1][(d1-1+4)%4][x2][y2][(d2-1+4)%4] = curDist+1;
            q.push(State{x1,y1,(d1-1+4)%4,x2,y2,(d2-1+4)%4});
        }
    }

    int ans = INF;
    F0R(i, 4) F0R(j, 4) ans = min(ans, dist[n-1][n-1][i][n-1][n-1][j]);

    cout << ans << endl;

    return 0;
}
