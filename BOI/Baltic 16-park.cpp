/*
 * https://usaco.guide/solutions/baltic-16-park
 *
 * Except instead of using 4 nodes for the walls, you can just store, for each component, whether there's an edge connecting it to each of the four walls.
 * I think this makes for an easier implementation.
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
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

bool can[4][4];
#define maxn 2000
bool wallTop[maxn], wallBot[maxn], wallLeft[maxn], wallRight[maxn];

struct object {
    int x, y, r;
};

void updCan(int i) {
    //cout << i << endl;
    if (wallTop[i] && wallBot[i]) {
        //cout << "top & bot" << endl;
        can[0][1] = can[0][2] = can[3][1] = can[3][2] = can[1][0] = can[2][0] = can[1][3] = can[2][3] = 0;
    }
    if (wallTop[i] && wallLeft[i]) {
        //cout << "top & left" << endl;
        can[3][0] = can[3][1] = can[3][2] = can[0][3] = can[1][3] = can[2][3] = 0;
    }
    if (wallTop[i] && wallRight[i]) {
        //cout << "top & right" << endl;
        can[2][0] = can[2][1] = can[2][3] = can[0][2] = can[1][2] = can[3][2] = 0;
    }
    if (wallLeft[i] && wallRight[i]) {
        //cout << "left & right" << endl;
        can[2][0] = can[2][1] = can[0][2] = can[1][2] = can[0][3] = can[1][3] = can[3][1] = can[3][0] = 0;
    }
    if (wallLeft[i] && wallBot[i]) {
        //cout << "left & bot" << endl;
        can[0][3] = can[0][1] = can[0][2] = can[2][0] = can[1][0] = can[3][0] = 0;
    }
    if (wallRight[i] && wallBot[i]) {
        //cout << "right & bot" << endl;
        can[1][0] = can[1][3] = can[1][2] = can[0][1] = can[3][1] = can[2][1] = 0;
    }
}

int pa[maxn], sz[maxn];
int get(int x) {
    return pa[x] == x ? x : pa[x] = get(pa[x]);
}
void unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    sz[b] += sz[a];
    pa[a] = b;
    wallTop[b] = wallTop[b] || wallTop[a];
    wallBot[b] = wallBot[b] || wallBot[a];
    wallLeft[b] = wallLeft[b] || wallLeft[a];
    wallRight[b] = wallRight[b] || wallRight[a];
    updCan(b);
}

vector<object> objects;
ll getDist(int i, int j) {
    ll dx = abs(objects[i].x-objects[j].x);
    ll dy = abs(objects[i].y-objects[j].y);
    return dx*dx+dy*dy;
}

string ans[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, w, h; cin >> n >> m >> w >> h;
    
    F0R(i, 4) F0R(j, 4) can[i][j] = true;

    F0R(i, n) {
        int x, y, r; cin >> x >> y >> r;
        objects.pb({x,y,r});
    }

    F0R(i, n) {
        sz[i] = 1;
        pa[i] = i;
    }

    vector<pair<ii, int>> queries;
    F0R(i, m) {
        int r, e; cin >> r >> e; --e;
        queries.pb(mp(mp(2*r, e), i));
    }
    sort(all(queries));

    // <radius, <eventType: 0 = wall update, 1 = union; <param1, param2>>>
    // update when radius is strictly greater than event
    vector<pair<int, pair<int, ii>>> events;
    // 0 = bot, 1 = right, 2 = top, 3 = left
    F0R(i, n) {
        events.pb(mp(objects[i].y-objects[i].r, mp(0, mp(i, 0))));
        events.pb(mp(w-objects[i].x-objects[i].r, mp(0, mp(i, 1))));
        events.pb(mp(h-objects[i].y-objects[i].r, mp(0, mp(i, 2))));
        events.pb(mp(objects[i].x-objects[i].r, mp(0, mp(i, 3))));
    }
    F0R(i, n) {
        FOR(j, i+1, n) {
            ll minR = floor(sqrt(getDist(i, j))) - objects[i].r - objects[j].r;
            events.pb(mp(minR, mp(1, mp(i, j))));
        }
    }
    sort(all(events));

    int idx = 0;
    for (auto q : queries) {
        while (idx < (int)events.size() && events[idx].f < q.f.f) {
            auto e = events[idx].s;
            if (e.f == 0) {
                if (e.s.s == 0) {
                    wallBot[get(e.s.f)] = 1;
                } else if (e.s.s == 1) {
                    wallRight[get(e.s.f)] = 1;
                } else if (e.s.s == 2) {
                    wallTop[get(e.s.f)] = 1;
                } else {
                    wallLeft[get(e.s.f)] = 1;
                }
                updCan(get(e.s.f));
            } else {
                unite(e.s.f, e.s.s);
            }
            idx++;
        }
        F0R(i, 4) if (can[q.f.s][i]) ans[q.s] = ans[q.s] + to_string(i+1);
    }

    F0R(i, m) cout << ans[i] << endl;

    return 0;
}
