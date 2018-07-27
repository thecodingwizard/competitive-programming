/*
ID: nathan.18
TASK: nocows
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
    freopen("nocows.in", "r", stdin);
    freopen("nocows.out", "w", stdout);

    int n, k; cin >> n >> k;
    int dp[k+1][n+1]; memset(dp, 0, sizeof dp);

    dp[1][1] = 1;
    FOR(i, 2, k+1) {
        FOR(j, 2*i-1, n+1) {
            FOR(nodes, 1, j-1) {
                FOR(level, 1, i) {
                    if (level != i - 1) dp[i][j] += 2 * dp[level][j - nodes - 1] * dp[i - 1][nodes];
                    else dp[i][j] += dp[level][j - nodes - 1] * dp[i - 1][nodes];
                    dp[i][j] %= 9901;
                }
            }
        }
    }

    cout << dp[k][n] << endl;

    return 0;
}
