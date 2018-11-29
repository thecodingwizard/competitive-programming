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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define STICKER 1
#define PILLAR 2
#define NORMAL 3
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4
int grid[101][101];
int n, m, s;

int turnLeft(int direction) {
    return direction - 1 == 0 ? 4 : direction - 1;
}
int turnRight(int direction) {
    return direction + 1 == 5 ? 1 : direction + 1;
}
bool safe(int direction, ii robot) {
    if (direction == NORTH) return robot.first - 1 >= 0 && grid[robot.first - 1][robot.second] != PILLAR;
    else if (direction == EAST) return robot.second + 1 < m && grid[robot.first][robot.second + 1] != PILLAR;
    else if (direction == SOUTH) return robot.first + 1 < n && grid[robot.first + 1][robot.second] != PILLAR;
    else return robot.second - 1 >= 0 && grid[robot.first][robot.second - 1] != PILLAR;
}

int main() {
    while (cin >> n >> m >> s && (n || m || s)) {
        memset(grid, -1, sizeof grid);
        int orientation;
        ii robot;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c;
                cin >> c;
                if (c == '*') grid[i][j] = STICKER;
                else if (c == '.') grid[i][j] = NORMAL;
                else if (c == '#') grid[i][j] = PILLAR;
                else if (c == 'N') {
                    orientation = NORTH;
                    robot.first = i; robot.second = j;
                } else if (c == 'S') {
                    orientation = SOUTH;
                    robot.first = i; robot.second = j;
                } else if (c == 'L') {
                    orientation = EAST;
                    robot.first = i; robot.second = j;
                } else if (c == 'O') {
                    orientation = WEST;
                    robot.first = i; robot.second = j;
                }
            }
        }
        int sticker = 0;
        while (s--) {
            char c;
            cin >> c;
            if (c == 'D') orientation = turnRight(orientation);
            else if (c == 'E') orientation = turnLeft(orientation);
            else {
                if (orientation == NORTH && safe(orientation, robot)) {
                    robot.first -= 1;
                }
                if (orientation == EAST && safe(orientation, robot)) {
                    robot.second += 1;
                }
                if (orientation == SOUTH && safe(orientation, robot)) {
                    robot.first += 1;
                }
                if (orientation == WEST && safe(orientation, robot)) {
                    robot.second -= 1;
                }
                if (grid[robot.first][robot.second] == STICKER) {
                    sticker++;
                    grid[robot.first][robot.second] = NORMAL;
                }
            }
        }
        cout << sticker << endl;
    }

    return 0;
}
