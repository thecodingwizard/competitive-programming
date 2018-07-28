/*
ID: nathan.18
TASK: money
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

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

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

int main() {
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    int v, n; cin >> v >> n;
    int coins[v+1]; F0R(i, v) cin >> coins[i+1];
    long long dp[v+10][n+10]; memset(dp, 0LL, sizeof dp);

    F0R(i, v+1) dp[i][0] = 1;

    FOR(i, 1, v+1) FOR(j, 1, n+1) F0R(k, (j/coins[i])+1) {
                dp[i][j] += dp[i - 1][j - k*coins[i]];
            }

    cout << dp[v][n] << endl;

    return 0;
}
