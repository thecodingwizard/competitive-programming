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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector<vector<pair<int, long long>>> adjList;
int n;
long long l;
int p[18][200001];
long long d[200001];
int toSubtract[200001];
long long ans[200001];
int depth[200001];

// Building the parent array, n log n
void dfs(int x, int pa, long long dist) {                  // node, parent of node, depth of node
    d[x] = dist;
    p[0][x] = pa;
    for (int i = 1; i < 18; i++) {
        p[i][x] = p[i - 1][p[i - 1][x]];
    }
    for (auto child : adjList[x]) {
        dfs(child.A, x, dist + child.B);
    }
}

long long dfsAns(int x) {
    long long counter = 1;
    for (auto child : adjList[x]) {
        counter += dfsAns(child.A);
    }
    counter -= toSubtract[x];
    return ans[x] = counter;
}

long long dist(int b, int a) {
    return d[b] - d[a];
}

int main() {
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);

    cin >> n >> l;
    adjList.resize(n+10);
    for (int i = 1; i <= n - 1; i++) {
        int pi; long long li; cin >> pi >> li;
        adjList[pi].push_back(mp(i + 1, li));
    }
    dfs(1, 1, 0);
    memset(toSubtract, 0, sizeof toSubtract);
    for (int i = 2; i <= n; i++) {
        int a = i;
        long long cur = 0;
        for (int j = 17; j >= 0; j--) {
            if (cur + dist(a, p[j][a]) <= l) {
                cur += dist(a, p[j][a]);
                a = p[j][a];
            }
        }
        toSubtract[(a == 1 ? 0 : p[0][a])]++;
    }
    memset(ans, -1, sizeof ans);
    dfsAns(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
