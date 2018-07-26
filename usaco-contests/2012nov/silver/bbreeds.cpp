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

int balance[1001];
int dp[1001][1001];

int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);

    string s;
    cin >> s;
    int n = s.length();

    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') counter++;
        else counter--;
        balance[i] = counter;
    }

    memset(dp, 0, sizeof dp);
    dp[0][0] = dp[0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;
            if (i == 0 && j == 1) continue;
            if (s[i] == '(') {
                dp[i][j] = ((i > 0 && j > 0 ? dp[i - 1][j - 1] : 0) + (i > 0 ? dp[i - 1][j] : 0)) % 2012;
            } else {
                int gBal = balance[i] - j + 1;
                dp[i][j] = ((gBal > 0 ? dp[i - 1][j] : 0) + dp[i - 1][j + 1]) % 2012;
            }
        }
    }

    cout << dp[n - 1][0];

    return 0;
}
