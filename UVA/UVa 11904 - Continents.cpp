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

int dr[] = {1,0,-1,0};
int dc[] = {0,1,0,-1};
int M, N;
bool water[21][21];
char grid[21][21];

int floodfill(int x, int y) {
    if (x < 0 || x >= M) return 0;
    if (y < 0) y = N - 1;
    if (y >= N) y = 0;
    if (water[x][y]) return 0;
    int ans = 1;
    water[x][y] = true; // do not visit same cell twice
    for (int d = 0; d < 4; d++) ans += floodfill(x + dr[d], y + dc[d]);
    return ans;
}

int main() {
    while (cin >> M >> N) {
        char waterGuess = 0;
        for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) {
                char c; cin >> c;
                if (waterGuess == 0) waterGuess = c;
                water[i][j] = c == waterGuess;
                grid[i][j] = c;
            }

        int x, y;
        cin >> x >> y;
        if (waterGuess == grid[x][y]) {
            for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) water[i][j] = !water[i][j];
        }
        floodfill(x, y);

        int ans = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                ans = max(ans, floodfill(i, j));
            }
        }

        cout << ans << endl;
    }


    return 0;
}
