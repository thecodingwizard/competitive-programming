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

int r, c, m, n;
bool water[101][101];
bool visited[101][101];
bool imLazyToProperlyImplementThisCode[101][101][101][101];
int ways[101][101];

void dfs(int x, int y);

bool notInBounds(int x, int y) {
    return x < 0 || y < 0 || x >= r || y >= c;
}

void run(int x1, int y1, int x2, int y2) {
    if (notInBounds(x1, y1) || notInBounds(x2, y2)) return;
    if (imLazyToProperlyImplementThisCode[x1][y1][x2][y2]) return;
    imLazyToProperlyImplementThisCode[x1][y1][x2][y2] = true;
    if (!water[x1][y1] && !water[x2][y2]) {
        dfs(x2, y2);
        ways[x2][y2]++;
    }
}

void dfs(int x, int y) {
    if (notInBounds(x, y) || visited[x][y]) return;
    visited[x][y] = true;
    // M horizontal, N vertical
    run(x, y, x+m, y+n);
    run(x, y, x-m, y+n);
    run(x, y, x-m, y-n);
    run(x, y, x+m, y-n);
    // M vertical, N horizontal
    run(x, y, x+n, y+m);
    run(x, y, x-n, y+m);
    run(x, y, x-n, y-m);
    run(x, y, x+n, y-m);
}

int main() {
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        memset(water, false, sizeof water);
        memset(ways, 0, sizeof ways);
        memset(visited, false, sizeof visited);
        memset(imLazyToProperlyImplementThisCode, false, sizeof imLazyToProperlyImplementThisCode);
        cin >> r >> c >> n >> m;
        int w;
        cin >> w;
        for (int i = 0; i < w; i++) {
            int x, y;
            cin >> x >> y;
            water[x][y] = true;
        }
        dfs(0, 0);
        int even = 0, odd = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (!visited[i][j]) continue;
                if (ways[i][j] % 2 == 0) even++;
                else odd++;
            }
        }
        cout << "Case " << caseNum << ": " << even << " " << odd << endl;
    }

    return 0;
}
