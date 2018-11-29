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

int t, n, u, v, forwardsTo[50001];
bool visited[50001];

int dfs(int pos) {
    if (visited[pos]) return 0;
    visited[pos] = true;
    return 1 + dfs(forwardsTo[pos]);
}

int main() {
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> u >> v;
            forwardsTo[u] = v;
        }

        int ans;
        int numSeen = 0;
        memset(visited, false, sizeof visited);
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            memset(visited, false, sizeof visited);
            int result = dfs(i);
            if (result > numSeen) {
                ans = i;
                numSeen = result;
            }
        }

        printf("Case %d: %d\n", caseNum, ans);
    }

    return 0;
}
