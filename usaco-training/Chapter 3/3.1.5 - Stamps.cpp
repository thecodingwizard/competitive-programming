/*
ID: nathan.18
TASK: stamps
LANG: C++11
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

int dp[10000*201];
int main() {
    freopen("stamps.in", "r", stdin);
    freopen("stamps.out", "w", stdout);

    int k, n; cin >> k >> n;
    int coins[n]; F0R(i, n) cin >> coins[i];
    F0R(i, 10000*201) dp[i] = INF;
    dp[0] = 0;
    int ans = 0;
    FOR(i, 1, 10000*201) {
        F0R(j, n) if (i - coins[j] >= 0) dp[i] = min(dp[i], dp[i - coins[j]]+1);
        if (dp[i] != 0 && dp[i] <= k) ans++;
        else break;
    }
    cout << ans << endl;

    return 0;
}
