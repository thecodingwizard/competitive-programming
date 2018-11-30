/*
Distance
========

You are given a tree with N nodes and N-1 unweighted edges and
you need to answer Q queries. Each query consists of two integers
A and B. For each query you need to output the distance between
node A and B in a single line.

PROBLEM NAME: distance

INPUT FORMAT:

* Line 1: Two space-separated integers: N and Q

* Lines 2..N: Each line represents an edge with two
	space-separated integers: A and B. It means there is
	an edge connecting two nodes A and B.

* Lines N+1..N+Q: Each line represents an operation with two
        space-separated integers: A and B

SAMPLE INPUT (file distance.in):

7 3
1 2
1 3
2 4
2 5
3 6
3 7
4 6
3 5
5 1

OUTPUT FORMAT:

* Lines 1..Q: For each query, print the distance
        as an integer on a single line.

SAMPLE OUTPUT (file distance.out):

4
3
2
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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int depth[100001], dist[100001], p[20][100001];
vector<vi> adjList;
bool visited[100001];

// Building the parent array, n log n
void dfs(int x, int pa, int d) {                  // node, parent of node, depth of node
    if (visited[x]) return;
    visited[x] = true;
    depth[x] = dist[x] = d;
    p[0][x] = pa;
    for (int i = 1; i <= 17; i++) {
        p[i][x] = p[i - 1][p[i - 1][x]];
    }
    for (int child : adjList[x]) {
        if (!visited[child]) dfs(child, x, d+1);
    }
}

// query, log n
int lca(int a, int b) {
    /* ===== Bring a and b to the same depth ===== */
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    for (int i = 0; i <= 17; i++) {
        if ((c >> i) & 1)
            a = p[i][a];
    }
    if (a == b) return a;        // Edge case: lca(a, b) = b

    /* ===== LCA ===== */
    for (int i = 17; i >= 0; i--) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }
    return p[0][a];
}

int getDist(int a, int b) {
    return dist[a] + dist[b] - 2*dist[lca(a, b)];
}

int main() {
    int n, q; cin >> n >> q;
    adjList.resize(n+10);
    memset(visited, false, sizeof visited);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    dfs(1, 1, 1);
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << getDist(a, b) << endl;
    }
    return 0;
}
