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
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1100000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int grid[801][801];
bool isValid[801][801];

int main() {
    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);

    int n, k; cin >> n >> k;
    memset(grid, 0, sizeof grid);
    memset(isValid, false, sizeof isValid);
    F0R(i, n) F0R(j, n) {
            cin >> grid[i+j][n-i+j-1];
            isValid[i+j][n-i+j-1] = true;
        }
    int ans = 0;
    for (int i = 0; i < 2*n; i++) {
        int sum = 0;
        for (int a = max(i - k, 0); a <= min(i+k, 2*n); a++) for (int b = 0; b <= min(k, 2*n); b++) {
                sum += grid[a][b];
            }
        if (isValid[i][0]) ans = max(ans, sum);
        for (int j = 1; j+k < 2*n; j++) {
            for (int a = max(i-k, 0); a <= min(i+k, 2*n); a++) {
                if (j - k - 1 >= 0) sum -= grid[a][j-k-1];
                sum += grid[a][j+k];
            }
            if (isValid[i][j]) ans = max(ans, sum);
        }
    }
    cout << ans << endl;

    return 0;
}
