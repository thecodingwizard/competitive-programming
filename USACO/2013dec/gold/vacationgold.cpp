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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vii adjList[20001];
vii reverseAdjList[20001];
int distTo[20001][201], distFrom[20001][201];

int main() {
    freopen("vacationgold.in", "r", stdin);
    freopen("vacationgold.out", "w", stdout);

    int n, m, k, q;
    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        adjList[a].push_back(mp(b, w));
        reverseAdjList[b].push_back(mp(a, w));
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= k; j++) {
        distTo[i][j] = distFrom[i][j] = INF;
    }
    for (int i = 1; i <= k; i++) {
        int hub; cin >> hub;
        // dijkstra
        distTo[hub][i] = 0;
        priority_queue<ii, vii, greater<ii>> pq; pq.push(mp(0, hub));
        while (!pq.empty()) {
            ii next = pq.top(); pq.pop();
            int d = next.A, node = next.B;
            if (d > distTo[node][i]) continue;
            for (ii child : adjList[node]) {
                if (distTo[node][i] + child.B < distTo[child.A][i]) {
                    distTo[child.A][i] = distTo[node][i] + child.B;
                    pq.push(mp(distTo[child.A][i], child.A));
                }
            }
        }

        distFrom[hub][i] = 0;
        pq.push(mp(0, hub));
        while (!pq.empty()) {
            ii next = pq.top(); pq.pop();
            int d = next.A, node = next.B;
            if (d > distFrom[node][i]) continue;
            for (ii child : reverseAdjList[node]) {
                if (distFrom[node][i] + child.B < distFrom[child.A][i]) {
                    distFrom[child.A][i] = distFrom[node][i] + child.B;
                    pq.push(mp(distFrom[child.A][i], child.A));
                }
            }
        }
    }
    long long success = 0, total = 0;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        int minCost = INF;

        for (int j = 1; j <= k; j++) {
            if (distTo[b][j] != INF && distFrom[a][j] != INF) {
                minCost = min(minCost, distTo[b][j] + distFrom[a][j]);
            }
        }

        if (minCost == INF) continue;
        else {
            success++;
            total += minCost;
        }
    }
    cout << success << endl << total << endl;
    return 0;
}
