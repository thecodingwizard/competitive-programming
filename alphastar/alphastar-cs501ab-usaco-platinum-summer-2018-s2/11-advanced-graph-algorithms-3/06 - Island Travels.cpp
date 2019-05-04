/*
Island Travels
==============

Farmer John has taken the cows to a vacation out on the ocean! The cows are
living on N (1 <= N <= 15) islands, which are located on an R x C grid (1
<= R, C <= 50). An island is a maximal connected group of squares on the
grid that are marked as 'X', where two 'X's are connected if they share a
side. (Thus, two 'X's sharing a corner are not necessarily connected.)

Bessie, however, is arriving late, so she is coming in with FJ by
helicopter. Thus, she can first land on any of the islands she chooses. She
wants to visit all the cows at least once, so she will travel between
islands until she has visited all N of the islands at least once.

FJ's helicopter doesn't have much fuel left, so he doesn't want to use it
until the cows decide to go home. Fortunately, some of the squares in the
grid are shallow water, which is denoted by 'S'. Bessie can swim through
these squares in the four cardinal directions (north, east, south, west) in
order to travel between the islands. She can also travel (in the four
cardinal directions) between an island and shallow water, and vice versa.

Find the minimum distance Bessie will have to swim in order to visit all of
the islands. (The distance Bessie will have to swim is the number of
distinct times she is on a square marked 'S'.) After looking at a map of
the area, Bessie knows this will be possible.

PROBLEM NAME: island2

INPUT FORMAT:

* Line 1: Two space-separated integers: R and C.

* Lines 2..R+1: Line i+1 contains C characters giving row i of the
        grid. Deep water squares are marked as '.', island squares are
        marked as 'X', and shallow water squares are marked as 'S'.

SAMPLE INPUT:

5 4
XX.S
.S..
SXSS
S.SX
..SX

INPUT DETAILS:

There are three islands with shallow water paths connecting some of them.

OUTPUT FORMAT:

* Line 1: A single integer representing the minimum distance Bessie
        has to swim to visit all islands.

SAMPLE OUTPUT:

3

OUTPUT DETAILS:

Bessie can travel from the island in the top left to the one in the middle,
swimming 1 unit, and then travel from the middle island to the one in the
bottom right, swimming 2 units, for a total of 3 units.
*/

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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int r, c;
int grid[52][52];
#define SHALLOW (-1)
#define DEEP (-2)
#define ISLAND (-3)
int islands = 0;
int dist[16][16];

bool visited[52][52];
void bfs(int startx, int starty) {
    int island = grid[startx][starty];
    if (island <= 0) return;
    int bfsDist[52][52];
    for (int i = 0; i < 52; i++) for (int j = 0; j < 52; j++) bfsDist[i][j] = INF;
    dist[island][island] = 0;
    bfsDist[startx][starty] = 0;
    memset(visited, false, sizeof visited);
    queue<ii> q; q.push(mp(startx, starty));
    int dx[4] = {1, 0, 0, -1};
    int dy[4] = {0, 1, -1, 0};
    while (!q.empty()) {
        ii front = q.front(); q.pop();
        if (visited[front.A][front.B]) continue;
        visited[front.A][front.B] = true;
        int x = front.A, y = front.B;
        for (int i = 0; i < 4; i++) {
            if (grid[x+dx[i]][y+dy[i]] == DEEP) continue;
            q.push(mp(x+dx[i], y+dy[i]));
            int prevDist = bfsDist[x+dx[i]][y+dy[i]];
            bfsDist[x+dx[i]][y+dy[i]] = min(bfsDist[x+dx[i]][y+dy[i]], bfsDist[x][y] + (grid[x+dx[i]][y+dy[i]] == SHALLOW ? 1 : 0));
            if (prevDist > bfsDist[x+dx[i]][y+dy[i]]) visited[x+dx[i]][y+dy[i]] = false;
            if (grid[x+dx[i]][y+dy[i]] > 0) {
                dist[island][grid[x+dx[i]][y+dy[i]]] = min(dist[island][grid[x+dx[i]][y+dy[i]]], bfsDist[x+dx[i]][y+dy[i]]);
            }
        }
    }
}

int memo[16][(1 << 16) - 1];

int tsp(int pos, int mask) {
    if (mask == (1 << islands) - 1) return 0;
    if (memo[pos][mask] != -1) return memo[pos][mask];
    int ans = INF;
    for (int i = 0; i < islands; i++) {
        if (i == pos || (mask & (1 << i)) || dist[pos+1][i+1] == INF) continue;
        ans = min(ans, dist[pos+1][i+1] + tsp(i, mask | (1 << i)));
    }
    return memo[pos][mask] = ans;
}

void dfsIsland(int i, int j, int island) {
    if (grid[i][j] != ISLAND) return;
    grid[i][j] = island;
    dfsIsland(i - 1, j, island);
    dfsIsland(i, j - 1, island);
    dfsIsland(i + 1, j, island);
    dfsIsland(i, j + 1, island);
}

int main() {
    cin >> r >> c;
    for (int i = 0; i < 52; i++) for (int j = 0; j < 52; j++) grid[i][j] = DEEP;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) {
            char ch; cin >> ch;
            if (ch == '.') grid[i][j] = DEEP;
            else if (ch == 'S') grid[i][j] = SHALLOW;
            else grid[i][j] = ISLAND;
        }
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) {
            if (grid[i][j] == ISLAND) dfsIsland(i, j, ++islands);
        }
    for (int i = 0; i <= 15; i++) for (int j = 0; j <= 15; j++) dist[i][j] = INF;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) {
            bfs(i, j);
        }
    memset(memo, -1, sizeof memo);
    int best = INF;
    for (int i = 1; i <= islands; i++) {
        memset(memo, -1, sizeof memo);
        best = min(best, tsp(i - 1, (1 << (i - 1))));
    }
    cout << best << endl;
    return 0;
}
