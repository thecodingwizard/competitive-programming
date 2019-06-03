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
    for (int caseNum = 1; caseNum <= cases; caseNum++) {
        int n, m, budget;
        cin >> n >> m >> budget;
        int sum[n+10][m+10];
        for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) sum[i][j] = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            cin >> sum[i][j];
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
        int area = 0, cost = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
        for (int k = i; k <= n; k++) for (int l = j; l <= m; l++) {
            int total = sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1];
            if (total > budget) continue;
            int area2 = (l - j + 1) * (k - i + 1);
            if (area2 > area || (area2 == area && total < cost)) {
                area = area2;
                cost = total;
            }
        }
        cout << "Case #" << caseNum << ": " << area << " " << cost << endl;
    }
    
    return 0;
}