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

int dp[(1 << 20)];
int movieStart[20][1000];
int movieDuration[20];
int movieCt[20];

int main() {
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    int n, l; cin >> n >> l;
    for (int i = 0; i < n; i++) {
        int duration, ct; cin >> duration >> ct;
        for (int j = 0; j < ct; j++) {
            int start; cin >> start;
            movieStart[i][j] = start;
        }
        movieCt[i] = ct;
        movieDuration[i] = duration;
    }
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    int ans = INF;
    for (int i = 0; i < (1 << n); i++) {
        if (dp[i] == -1) continue;
        if (dp[i] >= l) {
            ans = min(ans, __builtin_popcount(i));
        }
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;
            int idx = i | (1 << j);
            auto itr = lower_bound(movieStart[j], movieStart[j] + movieCt[j], dp[i]);
            if (*itr > dp[i]) itr--;
            if (itr < movieStart[j]) continue;
            dp[idx] = max(dp[idx], *itr + movieDuration[j]);
        }
    }
    if (ans == INF) {
        cout << "-1" << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}