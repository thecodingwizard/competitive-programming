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

bool visited[500][500];
int elevation[500][500];
int n;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int dfs(int x, int y, int d) {
    if (visited[x][y]) return 0;
    visited[x][y] = true;
    int ct = 1;
    for (int i = 0; i < 4; i++) {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || abs(elevation[x1][y1] - elevation[x][y]) > d) continue;
        ct += dfs(x1, y1, d);
    }
    return ct;
}

bool can(int d) {
    memset(visited, false, sizeof visited);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            if (visited[i][j]) continue;
            if (dfs(i, j, d) >= (n*n+1)/2) return true;
        }
    return false;
}

int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> elevation[i][j];
    int lo = 0, hi = 1000000, mid, ans;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        if (can(mid)) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid;
        }
    }
    cout << ans << endl;
    return 0;
}
