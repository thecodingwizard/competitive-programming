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

int k, n, coins[16], cost[100001], ps[100001];

int main() {
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);

    cin >> k >> n;
    for (int i = 0; i < k; i++) cin >> coins[i];
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
        ps[i] = (i > 0 ? ps[i - 1] : 0) + cost[i];
    }
    int dp[(1 << 16)];
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1 << k); i++) {
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) continue;
            int toSearch = coins[j];
            if (dp[i] > 0) {
                toSearch += ps[dp[i] - 1];
            }
            auto it = upper_bound(ps, ps + n, toSearch);
            dp[i | (1 << j)] = max(dp[i | (1 << j)], (int) distance(ps, it));
        }
    }
    int ans = -1;
    for (int i = 0; i < (1 << k); i++) {
        if (dp[i] >= n) {
            int sum = 0;
            for (int j = 0; j < k; j++) {
                if (!(i & (1 << j))) sum += coins[j];
            }
            ans = max(ans, sum);
        }
    }
    cout << ans << endl;
    return 0;
}