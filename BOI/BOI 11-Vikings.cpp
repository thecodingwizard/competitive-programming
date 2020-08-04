/*
 * compute B[i][j] = number of moves for pirate ship to be able to see (i, j) using a BFS
 *
 * Then, BFS from your starting location. You can only move to an adjacent location if B[i][j] is
 * strictly greater than the number of moves it takes for you to reach that location.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int pirateDone[700][700];

int main() {
    int n, m; cin >> n >> m;

    char A[n][m];
    int B[n][m];
    int C[n][m];
    ii me, pirate, treasure;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            B[i][j] = 1e9;
            cin >> A[i][j];
            if (A[i][j] == 'Y') {
                me = mp(i, j);
                A[i][j] = '.';
            } else if (A[i][j] == 'V') {
                pirate = mp(i, j);
                A[i][j] = '.';
            } else if (A[i][j] == 'T') {
                treasure = mp(i, j);
                A[i][j] = '.';
            }
        }
    }

    queue<ii> q;
    int vis[n][m];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) vis[i][j] = false;
    q.push(pirate); vis[pirate.f][pirate.s] = true;
    C[pirate.f][pirate.s] = 0;
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        for (int i = 0; i + u.f < n && A[i+u.f][u.s] != 'I' && (pirateDone[i+u.f][u.s] & 1) == 0; i++) {
            B[i+u.f][u.s] = min(C[u.f][u.s], B[i+u.f][u.s]);
            pirateDone[i+u.f][u.s] |= 1;
        }
        for (int i = 0; u.f - i >= 0 && A[u.f-i][u.s] != 'I' && (pirateDone[u.f-i][u.s] & 2) == 0; i++) {
            B[u.f-i][u.s] = min(C[u.f][u.s], B[u.f-i][u.s]);
            pirateDone[u.f-i][u.s] |= 2;
        }
        for (int i = 0; i + u.s < m && A[u.f][u.s+i] != 'I' && (pirateDone[u.f][u.s+i] & 4) == 0; i++) {
            B[u.f][u.s+i] = min(C[u.f][u.s], B[u.f][u.s+i]);
            pirateDone[u.f][u.s+i] |= 4;
        }
        for (int i = 0; u.s - i >= 0 && A[u.f][u.s-i] != 'I' && (pirateDone[u.f][u.s-i] & 8) == 0; i++) {
            B[u.f][u.s-i] = min(C[u.f][u.s], B[u.f][u.s-i]);
            pirateDone[u.f][u.s-i] |= 8;
        }
        for (int i = 0; i < 4; i++) {
            int a = u.f + dx[i], b = u.s + dy[i];
            if (a >= 0 && a < n && b >= 0 && b < m && A[a][b] != 'I' && !vis[a][b]) {
                C[a][b] = C[u.f][u.s]+1;
                vis[a][b] = true;
                q.push(mp(a, b));
            }
        }
    }

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) vis[i][j] = -1;
    q.push(me); vis[me.f][me.s] = 0;
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int a = u.f + dx[i], b = u.s + dy[i];
            if (a >= 0 && a < n && b >= 0 && b < m && A[a][b] != 'I' && vis[a][b] == -1 && vis[u.f][u.s]+1 < B[a][b]) {
                vis[a][b] = vis[u.f][u.s]+1;
                q.push(mp(a, b));
            }
        }
    }

    if (vis[treasure.f][treasure.s] == -1) cout << "NO" << endl;
    else cout << "YES" << endl;

    return 0;
}
