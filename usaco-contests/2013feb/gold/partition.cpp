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

int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    int n, k; cin >> n >> k;
    int cows[n][n], cost[n][n+1]; // cost[i][j] = biggest group between rows i, j given a fixed set of vert fences
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> cows[i][j];
    int ans = INF;
    for (int vertLinesMask = 0; vertLinesMask < (1 << (n-1)); vertLinesMask++) {
        if (__builtin_popcount(vertLinesMask) > k) continue;
        memset(cost, 0, sizeof cost);
        for (int i = 0; i < n; i++) {
            int colSum[n]; memset(colSum, 0, sizeof colSum);
            for (int j = i+1; j <= n; j++) {
                int runningSum = 0;
                for (int l = 0; l < n; l++) {
                    colSum[l] += cows[j-1][l];
                    runningSum += colSum[l];
                    cost[i][j] = max(cost[i][j], runningSum);
                    if (vertLinesMask & (1 << l)) {
                        runningSum = 0;
                    }
                }
            }
        }
        int horizontalLines = k - __builtin_popcount(vertLinesMask);
        int dp[n+1][horizontalLines+1];
        for (int i = 0; i <= n; i++) for (int j = 0; j <= horizontalLines; j++) {
                if (i == n) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = INF;
                }
            }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= horizontalLines; j++) {
                if (j == 0) {
                    dp[i][j] = cost[i][n];
                    continue;
                }
                for (int l = i + 1; l <= n; l++) {
                    dp[i][j] = min(dp[i][j], max(dp[l][j - 1], cost[i][l]));
                }
            }
        }
        ans = min(ans, dp[0][horizontalLines]);
    }
    cout << ans << endl;
    return 0;
}
