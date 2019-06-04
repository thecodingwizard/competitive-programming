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

struct Cow {
    long long height, weight, strength;
};

long long dp[(1 << 20)], weight[(1 << 20)], height[(1 << 20)];
int main() {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    int n, h;
    cin >> n >> h;
    Cow cows[n];
    for (int i = 0; i < n; i++) cin >> cows[i].height >> cows[i].weight >> cows[i].strength;
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = -INF;
        int w = 0, h = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) w += cows[j].weight;
            if (i & (1 << j)) h += cows[j].height;
        }
        weight[i] = w;
        height[i] = h;
    }
    long long best = -1;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;
            int idx = i | (1 << j);
            if (dp[i] == -INF) dp[i] = INF;
            dp[idx] = max(dp[idx], max(min(dp[i] - cows[j].weight, cows[j].strength), min(cows[j].strength - weight[i], dp[i])));
            if (height[idx] >= h) best = max(best, dp[idx]);
        }
    }
    if (best == -1) cout << "Mark is too tall" << endl;
    else cout << best << endl;
    return 0;
}