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

#define BLOCKED 0
#define EMPTY 1
#define DESTINATION 2

int n, m;
int grid[500][500];

ii getEndPosition(int x, int y, bool gravDirection) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == BLOCKED) {
        return mp(-1, -1);
    }
    if (grid[x][y] == DESTINATION) return mp(x, y);
    ii curPos = mp(x, y);
    while (true) {
        if (gravDirection) curPos.A--;
        else curPos.A++;
        if (curPos.A < 0 || curPos.A >= n) return mp(-1, -1);
        else if (grid[curPos.A][curPos.B] == BLOCKED) {
            if (gravDirection) curPos.A++;
            else curPos.A--;
            return mp(curPos.A, curPos.B);
        } else if (grid[curPos.A][curPos.B] == DESTINATION) {
            return mp(curPos.A, curPos.B);
        }
    }
}

int main() {
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);

    cin >> n >> m;
    int startX, startY;
    F0R(i, n) F0R(j, m) {
            char c; cin >> c;
            if (c == 'C') {
                startX = i, startY = j;
                c = '.';
            }
            if (c == '.') {
                grid[i][j] = EMPTY;
            } else if (c == '#') {
                grid[i][j] = BLOCKED;
            } else if (c == 'D') {
                grid[i][j] = DESTINATION;
            }
        }

    ii startPos = getEndPosition(startX, startY, false);
    if (startPos.A == -1) {
        cout << "-1" << endl;
        return 0;
    }

    // distance, gravityPointingUp, posX, posY
    priority_queue<pair<int, pair<bool, ii>>, vector<pair<int, pair<bool, ii>>>, greater<pair<int, pair<bool, ii>>>> pq;
    int dist[n][m][2]; F0R(i, n) F0R(j, m) F0R(k, 2) dist[i][j][k] = INF;
    dist[startPos.A][startPos.B][0] = 0;
    pq.push(mp(0, mp(false, mp(startPos.A, startPos.B))));
    while (!pq.empty()) {
        pair<int, pair<bool, ii>> next = pq.top(); pq.pop();
        int curDist = dist[next.B.B.A][next.B.B.B][next.B.A];
        if (curDist < next.A) continue;
        curDist = next.A;
        if (grid[next.B.B.A][next.B.B.B] == DESTINATION) {
            cout << curDist << endl;
            return 0;
        }
        // move right
        ii moveRight = getEndPosition(next.B.B.A, next.B.B.B+1, next.B.A);
        if (moveRight.A != -1) {
            if (curDist < dist[moveRight.A][moveRight.B][next.B.A]) {
                dist[moveRight.A][moveRight.B][next.B.A] = curDist;
                pq.push(mp(dist[moveRight.A][moveRight.B][next.B.A], mp(next.B.A, mp(moveRight.A, moveRight.B))));
            }
        }
        // move left
        ii moveLeft = getEndPosition(next.B.B.A, next.B.B.B-1, next.B.A);
        if (moveLeft.A != -1) {
            if (curDist < dist[moveLeft.A][moveLeft.B][next.B.A]) {
                dist[moveLeft.A][moveLeft.B][next.B.A] = curDist;
                pq.push(mp(dist[moveLeft.A][moveLeft.B][next.B.A], mp(next.B.A, mp(moveLeft.A, moveLeft.B))));
            }
        }
        // flip gravity
        ii flip = getEndPosition(next.B.B.A, next.B.B.B, !next.B.A);
        if (flip.A != -1) {
            if (curDist + 1 < dist[flip.A][flip.B][!next.B.A]) {
                dist[flip.A][flip.B][!next.B.A] = curDist + 1;
                pq.push(mp(dist[flip.A][flip.B][!next.B.A], mp(!next.B.A, mp(flip.A, flip.B))));
            }
        }
    }

    cout << "-1" << endl;

    return 0;
}
