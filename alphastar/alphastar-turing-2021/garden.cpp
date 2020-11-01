#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int n, m; 

/*
map<pair<int, ii>, int> memo[1000000];
int dp(int i, int cur, int small, int large) {
    if (large - small > 2) return 0;
    assert(0 <= cur && cur <= 4);
    if (i == n) return 1;
    if (memo[i].count(mp(cur, mp(small, large)))) return memo[i][mp(cur, mp(small, large))];
    return memo[i][mp(cur, mp(small, large))] = (dp(i+1, cur-1, min(small, cur-1), max(large, cur-1)) + dp(i+1, cur+1, min(small, cur+1), max(large, cur+1))) % m;
}
*/

int dp[2][5][5][5];

int main() {
    cin >> n >> m;

    string s; cin >> s;
    int ans = 1;
    int cur = 2, small = 2, large = 2;
    pair<int, ii> values[n];
    for (int i = 0; i < n; i++) {
        values[i] = mp(cur, mp(small, large));
        if (s[i] == 'L') cur++;
        else cur--;
        small = min(cur, small);
        large = max(cur, large);
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (j <= i && k >= i && k - j <= 2) {
                    dp[n%2][i][j][k] = 1;
                }
            }
        }
    }
    for (int i = n-1; i>=0; i--) {
        // todo somehow calculate dp
        for (int i2 = 0; i2 < 5; i2++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    if (j <= i2 && k >= i2 && k - j <= 2) {
                        dp[i%2][i2][j][k] = ((i2+1<5?dp[(i+1)%2][i2+1][j][max(k,i2+1)]:0) + (i2-1>=0?dp[(i+1)%2][i2-1][min(j,i2-1)][k]:0))%m;
                    } else {
                        dp[i%2][i2][j][k] = 0;
                    }
                }
            }
        }
        
        cur = values[i].f, small = values[i].s.f, large = values[i].s.s;
        if (s[i] == 'P') {
            // if this were l...
            if (cur+1<5) ans += dp[(i+1)%2][cur+1][min(small, cur+1)][max(large, cur+1)];
            //cout << ans << endl;
        }
        ans %= m;

    }
    cout << ans << endl;

    return 0;
}
