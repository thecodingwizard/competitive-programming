/*
ID: nathan.18
TASK: castle
LANG: C++
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
#include <fstream>

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int m, n;
bool passable[50][50][4]; // north, east, south, west
int room[50][50];
int roomSize[2501];
int biggestOriginalRoom = 0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
void floodfill(int i, int j, int color) {
    if (i < 0 || i >= m || j < 0 || j >= n || room[i][j] != -1) return;
    room[i][j] = color;
    roomSize[color]++;
    biggestOriginalRoom = max(biggestOriginalRoom, roomSize[color]);
    for (int x = 0; x < 4; x++) {
        if (passable[i][j][x]) {
            floodfill(i + dy[x], j + dx[x], color);
        }
    }
}

int main() {
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);

    cin >> n >> m;
    memset(passable, true, sizeof passable);
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            int x; cin >> x;
            if (x >= 8) {
                x -= 8;
                passable[i][j][2] = false;
            }
            if (x >= 4) {
                x -= 4;
                passable[i][j][1] = false;
            }
            if (x >= 2) {
                x -= 2;
                passable[i][j][0] = false;
            }
            if (x >= 1) {
                x -= 1;
                passable[i][j][3] = false;
            }
        }
    memset(room, -1, sizeof room);
    memset(roomSize, 0, sizeof roomSize);
    int roomCounter = 0;
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            if (room[i][j] == -1) {
                floodfill(i, j, ++roomCounter);
            }
        }
    int largestRoom = 0;
    pair<int, ii> wallToRemove = mp(INF, mp(-1, -1)); // direction (0 = north, 1 = east...), x, y
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            for (int x = 0; x < 2; x++) {
                int i1 = i+dy[x], j1 = j+dx[x];
                if (i1 < 0 || i1 >= m || j1 < 0 || j1 >= n) continue;
                int a = room[i][j], b = room[i1][j1];
                if (a != b) {
                    int combined = roomSize[a] + roomSize[b];
                    if (combined > largestRoom) {
                        largestRoom = combined;
                        wallToRemove = mp(x, mp(i, j));
                    } else if (combined == largestRoom) {
                        if (wallToRemove.B.B > j) { // farthest to west
                            wallToRemove = mp(x, mp(i, j));
                        } else if (wallToRemove.B.B == j) {
                            if (wallToRemove.B.A < i) { // farthest to south
                                wallToRemove = mp(x, mp(i, j));
                            } else if (wallToRemove.B.A == i) {
                                if (wallToRemove.A == 1) { // choose north before east
                                    wallToRemove = mp(x, mp(i, j));
                                }
                            }
                        }
                    }
                }
            }
        }
    cout << roomCounter << endl;
    cout << biggestOriginalRoom << endl;
    cout << largestRoom << endl;
    cout << wallToRemove.B.A+1 << " " << wallToRemove.B.B+1 << " " << (wallToRemove.A == 0 ? 'N' : 'E') << endl;
    return 0;
}
