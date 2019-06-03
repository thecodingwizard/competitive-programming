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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

int main() {
    int n, m;
    while (cin >> n >> m && (n || m)) {
        int grid[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        int q;
        cin >> q;
        int l, u;
        for (int x = 0; x < q; x++) {
            cin >> l >> u;
            int ans = 0;
            for (int row = 0; row < n; row++) {
                auto col = static_cast<int>(lower_bound(grid[row], grid[row] + m, l) - grid[row]);
                for (int size = ans; size < n; size++) {
                    if (row + size >= n || col + size >= m) break;
                    if (grid[row + size][col + size] > u) break;
                    ans = max(ans, size + 1);
                }
            }
            cout << ans << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}