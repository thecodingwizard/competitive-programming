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
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, m, queries;
char graph[1500][1500];
int dfsLow[1500][1500], dfsNum[1500][1500], dfsCtr;
set<int> componentNum[1500][1500];
int componentCtr;
bool visited[1500][1500][4];
bool can[1500][1500];
bool reachable[1500][1500];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

vector<pair<ii, ii>> S;

void dfs(ii node, ii parent) {
    dfsLow[node.pA][node.pB] = dfsNum[node.pA][node.pB] = dfsCtr++;

    int children = 0;
    F0R(i, 4) {
        ii next = {node.pA + dx[i], node.pB + dy[i]};
        if (next.pA < 0 || next.pA >= n || next.pB < 0 || next.pB >= m) continue;
        if (graph[next.pA][next.pB] == '#') continue;

        if (dfsNum[next.pA][next.pB] == INF) {
            S.pb(mp(node, next));
            dfs(next, node);
            children++;

            if ((parent.pA == -1 && children > 1) || (dfsLow[next.pA][next.pB] >= dfsNum[node.pA][node.pB])) {
                while (true) {
                    pair<ii, ii> prev = S.back(); S.pop_back();
                    componentNum[prev.pA.pA][prev.pA.pB].insert(componentCtr);
                    componentNum[prev.pB.pA][prev.pB.pB].insert(componentCtr);
                    if (prev == mp(node, next)) break;
                }
                componentCtr++;
            }

            dfsLow[node.pA][node.pB] = min(dfsLow[node.pA][node.pB], dfsLow[next.pA][next.pB]);
        } else if (next != parent && dfsLow[node.pA][node.pB] > dfsNum[next.pA][next.pB]) {
            dfsLow[node.pA][node.pB] = dfsNum[next.pA][next.pB];
            S.pb(mp(node, next));
        }
    }
}

bool visited2[1500][1500];
void dfs2(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || graph[x][y] == '#' || graph[x][y] == 'B') return;
    if (visited2[x][y]) return;
    visited2[x][y] = true;
    reachable[x][y] = true;
    F0R(i, 4) {
        dfs2(x + dx[i], y + dy[i]);
    }
}

bool sameComponent(ii a, ii b) {
    for (int c : componentNum[a.pA][a.pB]) {
        if (componentNum[b.pA][b.pB].count(c) > 0) return true;
    }
    return false;
}

int main() {
    setupIO("pushabox");

    SET2D(dfsLow, INF, 1500, 1500);
    SET2D(dfsNum, INF, 1500, 1500);
    SET2D(can, false, 1500, 1500);
    SET2D(reachable, false, 1500, 1500);
    SET2D(visited2, false, 1500, 1500);
    SET3D(visited, false, 1500, 1500, 4);
    componentCtr = 0;
    dfsCtr = 0;

    cin >> n >> m >> queries;
    ii bessie, box;
    F0R(i, n) {
        F0R(j, m) {
            cin >> graph[i][j];
            if (graph[i][j] == 'A') {
                bessie = { i, j };
            } else if (graph[i][j] == 'B') {
                box = { i, j };
                can[i][j] = true;
            }
        }
    }

    F0R(i, n) {
        F0R(j, m) {
            if (graph[i][j] == '#') continue;
            if (dfsNum[i][j] == INF) dfs(mp(i, j), mp(-1, -1));
        }
    }

    dfs2(bessie.pA, bessie.pB);

    queue<pair<ii, int>> q;
    F0R(i, 4) {
        ii spot = { box.pA + dx[i], box.pB + dy[i] };
        if (spot.pA < 0 || spot.pA >= n || spot.pB < 0 || spot.pB >= m || graph[spot.pA][spot.pB] == '#') continue;
        if (reachable[spot.pA][spot.pB]) {
            q.push(mp(box, i));
        }
    }

    while (!q.empty()) {
        pair<ii, int> next = q.front(); q.pop();
        if (visited[next.pA.pA][next.pA.pB][next.pB]) continue;
        visited[next.pA.pA][next.pA.pB][next.pB] = true;
        can[next.pA.pA][next.pA.pB] = true;

        ii cowPos = { next.pA.pA + dx[next.pB], next.pA.pB + dy[next.pB] };
        F0R(i, 4) {
            ii spot = { next.pA.pA + dx[i], next.pA.pB + dy[i] };
            if (spot.pA < 0 || spot.pA >= n || spot.pB < 0 || spot.pB >= m || graph[spot.pA][spot.pB] == '#') continue;
            if (sameComponent(cowPos, spot)) {
                ii newBox = { next.pA.pA + dx[(i+2)%4], next.pA.pB + dy[(i+2)%4] };
                if (newBox.pA < 0 || newBox.pA >= n || newBox.pB < 0 || newBox.pB >= m || graph[newBox.pA][newBox.pB] == '#') continue;
                q.push(mp(newBox, i));
            }
        }
    }

    F0R(i, queries) {
        int a, b; cin >> a >> b;
        --a; --b;
        if (can[a][b]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
