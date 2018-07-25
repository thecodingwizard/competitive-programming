/*
ID: nathan.18
TASK: subset
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
#include <cassert>

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);

    int n; cin >> n;
    int maxSum = n*(n+1)/2;
    if (maxSum%2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    long long dp[n+1][maxSum+1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= maxSum; j++) {
            dp[i][j] = dp[i - 1][j] + (j - 1 >= 0 ? dp[i - 1][j - i] : 0);
        }
    }
    cout << dp[n][maxSum/2]/2 << endl;

    return 0;
}
