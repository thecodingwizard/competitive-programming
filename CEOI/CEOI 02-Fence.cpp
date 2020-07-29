/*
 * Basically the same as official editorial I think
 *
 * define dp[i][j][0/1] = number of orderings of the first i numbers, where the
 * first number in the ordering must be j, and the second number is either
 * decreasing/increasing depending on if the third state is 0/1.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main() {
    cin.tie(0); ios::sync_with_stdio(false);
    int k; cin >> k;

    ll dp[21][21][2];

    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == 1) {
                dp[i][j][0] = dp[i][j][1] = 1;
            } else {
                dp[i][j][0] = 0;
                for (int k = 1; k < j; k++) {
                    dp[i][j][0] += dp[i-1][k][1];
                }
                dp[i][j][1] = 0;
                for (int k = j+1; k <= i; k++) {
                    dp[i][j][1] += dp[i-1][k-1][0];
                }
            }
        }
    }

    /*
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k < 2; k++) {
                cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl;
            }
        }
    }
    */

    for (int i = 0; i < k; i++) {
        int n; ll c; cin >> n >> c;

        vector<int> res;

        bool increasing = false;
        for (int x = 1; x <= n; x++) {
            if (dp[n][x][0] + dp[n][x][1] < c) {
                c -= dp[n][x][0] + dp[n][x][1];
                continue;
            }
            res.push_back(x);
            if (dp[n][x][0] < c) {
                c -= dp[n][x][0];
                increasing = true;
            }
            break;
        }
        for (int j = 1; j < n; j++) {
            if (increasing) {
                for (int x = res.back(); x <= n-j; x++) {
                    if (dp[n-j][x][!increasing] < c) {
                        c -= dp[n-j][x][!increasing];
                        continue;
                    }
                    res.push_back(x);
                    break;
                }
            } else {
                for (int x = 1; x <= n-j; x++) {
                    if (dp[n-j][x][!increasing] < c) {
                        c -= dp[n-j][x][!increasing];
                        continue;
                    }
                    res.push_back(x);
                    break;
                }
            }
            increasing = !increasing;
        }
        
        set<int> nums;
        for (int i = 0; i < n; i++) {
            int x = res[i];
            for (int j : nums) {
                if (j <= x) x++;
            }
            nums.insert(x);
            cout << x << " ";
        }
        cout << "\n";
    }

    return 0;
}
