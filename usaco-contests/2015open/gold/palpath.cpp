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

int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);

    int n; cin >> n;
    char grid[n][n];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> grid[i][j];
    long long dp[2][n][n];
    memset(dp, 0, sizeof dp);
    int curDP = 0;
    for (int i = 0; i < n; i++) {
        dp[curDP][i][i] = 1;
    }
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < n; j++) {
            int row1 = j, col1 = i - j - 1;
            if (col1 < 0) continue;
            for (int k = 0; k < n; k++) {
                int row2 = k, col2 = 2*n-i-k-1;
                if (col2 >= n) continue;
                if (grid[row1][col1] != grid[row2][col2]) continue;
                dp[!curDP][row1][row2] += dp[curDP][row1][row2];
                if (row1 + 1 < n) dp[!curDP][row1][row2] += dp[curDP][row1+1][row2];
                if (row2 - 1 >= 0) dp[!curDP][row1][row2] += dp[curDP][row1][row2 - 1];
                if (row1 + 1 < n && row2 - 1 >= 0) dp[!curDP][row1][row2] += dp[curDP][row1+1][row2 - 1];
                dp[!curDP][row1][row2] %= 1000000007;
            }
        }
        for (int x = 0; x < n; x++) for (int y = 0; y < n; y++) dp[curDP][x][y] = 0;
        curDP = !curDP;
    }
    cout << dp[curDP][0][n - 1] << endl;
    return 0;
}