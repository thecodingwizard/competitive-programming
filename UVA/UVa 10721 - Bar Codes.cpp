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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, k, m;
long long memo[51][51];

long long dp(int pos, int barsLeft) {
    if (pos == n && barsLeft == 0) return 1;
    if (memo[pos][barsLeft] != -1) return memo[pos][barsLeft];

    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        if (pos + i > n) break;
        ans += dp(pos + i, barsLeft - 1);
    }

    return memo[pos][barsLeft] = ans;
}

int main() {
    while (cin >> n >> k >> m) {
        memset(memo, -1, sizeof memo);
        cout << dp(0, k) << endl;
    }
    return 0;
}
