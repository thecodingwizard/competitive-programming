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

int n, m, S;
int memo[301][301], coinValue1[301], coinValue2[301];

int dp(int val1, int val2) {
    if (sqrt(val1*val1 + val2*val2) == S) return 0;
    if (sqrt(val1*val1 + val2*val2) > S) return INF;
    if (memo[val1][val2] != -1) return memo[val1][val2];
    int ans = INF;
    for (int i = 0; i < m; i++) {
        ans = min(dp(val1 + coinValue1[i], val2 + coinValue2[i]), ans);
    }
    return memo[val1][val2] = ans + 1;
}

int main() {
    cin >> n;
    while (n--) {
        cin >> m >> S;
        memset(memo, -1, sizeof memo);
        for (int i = 0; i < m; i++) {
            cin >> coinValue1[i] >> coinValue2[i];
        }
        int ans = dp(0, 0);
        if (ans == INF + 1) cout << "not possible" << endl;
        else cout << ans << endl;
    }
    return 0;
}
