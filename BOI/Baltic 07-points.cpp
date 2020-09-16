/*
 * Matrix exponentiation problem, same solution as editorial
 *
 * Come up with O(n) DP then extend it to use matrix exponentiation
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000000
#define ll long long

struct Matrix {
    ll a[6][6]={0};

    Matrix operator*(const Matrix &other) {
        Matrix ans;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                for (int k = 0; k < 6; k++) {
                    ans.a[i][j] += a[i][k]*other.a[k][j];
                    ans.a[i][j] %= mod;
                }
            }
        }
        return ans;
    }
};

int main() {
    int n; cin >> n;
    
    ll A[6] = {1,1,1,1,1,4};
    ll mult[][6] = {
        {0,0,0,0,0,1},
        {0,0,0,1,1,0},
        {0,0,0,0,0,1},
        {1,1,1,1,1,2},
        {1,1,1,1,1,2},
        {1,1,1,1,1,2}
    };

    // define B = A*mult^(n-3)
    // answer is B[0]*2 + B[3] + B[4] + B[5]

    int p = n-4;
    Matrix multiplier;
    Matrix cur; for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) cur.a[i][j] = multiplier.a[i][j] = mult[i][j];

    while (p > 0) {
        if (p&1) {
            cur = cur*multiplier;
        }
        multiplier = multiplier * multiplier;
        p /= 2;
    }

    ll B[6] = {0};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            B[i] += (p==-1?j==i:cur.a[j][i])*A[j];
        }
    }

    cout << (B[0]+B[0]+B[3]+B[4]+B[5])%mod << endl;

    return 0;
}

/* O(n) DP Version:
int main() {
    int n; cin >> n;
    assert(n <= 100000);

    ll dp[2][6] = {
        {0},
        {1,1,1,1,1,4},
    };
    for (int i = 1; i < n-2; i++) {
        int x = (i+1)%2, y = i%2;
        for (int j = 0; j < 6; j++) dp[x][j] = 0;
        dp[x][0] += dp[y][3] + dp[y][4] + dp[y][5];
        dp[x][1] += dp[y][3] + dp[y][4] + dp[y][5];
        dp[x][2] += dp[y][3] + dp[y][4] + dp[y][5];
        dp[x][3] += dp[y][1] + dp[y][3] + dp[y][4] + dp[y][5];
        dp[x][4] += dp[y][1] + dp[y][3] + dp[y][4] + dp[y][5];
        dp[x][5] += dp[y][0] + dp[y][2] + 2*dp[y][3] + 2*dp[y][4] + 2*dp[y][5];
        for (int j = 0; j < 6; j++) dp[x][j] %= mod;
        for (int j = 0; j < 6; j++) cerr << dp[x][j] << " ";
        cerr << endl;
    }

    int a = (n-2)%2;
    cout << (dp[a][1]*2+dp[a][3]+dp[a][4]+dp[a][5])%mod << endl;

    return 0;
}
*/
