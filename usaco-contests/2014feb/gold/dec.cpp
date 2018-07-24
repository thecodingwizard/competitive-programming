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
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Bonus {
    int points, additional;
    Bonus(int _pts, int _add) : points(_pts), additional(_add) {}
};

int main() {
    freopen("dec.in", "r", stdin);
    freopen("dec.out", "w", stdout);

    int n, b; cin >> n >> b;
    vector<Bonus> bonuses[n]; for (int i = 0; i < b; i++) {
        int a, pts, add; cin >> a >> pts >> add;
        bonuses[a-1].emplace_back(pts, add);
    }
    int cows[n][n];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> cows[i][j];
    int dp[(1 << n)]; memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1 << n); i++) {
        int event = __builtin_popcount(i);
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;

            int cowScore = cows[j][event];
            int totScore = dp[i] + cowScore;
            int bonusToAdd = 0;
            for (Bonus bonus : bonuses[event]) if (bonus.points <= totScore) bonusToAdd += bonus.additional;
            totScore += bonusToAdd;

            int idx = i | (1 << j);
            dp[idx] = max(dp[idx], totScore);
        }
    }
    cout << dp[(1 << n) - 1] << endl;
    return 0;
}
