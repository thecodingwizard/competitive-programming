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
typedef vector<int> vi;

int main() {
    int cases;
    cin >> cases;
    while (cases--) {
        int n;
        cin >> n;
        int sum[n*2+10][n*2+10];
        int A[n+10][n+10];
        for (int i = 0; i <= 2*n; i++) for (int j = 0; j <= 2*n; j++) sum[i][j] = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> A[i][j];
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            sum[i][j] = A[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            sum[i+n][j] = A[i][j] + sum[i + n - 1][j] + sum[i + n][j - 1]  - sum[i + n - 1][j - 1];
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            sum[i][j + n] = A[i][j] + sum[i - 1][j + n] + sum[i][j + n - 1] - sum[i - 1][j + n - 1];
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            sum[i+n][j+n] = A[i][j] + sum[i - 1 + n][j + n] + sum[i + n][j + n - 1] - sum[i + n - 1][j + n - 1];
        }

        int ans = -INF;
        for (int i = 1; i <= 2*n; i++) for (int j = 1; j <= 2*n; j++)
        for (int k = i; k <= 2*n; k++) for (int l = j; l <= 2*n; l++) {
            if (k - i >= n || l - j >= n) continue;
            ans = max(ans, sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1]);
        }
        cout << ans << endl;
    }
    
    return 0;
}