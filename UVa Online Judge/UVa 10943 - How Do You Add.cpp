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

int n, k;
int memo[101][101];

int dp(int numsRemaining, int sum) {
    if (numsRemaining == 0 && sum == n) return 1;
    if (numsRemaining == 0) return 0;
    if (memo[numsRemaining][sum] != -1) return memo[numsRemaining][sum];

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (sum + i > n) break;
        ans = (ans + dp(numsRemaining - 1, sum + i)) % 1000000;
    }

    return memo[numsRemaining][sum] = ans;
}

int main() {
    while (cin >> n >> k && (n || k)) {
        memset(memo, -1, sizeof memo);
        cout << dp(k, 0) << endl;
    }
    return 0;
}
