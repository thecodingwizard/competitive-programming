/*
 * Same solution as editorial, use PIE + combinatorics
 *
 * I tried the O(bn) dp solution, but it got TLE on the last two test cases
 * (the time limit of the judge is only 0.10s)
 */

#include <bits/stdc++.h>
using namespace std;

int n, a, b; 
int A[10]; 

// returns how many ways there are to assign tgt elements into n buckets
int pick(int tgt, int n) {
    int a = tgt+n, b = n;
    // basically compute a choose b
    vector<int> numbers;
    for (int i = 0; i < b; i++) {
        numbers.push_back(a-i);
    }
    for (int i = b; i > 0; i--) {
        int toDivide = i;
        for (int &x : numbers) {
            for (int y = 2; y <= toDivide; y++) {
                while (toDivide % y == 0 && x % y == 0) {
                    toDivide /= y;
                    x /= y;
                }
            }
        }
    }
    int ans = 1;
    for (int x : numbers) {
        ans = ans*(x%2004)%2004;
    }
    return ans;
}

int solve(int x) {
    if (x == 0) return 1;

    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        int sign = __builtin_popcount(i) % 2 == 1 ? -1 : 1;
        int tgt = x;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                tgt -= A[j]+1;
            }
        }
        if (tgt >= 0) {
            ans = ((ans + sign*pick(tgt, n)) % 2004 + 2004) % 2004;
        }
    }
    return ans;
}

int main() {
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << (solve(b) - solve(a-1) + 2004) % 2004 << endl;

    return 0;
}

/* TLE, O(bn) dp

int A[11]; 
int16_t dp[2][10000001];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    int n, a, b; cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) cin >> A[i];

    for (int i = 0; i <= b; i++) dp[0][i] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= b; j++) {
            dp[i&1][j] = dp[~i&1][j] - (j-A[i]-1>=0?dp[~i&1][j-A[i]-1]:0) + (j==0?0:dp[i&1][j-1]);
            if (dp[i&1][j] < 0) dp[i&1][j] += 2004;
            else if (dp[i&1][j] >= 2004) dp[i&1][j] -= 2004;
        }
    }

    cout << (dp[n&1][b]-(a-1==-1?0:dp[n&1][a-1])+2004)%2004 << endl;

    return 0;
}

*/
