#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

int main() {
    int n, l; cin >> n >> l;
    int A[n]; for (int i = 0; i < n; i++) cin >> A[i];
    int D = (l)/(n-1);

    int dp[l+1][2];
    for (int i = 0; i < n; i++) {
        int prv = (i-1)%2;
        for (int j = D*i; j <= (D+1)*i; j++) {
            if (j>l) continue;
            if (i == 0) dp[j][i%2] = abs(A[i]-j);
            else dp[j][i%2] = min(j-D>=D*(i-1)&&j-D<=(D+1)*(i-1) ? dp[j-D][prv] : inf, j-D-1>=D*(i-1)&&j-D-1<=(D+1)*(i-1) ? dp[j-D-1][prv] : inf) + abs(A[i]-j);
        }
    }
    cout << dp[l][(n-1)%2] << endl;

    return 0;
}
