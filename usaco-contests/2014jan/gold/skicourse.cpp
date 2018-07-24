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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define ROUGH 0
#define SMOOTH 1
#define STAMPED 2
int main() {
    freopen("skicourse.in", "r", stdin);
    freopen("skicourse.out", "w", stdout);
    
    int n, m; cin >> n >> m;
    int grid[n][m];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        char c; cin >> c;
        if (c == 'R') grid[i][j] = ROUGH;
        else grid[i][j] = SMOOTH;
    }

    int dpRough[n+1][m+1];
    int dpSmooth[n+1][m+1];
    int dpStamped[n+1][m+1];
    int ans = INF;
    while (true) {
        memset(dpRough, 0, sizeof dpRough);
        memset(dpSmooth, 0, sizeof dpSmooth);
        memset(dpStamped, 0, sizeof dpStamped);
        int best = -1;
        int endX, endY;
        // stamped
        if (grid[0][0] == STAMPED) {
            dpStamped[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            dpStamped[i][j] = min(dpStamped[i - 1][j], min(dpStamped[i][j - 1], dpStamped[i - 1][j - 1])) + 1;
            if (grid[i - 1][j - 1] != STAMPED) dpStamped[i][j] = 0;
        }
        // rough
        if (grid[0][0] == ROUGH) {
            dpRough[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            dpRough[i][j] = min(dpRough[i - 1][j], min(dpRough[i][j - 1], dpRough[i - 1][j - 1])) + 1;
            if (grid[i - 1][j - 1] == SMOOTH) dpRough[i][j] = 0;
            if (best < dpRough[i][j] && dpRough[i][j] != dpStamped[i][j]) {
                best = dpRough[i][j];
                endX = i; endY = j;
            }
        }
        // smooth
        if (grid[0][0] == SMOOTH) {
            dpSmooth[1][1] = 1;
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            dpSmooth[i][j] = min(dpSmooth[i - 1][j], min(dpSmooth[i][j - 1], dpSmooth[i - 1][j - 1])) + 1;
            if (grid[i - 1][j - 1] == ROUGH) dpSmooth[i][j] = 0;
            if (best < dpSmooth[i][j] && dpSmooth[i][j] != dpStamped[i][j]) {
                best = dpSmooth[i][j];
                endX = i; endY = j;
            }
        }

        if (best == -1) break;

        ans = min(ans, best);

        for (int i = endX - best; i < endX; i++) for (int j = endY - best; j < endY; j++) {
            grid[i][j] = STAMPED;
        }
    }

    cout << ans << endl;
    return 0;
}