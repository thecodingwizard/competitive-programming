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
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int t, a, b;
int dp[5000001];

int main() {
    // Also solvable with knapsack: dp[0][X] = if bessie can obtain X units of fullness w/o drinking water
    //                              dp[1][X] = if bessie can obtain X units of fullness after drinking water
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> t >> a >> b;
    dp[0] = 0;

    int best = 0;
    F0R(i, t+1) {
        if (i < a && i >= b) dp[i] = dp[i - b] + b;
        if (i < b && i >= a) dp[i] = dp[i - a] + a;
        if (i >= a && i >= b) dp[i] = max(dp[i - a] + a, dp[i - b] + b);
        if (i != 0) dp[i] = max(dp[i], dp[i - 1]);
    }

    F0R(i, t+1) {
        best = max(best, dp[i]);
        best = max(best, dp[i]/2 + dp[t-dp[i]/2]);
    }

    cout << best << endl;

    return 0;
}
