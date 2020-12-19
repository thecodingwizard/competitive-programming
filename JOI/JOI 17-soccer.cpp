/*
 * It's never optimal for someone to touch the ball twice.
 *
 * We can solve with dijkstra's, where our state is
 *
 * dist(i, j, k): min cost to get the ball to (i,j) where:
 * - if 0 <= k <= 3, k represents the direction the ball is currently traveling
 *   (the ball is is being kicked)
 * - if k = 4, the ball is no longer traveling and is under the posession of a player
 *
 * We can use multi source BFS to find the min dist between every grid cell and the closest
 * player. Then, to transition to k = 4, we can just move the closest player to the
 * location of the ball.
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

int h, w; 
// min dist to get a player to (i, j)
ll getPlayer[501][501];
// min cost to get ball to (i, j)
// {0-3}: direction the ball is currently traveling (kicked)
// 4: The ball has landed and a person is currently holding it
ll dist[501][501][5];
ll a, b, c;

bool g(ii x) {
    return x.f >= 0 && x.f <= h && x.s >= 0 && x.s <= w;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    F0R(i, h+1) F0R(j, w+1) getPlayer[i][j] = 1e18;
    F0R(i, h+1) F0R(j, w+1) F0R(k, 5) dist[i][j][k] = 1e18;
    cin >> a >> b >> c;
    int n; cin >> n;
    queue<ii> q;
    ii first;
    F0R(i, n-1) {
        int x, y; cin >> x >> y; q.push(mp(x, y));
        if (i == 0) first = mp(x,y);
        getPlayer[x][y] = 0;
    }
    int dx[4]{-1,0,1,0};
    int dy[4]{0,-1,0,1};
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        F0R(i, 4) {
            ii v = mp(u.f+dx[i], u.s+dy[i]);
            if (g(v) && getPlayer[v.f][v.s] == 1e18) {
                getPlayer[v.f][v.s] = getPlayer[u.f][u.s]+1;
                q.push(v);
            }
        }
    }
    ii dest; cin >> dest.f >> dest.s;

    priority_queue<pair<ll, pair<ii, int>>, vector<pair<ll, pair<ii, int>>>, greater<pair<ll, pair<ii, int>>>> pq;
    pq.push(mp(0, mp(first, 4)));
    dist[first.f][first.s][4] = 0;
    while (!pq.empty()) {
        pair<ll, pair<ii, int>> top = pq.top(); pq.pop();
        ll d = top.f;
        ii u = top.s.f;
        int dir = top.s.s;
        if (dist[u.f][u.s][dir] != d) continue;
        
        if (dir == 4) {
            // choose a direction and kick it
            F0R(i, 4) {
                ii v = u;
                if (g(v) && dist[v.f][v.s][i] > d+b) {
                    dist[v.f][v.s][i] = d+b;
                    pq.push(mp(d+b, mp(v, i)));
                }
            }
            // or, choose a direction and move
            F0R(i, 4) {
                ii v = mp(u.f+dx[i], u.s+dy[i]);
                if (g(v) && dist[v.f][v.s][4] > d+c) {
                    dist[v.f][v.s][4] = d+c;
                    pq.push(mp(d+c, mp(v, 4)));
                }
            }
        } else {
            // keep kicking it
            ii v = mp(u.f+dx[dir], u.s+dy[dir]);
            if (g(v) && dist[v.f][v.s][dir] > d+a) {
                dist[v.f][v.s][dir] = d+a;
                pq.push(mp(d+a, mp(v, dir)));
            }
            // stop, get somebody to pick it up
            if (dist[u.f][u.s][4] > d+getPlayer[u.f][u.s]*c) {
                dist[u.f][u.s][4] = d+getPlayer[u.f][u.s]*c;
                pq.push(mp(d+getPlayer[u.f][u.s]*c, mp(u, 4)));
            }
        }
    }

    ll ans = dist[dest.f][dest.s][4];
    F0R(i, 4) ans = min(ans, dist[dest.f][dest.s][i]);
    cout << ans << endl;

    return 0;
}
