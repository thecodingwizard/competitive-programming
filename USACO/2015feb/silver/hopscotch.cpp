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
#include <fstream>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, c, k, grid[751][751];
long long dp[751][751];

int main() {
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);

    cin >> n >> c >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < c; j++) cin >> grid[i][j];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < c; j++) for (int k = i + 1; k < n; k++) for (int l = j + 1; l < c; l++) {
                    if (grid[i][j] == grid[k][l]) continue;
                    dp[k][l] += dp[i][j];
                    dp[k][l] %= 1000000007;
                }
    cout << dp[n - 1][c - 1] << endl;
    return 0;
}