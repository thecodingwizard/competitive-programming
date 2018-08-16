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

int n, m;
int grid[1000][1000];
int dist[1000][1000][2];

struct State {
    int cost, x, y, smell;

    bool operator>(const State other) const {
        return cost > other.cost;
    }
};

State calcMove(State state, int dx, int dy) {
    int x = state.x + dx, y = state.y + dy;
    if (x < 0 || x >= n || y < 0 || y >= m) return State{-1,0,0,0};
    if (grid[x][y] == 0 || (grid[x][y] == 3 && state.smell == 0)) return State{-1,0,0,0};
    if (grid[x][y] == 1) return State{state.cost+1, x, y, state.smell};
    if (grid[x][y] == 2) return State{state.cost+1, x, y, 1};
    if (grid[x][y] == 3) return State{state.cost+1, x, y, 1};
    if (grid[x][y] == 4) {
        State next = calcMove(State{state.cost+1, x, y, 0}, dx, dy);
        if (next.cost == -1) {
            return State{state.cost+1, x, y, 0};
        } else {
            return next;
        }
    }
}

int main() {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);

    cin >> n >> m;
    F0R(i, n) F0R(j, m) cin >> grid[i][j];

    F0R(i, n) F0R(j, m) F0R(k, 2) dist[i][j][k] = INF;
    dist[0][0][0] = 0;

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push(State{0, 0, 0, 0});

    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, 1, -1, 0};
    while (!pq.empty()) {
        State next = pq.top(); pq.pop();
        if (next.cost > dist[next.x][next.y][next.smell]) continue;
        F0R(i, 4) {
            State move = calcMove(next, dx[i], dy[i]);
            if (move.cost == -1) continue;
            if (dist[move.x][move.y][move.smell] > move.cost) {
                dist[move.x][move.y][move.smell] = move.cost;
                pq.push(move);
            }
        }
    }

    int ans = min(dist[n-1][m-1][0], dist[n-1][m-1][1]);
    if (ans == INF) cout << "-1" << endl;
    else cout << ans << endl;

    return 0;
}
