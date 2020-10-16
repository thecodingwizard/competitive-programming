/*
 * https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2007/olympiad_solutions/solutions.pdf
 *
 * Each cell's political affiliation can be determined through its indices, regardless
 * of how the obstacles are positioned.
 *
 * Brute force distances for 2002x2002 grid around the center. Then, for each cell
 * on the outer border with distance d, there will still be S-d politicians of
 * alternating political parties that are on the row/column of the cell. use math
 * to update party counts.
 *
 * Then, for each of the four corners, we can use math again and take advantage
 * of the triangle pattern to calculate party counts.
 *
 * See the solution code and editorial for more details
 */

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second
#define maxn 2010
using ll = long long;

bool blocked[maxn][maxn];
int dist[maxn][maxn];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
    int b, s; cin >> b >> s;
    for (int i = 0; i < b; i++) {
        int a, b; cin >> a >> b;
        blocked[a+maxn/2][b+maxn/2] = 1;
    }

    for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) dist[i][j] = -1;
    dist[maxn/2][maxn/2] = 0;
    queue<ii> q;
    q.push(mp(maxn/2, maxn/2));

    while (!q.empty()) {
        ii u = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            ii v = mp(u.f+dx[i],u.s+dy[i]);
            if (v.f >= 0 && v.f < maxn && v.s >= 0 && v.s < maxn && dist[v.f][v.s] == -1 && !blocked[v.f][v.s]) {
                dist[v.f][v.s] = dist[u.f][u.s]+1;
                q.push(v);
            }
        }
    }
    ll p1 = 0, p2 = 0;
    for (int i = 0; i < maxn; i++) for (int j = 0; j < maxn; j++) {
        if (dist[i][j] == -1) continue;
        if (dist[i][j] <= s) {
            if ((i+j)%2==0) p1++;
            else p2++;
        }
        if (j == 0 || j == maxn-1) {
            ll extra = s - dist[i][j];
            if (extra <= 0) continue;
            if ((i+j)%2==0) {
                p1 += (extra)/2;
                p2 += (extra+1)/2;
            } else {
                p1 += (extra+1)/2;
                p2 += (extra)/2;
            }
        }
        if (i == 0 || i == maxn-1) {
            ll extra = s - dist[i][j];
            if (extra <= 0) continue;
            if ((i+j)%2==0) {
                p1 += (extra)/2;
                p2 += (extra+1)/2;
            } else {
                p1 += (extra+1)/2;
                p2 += (extra)/2;
            }
        }
        if (i == 0 && j == 0 || i == 0 && j == maxn-1 || j == 0 && i == maxn-1 || j == maxn-1 && i == maxn-1) {
            ll extra = s - dist[i][j] - 1;
            if (extra <= 0) continue;
            if ((i+j)%2==0) {
                p1 += ((extra+1)/2)*((extra+1)/2);
                p2 += ((extra)/2)*((extra)/2)+(extra/2);
            } else {
                p2 += ((extra+1)/2)*((extra+1)/2);
                p1 += ((extra)/2)*((extra)/2)+(extra/2);
            }
        }
    }

    cout << p1 << " " << p2 << endl;
    return 0;
}
