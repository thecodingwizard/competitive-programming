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
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int cost[251][251];
int dist[251];
int parent[251];
int n, m;

int dijkstra() {
    for (int i = 0; i <= n; i++) dist[i] = INF;
    dist[1] = 0; parent[1] = -1;
    priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push(mp(0, 1));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int distance = front.A, node = front.B;
        if (distance > dist[node]) continue;
        for (int i = 1; i <= n; i++) {
            if (dist[node] + cost[node][i] < dist[i]) {
                dist[i] = dist[node] + cost[node][i];
                parent[i] = node;
                pq.push(mp(dist[i], i));
            }
        }
    }
    return dist[n];
}

int main() {
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i <= 250; i++) for (int j = 0; j <= 250; j++) cost[i][j] = INF;
    for (int i = 0; i < m; i++) {
        int a, b, l; cin >> a >> b >> l;
        cost[a][b] = l; cost[b][a] = l;
    }

    dijkstra();

    int originalDist = dist[n];
    vector<int> nodesOnPath;
    int curNode = n;
    while (curNode != -1) {
        nodesOnPath.push_back(curNode);
        curNode = parent[curNode];
    }
    int ans = -1;
    while (nodesOnPath.size() > 1) {
        int n1 = nodesOnPath.back(); nodesOnPath.pop_back();
        int n2 = nodesOnPath.back();
        cost[n1][n2] = 2*cost[n1][n2];
        cost[n2][n1] = 2*cost[n2][n1];

        ans = max(ans, dijkstra() - originalDist);

        cost[n1][n2] = cost[n2][n1] = cost[n1][n2]/2;
    }
    cout << ans;
    return 0;
}
