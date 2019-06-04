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

#define INF 1000000010
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
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    int n; cin >> n;
    int left[n], right[n]; F0R(i, n) cin >> left[i]; F0R(i, n) cin >> right[i];
    int dp[n+10][n+10]; memset(dp, 0, sizeof dp);
    int ans = 0;
    F0R(i, n) {
        F0R(j, n) {
            if (abs(left[i]-right[j]) <= 4) {
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+1);
                ans = max(ans, dp[i][j]+1);
            }
            dp[i][j+1] = max(dp[i][j+1], dp[i][j]);
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
        }
    }
    cout << ans << endl;

    return 0;
}
