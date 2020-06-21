#include <bits/stdc++.h>

using namespace std;

int n; 
int A[400]; 
int B[400][400];

int memo[400];
int dp(int u) {
    if (memo[u] != -1) return memo[u];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i == u) continue;
        if (A[u] + B[u][i] <= A[i]) {
            ans = max(ans, dp(i));
        }
    }
    return memo[u] = ans + 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> B[i][j];
    for (int i = 0; i < n; i++) memo[i] = -1;

    int best = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] < B[0][i]) continue;
        best = max(best, dp(i));
    }
    cout << best << endl;

    return 0;
}
