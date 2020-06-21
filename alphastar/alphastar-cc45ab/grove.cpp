#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int main() {
    int r, c; cin >> r >> c;
    ii topRight = { 1000, -1 };
    ii start;

    char A[r][c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> A[i][j];
            if (A[i][j] == 'X') {
                if (topRight.f > i) {
                    topRight = mp(i, j);
                } else if (topRight.f == i && topRight.s < j) {
                    topRight = mp(i, j);
                }
            } else if (A[i][j] == '*') start = mp(i, j);
        }
    }

    // draw a line segment from the top right point all the way to the right border.
    // we want to find shortest path that crosses this segment exactly once.
    
    // <<x, y>, crossedLine>
    queue<pair<ii, bool>> q;
    int dist[r][c][2]; for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) for (int k = 0; k < 2; k++) dist[i][j][k] = 1000;
    dist[start.f][start.s][0] = 0;
    q.push({start, 0});

    int dx[8] = { -1, 0, 1, 0, 1, 1, -1, -1 };
    int dy[8] = { 0, 1, 0, -1, 1, -1, 1, -1 };
    while (!q.empty()) {
        pair<ii, bool> u = q.front(); q.pop();
        for (int i = 0; i < 8; i++) {
            int a = u.f.f + dx[i], b = u.f.s + dy[i];
            if (a < 0 || a >= r || b < 0 || b >= c) continue;
            if (A[a][b] == 'X') continue;
            
            bool crossedAboveLine = (u.f.f >= topRight.f && u.f.s >= topRight.s) && (a < topRight.f && b >= topRight.s);
            if (crossedAboveLine && u.s) continue;

            bool crossedBelowLine = (u.f.f < topRight.f && u.f.s >= topRight.s) && (a >= topRight.f && b >= topRight.s);
            if (crossedBelowLine && u.s) continue;

            bool nextNodePassedLine = u.s || crossedAboveLine || crossedBelowLine;
            if (dist[a][b][nextNodePassedLine] == 1000) {
                dist[a][b][nextNodePassedLine] = dist[u.f.f][u.f.s][u.s] + 1;
                q.push({{a,b},nextNodePassedLine});
            }
        }
    }

    cout << dist[start.f][start.s][1] << endl;

    return 0;
}
