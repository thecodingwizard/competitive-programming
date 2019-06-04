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
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n;
int dp[101][101];
int sequence[101];

int solve(int day, int breakins) {
    if (day == n && breakins == 0) return 0;
    if (n-day < breakins) return INF;
    if (dp[day][breakins] != -1) return dp[day][breakins];
    int ans = INF;
    int diff = 0;
    F0R(i, n-day) {
        if (sequence[day+i] != i) diff++;
        ans = min(ans, solve(day+i+1, breakins-1) + diff);
    }
    return dp[day][breakins] = ans;
}

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    cin >> n;
    F0R(i, n) cin >> sequence[i];

    F0R(i, 101) F0R(j, 101) dp[i][j] = -1;

    FOR(i, 1, n+1) {
        cout << solve(0, i) << endl;
    }

    return 0;
}
