/*
 * Define dp[left][right][r][c] = min moves to get a robot containing [left...right] into the position (r, c)
 *
 * dp[left][right][r][c] = min(dp[left][mid][r][c] + dp[mid+1][right][r][c])
 *
 * Also, after computing dp[left][right] for a fixed [left, right], we need to handle the case where
 * a robot can move without merging. This can be done with dijkstra's (but this TLE's) or BFS.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int n, w, h; 
char A[500][500];
int moveOneRobot[9][500][500]; // cost to move robot i to (j, k)

ii nextPos[4][500][500]; // where we'll end up if we go in direction i from (j, k)
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
ii findNextPos(int dir, int r, int c) {
    if (nextPos[dir][r][c].f != -1) return nextPos[dir][r][c];
    nextPos[dir][r][c] = mp(-2, -2); // cycle

    int r2 = r + dx[dir], c2 = c + dy[dir];
    if (r2 < 0 || r2 >= h || c2 < 0 || c2 >= w || A[r2][c2] == 'x') {
        return nextPos[dir][r][c] = mp(r, c);
    }
    int nextDir = dir;
    if (A[r2][c2] == 'A') {
        nextDir = (dir+1)%4;
    } else if (A[r2][c2] == 'C') {
        nextDir = (dir-1+4)%4;
    }

    return nextPos[dir][r][c] = findNextPos(nextDir, r2, c2);
}

void calcDistForOneRobot(int idx) {
    ii start;
    F0R(i, h) F0R(j, w) {
        if (A[i][j] == '1'+idx) start = mp(i, j);
        moveOneRobot[idx][i][j] = inf;
    }

    queue<ii> q;
    q.push(start); moveOneRobot[idx][start.f][start.s] = 0;
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        F0R(dir, 4) {
            ii v = nextPos[dir][u.f][u.s];
            if (v.f != -2 && moveOneRobot[idx][v.f][v.s] == inf) {
                moveOneRobot[idx][v.f][v.s] = moveOneRobot[idx][u.f][u.s]+1;
                q.push(v);
            }
        }
    }
}

int dp[9][9][500][500];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> w >> h;
    F0R(i, h) F0R(j, w) cin >> A[i][j];

    F0R(i, h) F0R(j, w) F0R(k, 4) nextPos[k][i][j] = mp(-1, -1);
    F0R(i, h) F0R(j, w) F0R(k, 4) nextPos[k][i][j] = findNextPos(k, i, j);

    F0R(i, n) {
        calcDistForOneRobot(i);
    }

    // dp[left][right][r][c] = cost to get [left...right] into location (r, c)
    F0R(delta, n) {
        F0R(left, n) {
            int right = left + delta;
            if (right >= n) continue;

            F0R(r, h) {
                F0R(c, w) {
                    if (delta == 0) {
                        dp[left][right][r][c] = moveOneRobot[left][r][c];
                    } else {
                        dp[left][right][r][c] = inf;
                        FOR(mid, left, right) {
                            dp[left][right][r][c] = min(dp[left][right][r][c], dp[left][mid][r][c] + dp[mid+1][right][r][c]);
                        }
                    }
                }
            }

            map<int, vector<ii>> startNodes;
            F0R(r, h) F0R(c, w) if (dp[left][right][r][c] != inf) startNodes[dp[left][right][r][c]].pb(mp(r, c));
            deque<ii> q;

            while (!startNodes.empty()) {
                for (auto x : startNodes.begin()->second) {
                    if (dp[left][right][x.f][x.s] == startNodes.begin()->first) {
                        q.push_front(x);
                    }
                }
                startNodes.erase(startNodes.begin());

                while (!q.empty()) {
                    ii u = q.front();
                    int cost = dp[left][right][u.f][u.s];
                    if (!startNodes.empty() && startNodes.begin()->first < cost) break;
                    q.pop_front();

                    F0R(dir, 4) {
                        ii v = nextPos[dir][u.f][u.s];
                        if (v.s < 0) continue;
                        if (dp[left][right][v.f][v.s] > cost + 1) {
                            dp[left][right][v.f][v.s] = cost+1;
                            q.push_back(v);
                        }
                    }
                }
            }
        }
    }

    int ans = inf;
    F0R(r, h) {
        F0R(c, w) {
            ans = min(ans, dp[0][n-1][r][c]);
        }
    }
    if (ans == inf) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}
