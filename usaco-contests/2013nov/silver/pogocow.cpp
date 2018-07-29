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
    freopen("pogocow.in", "r", stdin);
    freopen("pogocow.out", "w", stdout);

    int n; cin >> n;
    ii cows[n]; F0R(i, n) cin >> cows[i].A >> cows[i].B;
    sort(cows, cows+n);
    int dp[n][n];

    int ans = 0;
    F0R(x, 2) {
        memset(dp, 0, sizeof dp);
        FORd(i, 0, n) {
            int nextCow = i + 1;
            F0Rd(j, i + 1) {
                dp[i][j] = cows[i].B;
                int dist = abs(cows[i].A - cows[j].A);
                while (nextCow < n && abs(cows[nextCow].A - cows[i].A) < dist) {
                    nextCow++;
                }
                if (nextCow != n) {
                    dp[i][j] = max(dp[i][j], cows[i].B + dp[nextCow][i]);
                }
                if (i != n - 1) dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                ans = max(ans, dp[i][j]);
            }
        }
        reverse(cows, cows+n);
    }
    cout << ans << endl;

    return 0;
}
