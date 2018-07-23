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

int n, cows[1000], dp[1000][1000];

int calc(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= n) return INF;
    if (dp[i][j] != -1) return dp[i][j];
    int numCows = n-(abs(j - i)+1);
    if (i <= j) {
        int goLeft = (i == 0 ? INF : calc(i - 1, j) + abs(cows[i] - cows[i - 1])*numCows);
        int goRight = (j+1 < n ? calc(j + 1, i) + abs(cows[i] - cows[j + 1])*numCows : INF);
        return dp[i][j] = min(goLeft, goRight);
    } else {
        int goLeft = j == 0 ? INF : calc(j - 1, i) + abs(cows[i] - cows[j - 1])*numCows;
        int goRight = i == n - 1 ? INF : calc(i+1, j) + abs(cows[i] - cows[i + 1])*numCows;
        return dp[i][j] = min(goLeft, goRight);
    }
}

int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> cows[i];
    sort(cows, cows + n);
    memset(dp, -1, sizeof dp);
    dp[n-1][0] = dp[0][n - 1] = 0;
    for (int i = 0; i < n; i++) {
        if (cows[i] > 0) {
            if (i == 0) cout << calc(i, i) + n*cows[i] << endl;
            else cout << min(calc(i, i) + n*cows[i], calc(i - 1, i - 1) + n*abs(cows[i - 1])) << endl;
            return 0;
        }
    }
    cout << calc(n - 1, n - 1) + n*abs(cows[n - 1]) << endl;
    return 0;
}
