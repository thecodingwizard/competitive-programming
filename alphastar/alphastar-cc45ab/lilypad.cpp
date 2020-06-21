#include <bits/stdc++.h>

using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define ll long long

int main() {
    int n, m; cin >> n >> m;
    int A[n][m];
    ii start, end;
    F0R(i, n) {
        F0R(j, m) {
            int x; cin >> x;
            if (x == 3) {
                start = mp(i,j);
                x = 0;
            } else if (x == 4) {
                end = mp(i, j);
                x = 0;
            }
            A[i][j] = x;
        }
    }

    int dx[8] = {-2,-1,1,2,2,1,-1,-2};
    int dy[8] = {-1,-2,-2,-1,1,2,2,1};

    bool vis[n][m];
    vector<ii> adj[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] != 0) continue;

            for (int k = 0; k < n; k++) for (int l = 0; l < m; l++) vis[k][l] = false;

            vis[i][j] = true;
            queue<ii> q; q.push({i,j});

            while (!q.empty()) {
                ii u = q.front(); q.pop();
                if (!(u.f == i && u.s == j) && A[u.f][u.s] == 0) {
                    adj[i][j].push_back(u);
                    continue;
                }

                for (int k = 0; k < 8; k++) {
                    int a = u.f + dx[k], b = u.s + dy[k];
                    if (a < 0 || a >= n || b < 0 || b >= m || A[a][b] == 2) continue;

                    if (!vis[a][b]) {
                        vis[a][b] = true;
                        q.push({a,b});
                    }
                }
            }
        }
    }

    int cost[n][m]; ll ways[n][m];
    F0R(i, n) F0R(j, m) { cost[i][j] = 10000; ways[i][j] = 0; vis[i][j] = false; }

    queue<ii> q;
    cost[start.f][start.s] = 0; ways[start.f][start.s] = 1; vis[start.f][start.s] = true;
    q.push(start);

    while (!q.empty()) {
        ii u = q.front(); q.pop();

        for (ii v : adj[u.f][u.s]) {
            if (cost[v.f][v.s] < cost[u.f][u.s] + 1) continue;

            cost[v.f][v.s] = cost[u.f][u.s] + 1;
            ways[v.f][v.s] += ways[u.f][u.s];

            if (!vis[v.f][v.s]) {
                vis[v.f][v.s] = true;
                q.push(v);
            }
        }
    }

    if (cost[end.f][end.s] == 10000) cout << -1 << endl;
    else cout << cost[end.f][end.s] - 1 << endl << ways[end.f][end.s] << endl;
}
