/*
 * Used alternate solution in editorial
 *
 * Basically, take the leftmost wall and traverse clockwise by imagining
 * putting your right hand on the leftmost wall and traversing the edge.
 *
 * - Go left if possible, then
 * - Go straight if possible, then
 * - Go right if possible, then
 * - Backtrack
 *
 * If a wall is traversed in both directions, then it will survive.
 *
 * After each traversal, remove the edges you touched, find the next
 * leftmost wall, and repeat.
 *
 * My implementation is really bad and just barely passes memory limit...
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define ll long long

ii A[100000];
struct Wall {
    int a, b;

    bool operator<(const Wall &other) const {
        int x = min(A[a].f, A[b].f);
        int y = min(A[other.a].f, A[other.b].f);
        int X = max(A[a].f, A[b].f);
        int Y = max(A[other.a].f, A[other.b].f);
        if (x==y&&X==Y) {
            return a==other.a?b<other.b:a<other.a;
        }
        return x==y?X<Y:x<y;
    }
};

int n;
vector<int> graph[100000];
vector<Wall> walls;
auto swcmp = [](const int &a, const int &b) { return walls[a] < walls[b]; };
set<int, decltype(swcmp)> sortedWalls(swcmp);
bitset<200000> vis[2];
bitset<200000> done;
vector<int> justDone;

ll cross(int a, int b, int c) {
    int w = A[b].f-A[a].f, x = A[b].s - A[a].s, y = A[c].f - A[b].f, z = A[c].s - A[b].s;
    return (ll)w*z-(ll)x*y;
}

bool turnRight(int a, int b, int c) {
    return cross(a, b, c) < 0;
}
bool turnLeft(int a, int b, int c) {
    return cross(a, b, c) > 0;
}
bool goForward(int a, int b, int c) {
    int w = A[b].f-A[a].f, x = A[b].s - A[a].s, y = A[c].f - A[b].f, z = A[c].s - A[b].s;
    return (w==y&&(x<0)==(z<0))||(x==z&&(w<0)==(y<0));
    //return (A[a].f==A[b].f&&A[b].f==A[c].f&&(A[a].s<A[b].s&&A[b].s<A[c].s||A[a].s>A[b].s&&A[b].s>A[c].s))||(A[a].s==A[b].s&&A[b].s==A[c].s&&(A[a].f<A[b].f&&A[b].f<A[c].f||A[a].f>A[b].f&&A[b].f>A[c].f));
}

bool goBack(int a, int b, int c) {
    int w = A[b].f-A[a].f, x = A[b].s - A[a].s, y = A[c].f - A[b].f, z = A[c].s - A[b].s;
    return (w==y&&(x<0)!=(z<0))||(x==z&&(w<0)!=(y<0));
    //return (A[a].f==A[b].f&&A[b].f==A[c].f&&(A[a].s<A[b].s&&A[b].s<A[c].s||A[a].s>A[b].s&&A[b].s>A[c].s))||(A[a].s==A[b].s&&A[b].s==A[c].s&&(A[a].f<A[b].f&&A[b].f<A[c].f||A[a].f>A[b].f&&A[b].f>A[c].f));
}

void go(int u, int dir) {
    //cout << "go: " << u << " " << dir << endl;
    if (vis[dir][u]) return;
    vis[dir][u] = true;
    justDone.push_back(u);
    Wall w = walls[u];
    sortedWalls.erase(u);

    int prvNode = dir == 0 ? w.b : w.a;
    int node = dir == 0 ? w.a : w.b;

    // left
    for (int wID : graph[node]) {
        int nxtNode = walls[wID].a == node ? walls[wID].b : walls[wID].a;
        int nxtDir = walls[wID].a == nxtNode ? 0 : 1;
        if (!done[wID] && turnLeft(prvNode, node, nxtNode)) {
            //cout << "left" << endl;
            return go(wID, nxtDir);
        }
    }

    // forward
    for (int wID : graph[node]) {
        int nxtNode = walls[wID].a == node ? walls[wID].b : walls[wID].a;
        int nxtDir = walls[wID].a == nxtNode ? 0 : 1;
        if (!done[wID] && goForward(prvNode, node, nxtNode)) {
            //cout << "forward" << endl;
            return go(wID, nxtDir);
        }
    }
    
    // right
    for (int wID : graph[node]) {
        int nxtNode = walls[wID].a == node ? walls[wID].b : walls[wID].a;
        int nxtDir = walls[wID].a == nxtNode ? 0 : 1;
        if (!done[wID] && turnRight(prvNode, node, nxtNode)) {
            //cout << "right" << endl;
            return go(wID, nxtDir);
        }
    }
    
    // back
    for (int wID : graph[node]) {
        int nxtNode = walls[wID].a == node ? walls[wID].b : walls[wID].a;
        int nxtDir = walls[wID].a == nxtNode ? 0 : 1;
        if (!done[wID]) {
            assert(goBack(prvNode, node, nxtNode));
            //cout << "back" << endl;
            return go(wID, nxtDir);
        }
    }
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i].f >> A[i].s;
    int w; cin >> w;
    for (int i = 0; i < w; i++) {
        int a, b; cin >> a >> b; --a; --b;
        walls.push_back({a,b});
        sortedWalls.insert(i);
        graph[a].push_back(i);
        graph[b].push_back(i);
        vis[0][i] = vis[1][i] = false;
        done[i] = false;
    }

    while (!sortedWalls.empty()) {
        //cout << "=== new go ===" << endl;
        int u = *sortedWalls.begin();
        int x = A[walls[u].a].f - A[walls[u].b].f, y = A[walls[u].b].s - A[walls[u].a].s;
        if (x<0||y<0) {
            go(*sortedWalls.begin(), 0);
        } else {
            go(*sortedWalls.begin(), 1);
        }
        
        for (int x : justDone) done[x] = true;
        justDone.clear();
    }

    int sz = 0;
    for (int i = 0; i < w; i++) {
        if (vis[0][i] && vis[1][i]) {
            sz++;
        }
    }
    cout << sz << endl;
    for (int i = 0; i < w; i++) {
        if (vis[0][i] && vis[1][i]) {
            cout << i+1 << endl;
        }
    }

    return 0;
}
