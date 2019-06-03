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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int x, y, n;
int dist[11][11], coords[11][2], memo[11][4096];

int tsp(int pos, int mask) {
    if (mask == pow(2, n+1) - 1) return dist[pos][0];
    if (memo[pos][mask] != -1) return memo[pos][mask];
    int shortest = INF;
    for (int i = 0; i <= n; i++) {
        if (i == pos || mask & (1 << i)) continue;
        shortest = min(shortest, dist[pos][i] + tsp(i, mask | (1 << i)));
    }
    return memo[pos][mask] = shortest;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> x >> y >> coords[0][0] >> coords[0][1] >> n;
        memset(memo, -1, sizeof(memo));
        for (int i = 1; i <= n; i++) {
            cin >> coords[i][0] >> coords[i][1];
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dist[i][j] = abs(coords[i][0] - coords[j][0]) + abs(coords[i][1] - coords[j][1]);
            }
        }

        cout << "The shortest path has length " << tsp(0, 1) << endl;
    }
    return 0;
}
