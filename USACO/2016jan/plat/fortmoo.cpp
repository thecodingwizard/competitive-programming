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
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int grid[210][210];

int sum(int x1, int y1, int x2, int y2) {
    return grid[x2+1][y2+1] - grid[x1][y2+1] - grid[x2+1][y1] + grid[x1][y1];
}

int main() {
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);

    int n, m; cin >> n >> m;
    SET2D(grid, 0, 210, 210);
    F0R(i, n) F0R(j, m) {
        char c; cin >> c;
        grid[i+1][j+1] = grid[i+1][j] + grid[i][j+1] - grid[i][j];
        if (c == 'X') {
            grid[i+1][j+1]++;
        }
    }

    int best = 0;
    F0R(i, n) {
        FOR(j, i, n) {
            int left = -1;
            F0R(k, m) {
                bool canUse = sum(i, k, j, k) == 0;
                if (canUse) {
                    best = max(best, j-i+1);
                }
                if (left != -1 && canUse) {
                    best = max(best, (j-i+1)*(k-left+1));
                }
                if (sum(i, k, i, k) != 0 || sum(j, k, j, k) != 0) left = -1;
                if (canUse && left == -1) left = k;
            }
        }
    }
    cout << best << endl;

    return 0;
}
