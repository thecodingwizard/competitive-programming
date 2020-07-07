/*
 * Note that the swaps can be thought of as a binary search tree.
 *
 * Define dp[i][j] = min subtree of i assuming the value of i is j.
 *
 * See: https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/BtOI/16-Swap.cpp
 * https://github.com/stefdasca/CompetitiveProgramming/blob/master/BalticOI/Baltic%2016-Swap.cpp
 *
 * Note that time limit + memory is *extremely* tight... :(
 */

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
 
using namespace std;
 
const int maxn = 200000;
 
int n, A[maxn+10];
vector<int> dp[maxn+10][36], tmp1, tmp2;
bool v[maxn+10][40];
 
void merge(vector<int> &res, vector<int> &L, vector<int> &R) {
    for (int len = 1, i = 0, j = 0; i < L.size() || j < R.size(); i += len, j += len, len *= 2) {
        for (int k = 0; k < len && i+k<L.size(); k++) res.push_back(L[i+k]);
        for (int k = 0; k < len && i+k<R.size(); k++) res.push_back(R[i+k]);
    }
}
 
int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n; for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) for (int j = 0; j < 36; j++) v[i][j] = false;
    v[1][0] = 1;
    for (int i = 1; 2*i+1 <= n; i++) {
        for (int j = 0; j < 36; j++) {
            if (!v[i][j]) continue;
            int idx = i>>(j/2);
            if (j&1) idx *= 2;
 
            // if left is smallest
            if (A[i<<1]<A[idx]&&A[i<<1]<A[i<<1^1]) {
                v[i<<1^1][0] = v[i<<1][j+2] = true;
            } else if (A[i<<1^1]<A[idx]&&A[i<<1^1]<A[i<<1]) {
                v[i<<1][0] = v[i<<1^1][3] = v[i<<1][j+2] = v[i<<1^1][j+2] = true;
            } else {
                v[i<<1][0] = v[i<<1^1][0] = true;
            }
        }
    }
    for (int i = n; i; i--) {
        int l = i<<1, r = i<<1^1;
        for (int j = 0; j < 36; j++) {
            if (!v[i][j]) continue;
            int idx = i>>(j/2);
            if (j&1) idx *= 2;
            int cur = A[idx];
 
            if (l > n && r > n) {
                dp[i][j] = {cur};
            } else if (r > n) {
                dp[i][j] = {min(A[l],cur),max(A[l],cur)};
            } else {
                int L = A[l], R = A[r];
                if (R < cur && R < L) {
                    tmp1 = {R}, tmp2 = {R};
                    // swap right
                    merge(tmp1, dp[l][0], dp[r][j+2]);
                    // swap both
                    merge(tmp2, dp[l][j+2], dp[r][3]);
                    dp[i][j] = min(tmp1, tmp2);
                } else {
                    dp[i][j]={cur<L?cur:L};
                    // no swap / swap left
                    merge(dp[i][j], dp[l][cur<L?0:j+2], dp[r][0]);
                }
            }
        }
 
        if ((i<<1^1)<=n) {
            for (int k = 0; k < 2; k++)
            for (int j = 0; j < 36; j++) if (v[i<<1|k][j]) vector<int>().swap(dp[i<<1|k][j]);
        }
    }
    for (int v : dp[1][0]) cout << v << " ";
    return 0;
}
