#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <assert.h>

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
    int n; cin >> n;
    int values[n]; for (int i = 0; i < n; i++) cin >> values[i];
    long long dp[n][20001];
    memset(dp, 0, sizeof dp);
    dp[0][10000-values[0]]=1,dp[0][10000+values[0]]=1,dp[0][10000] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= 20000; j++) {
            if (j == 10000) dp[i][j]++;
            if (j-values[i]>=0) dp[i][j] += dp[i - 1][j - values[i]];
            if (j+values[i]<=20000) dp[i][j] += dp[i - 1][j + values[i]];
            dp[i][j] %= 1000000007;
        }
    }
    long long tot = -n; // empty frame counted once for each value
    for (int i = 0; i < n; i++) tot = (tot + dp[i][10000]) % 1000000007;
    cout << tot << endl;
    return 0;
}