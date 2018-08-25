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

int n, x1, Y1, x2, y2;
int up[100010], down[100010], left1[100010], right1[100010];
map<int, vii> h, v;
int dist[100010][4];
bool visited[100010][4];

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);

    cin >> n >> x1 >> Y1 >> x2 >> y2;
    F0R(i, n) {
        int x, y; cin >> x >> y;
        v[x].push_back(mp(y, i+1));
        h[y].push_back(mp(x, i+1));
    }
    v[x1].push_back(mp(Y1, 0));
    h[Y1].push_back(mp(x1, 0));
    v[x2].push_back(mp(y2, n+1));
    h[y2].push_back(mp(x2, n+1));
    for (pair<int, vii> x : h) {
        SORT(x.B);
        F0R(i, x.B.size()) {
            if (i == 0) left1[x.B[i].B] = -1;
            else {
                left1[x.B[i].B] = x.B[i-1].B;
            }
            if (i + 1 < x.B.size()) {
                right1[x.B[i].B] = x.B[i+1].B;
            } else {
                right1[x.B[i].B] = -1;
            }
        }
    }
    for (pair<int, vii> x : v) {
        SORT(x.B);
        F0R(i, x.B.size()) {
            if (i == 0) {
                down[x.B[i].B] = -1;
            } else {
                down[x.B[i].B] = x.B[i - 1].B;
            }
            if (i + 1 < x.B.size()) {
                up[x.B[i].B] = x.B[i+1].B;
            } else {
                up[x.B[i].B] = -1;
            }
        }
    }

    queue<ii> q;
    F0R(i, 4) q.push(mp(0, i));
    F0R(i, n+5) F0R(j, 4) dist[i][j] = INF;
    memset(visited, false, sizeof visited);
    F0R(i, 4) dist[0][i] = 0;

    while (!q.empty()) {
        ii next = q.front(); q.pop();
        int node = next.A, dir = next.B;
        if (visited[node][dir]) continue;
        visited[node][dir] = true;
        if (up[node] != -1 && dir != DOWN) {
            dist[up[node]][UP] = min(dist[up[node]][UP], dist[node][dir] + (dir != UP));
            q.push(mp(up[node], UP));
        }
        if (left1[node] != -1 && dir != RIGHT) {
            dist[left1[node]][LEFT] = min(dist[left1[node]][LEFT], dist[node][dir] + (dir != LEFT));
            q.push(mp(left1[node], LEFT));
        }
        if (right1[node] != -1 && dir != LEFT) {
            dist[right1[node]][RIGHT] = min(dist[right1[node]][RIGHT], dist[node][dir]  + (dir != RIGHT));
            q.push(mp(right1[node], RIGHT));
        }
        if (down[node] != -1 && dir != UP) {
            dist[down[node]][DOWN] = min(dist[down[node]][DOWN], dist[node][dir] + (dir != DOWN));
            q.push(mp(down[node], DOWN));
        }
    }

    int ans = INF;
    F0R(i, 4) ans = min(ans, dist[n+1][i]);

    cout << (ans == INF ? -1 : ans) << endl;

    return 0;
}
