/*
Roadblock
=========

Every morning, FJ wakes up and walks across the farm from his house to the
barn.  The farm is a collection of N fields (1 <= N <= 250) connected by M
bidirectional pathways (1 <= M <= 25,000), each with an associated length.
FJ's house is in field 1, and the barn is in field N.  No pair of fields is
joined by multiple redundant pathways, and it is possible to travel between
any pair of fields in the farm by walking along an appropriate sequence of
pathways.  When traveling from one field to another, FJ always selects a
route consisting of a sequence of pathways having minimum total length.

Farmer John's cows, up to no good as always, have decided to interfere with
his morning routine.  They plan to build a pile of hay bales on exactly one
of the M pathways on the farm, doubling its length.  The cows wish to
select a pathway to block so that they maximize the increase in FJ's
distance from the house to the barn.  Please help the cows determine
by how much they can lengthen FJ's route.

PROBLEM NAME: rblock

INPUT FORMAT:

* Line 1: Two space-separated integers, N and M.

* Lines 2..1+M: Line j+1 describes the jth bidirectional pathway in
        terms of three space-separated integers: A_j B_j L_j, where
        A_j and B_j are indices in the range 1..N indicating the
        fields joined by the pathway, and L_j is the length of the
        pathway (in the range 1...1,000,000).

SAMPLE INPUT:

5 7
2 1 5
1 3 1
3 2 8
3 5 7
3 4 3
2 4 7
4 5 2

INPUT DETAILS:

There are 5 fields and 7 pathways.  Currently, the shortest path from the
house (field 1) to the barn (field 5) is 1-3-4-5 of total length 1+3+2=6.

OUTPUT FORMAT:

* Line 1: The maximum possible increase in the total length of FJ's
        shortest route made possible by doubling the length of a
        single pathway.

SAMPLE OUTPUT:

2

OUTPUT DETAILS:

If the cows double the length of the pathway from field 3 to field 4
(increasing its length from 3 to 6), then FJ's shortest route is now 1-3-5,
of total length 1+7=8, larger by two than the previous shortest route length.
*/

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
