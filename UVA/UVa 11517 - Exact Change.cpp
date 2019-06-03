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

int n, c, p;
int memo[10001][101], memo2[10001][101], coinValue[101];

int dp(int amt, int coin) {
    if (amt <= 0) return -amt;
    if (coin == n) return INF;
    if (memo[amt][coin] != -1) return memo[amt][coin];
    return memo[amt][coin] = min(dp(amt, coin+1), dp(amt-coinValue[coin], coin+1));
}

int dp2(int value, int coin) {
    if (value == 0) return 0;
    if (value < 0 || coin == n) return INF;
    if (memo2[value][coin] != -1) return memo2[value][coin];
    int ans = min(dp2(value, coin+1), dp2(value-coinValue[coin], coin+1)+1);
    return memo2[value][coin] = ans;
}

int main() {
    cin >> c;
    while (c--) {
        cin >> p >> n;
        memset(memo, -1, sizeof memo);
        memset(memo2, -1, sizeof memo2);
        for (int i = 0; i < n; i++) cin >> coinValue[i];
        int amt = p + dp(p, 0);
        int coins = dp2(amt, 0);
        cout << amt << " " << coins << endl;
    }
    return 0;
}
