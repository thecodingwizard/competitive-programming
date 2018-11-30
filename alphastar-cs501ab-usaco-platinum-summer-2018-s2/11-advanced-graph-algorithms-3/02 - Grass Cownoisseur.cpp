/*
Grass Cownoisseur
=================

In an effort to better manage the grazing patterns of his cows, Farmer
John has installed one-way cow paths all over his farm.  The farm
consists of N fields, conveniently numbered 1..N, with each one-way
cow path connecting a pair of fields.  For example, if a path connects
from field X to field Y, then cows are allowed to travel from X to Y
but not from Y to X.

Bessie the cow, as we all know, enjoys eating grass from as many
fields as possible.  She always starts in field 1 at the beginning of
the day and visits a sequence of fields, returning to field 1 at the
end of the day.  She tries to maximize the number of distinct fields
along her route, since she gets to eat the grass in each one (if she
visits a field multiple times, she only eats the grass there once).

As one might imagine, Bessie is not particularly happy about the
one-way restriction on FJ's paths, since this will likely reduce the
number of distinct fields she can possibly visit along her daily
route.  She wonders how much grass she will be able to eat if she
breaks the rules and follows up to one path in the wrong direction.
Please compute the maximum number of distinct fields she can visit
along a route starting and ending at field 1, where she can follow up
to one path along the route in the wrong direction.  Bessie can only
travel backwards at most once in her journey.  In particular, she
cannot even take the same path backwards twice.

INPUT:

The first line of input contains N and M, giving the number of fields
and the number of one-way paths (1 <= N, M <= 100,000).

The following M lines each describe a one-way cow path.  Each line
contains two distinct field numbers X and Y, corresponding to a cow
path from X to Y.  The same cow path will never appear more than once.

SAMPLE INPUT:

7 10
1 2
3 1
2 5
2 4
3 7
3 5
3 6
6 5
7 2
4 7

OUTPUT:

A single line indicating the maximum number of distinct fields Bessie
can visit along a route starting and ending at field 1, given that she can
follow at most one path along this route in the wrong direction.

SAMPLE OUTPUT:

6

SOLUTION NOTES:

Here is an ASCII drawing of the sample input:

v---3-->6
7   |\  |
^\  v \ |
| \ 1  \|
|  \|   v
|   v   5
4<--2---^

Bessie can visit pastures 1, 2, 4, 7, 2, 5, 3, 1 by traveling
backwards on the path between 5 and 3.  When she arrives at 3 she
cannot reach 6 without following another backwards path.
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


#define UNVISITED (-1)

vi dfs_num;     // this variable has to be global, we cannot put it in recursion
int numCC;

vector<vi> adjList;

vi dfs_low;       // additional information for articulation points/bridges/SCCs
int dfsNumberCounter;

vi S, visited;                                    // additional global variables
int numSCC;

int nodeNum[100001];
int weight[100001];
int dp[100001];
int reverseDP[100001];
vi compressedAdjList[100001];
vi reverseCompressedAdjList[100001];

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
    S.push_back(u);           // stores u in a vector based on order of visitation
    visited[u] = 1;
    for (int j = 0; j < (int)adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == UNVISITED)
            tarjanSCC(v);
        if (visited[v])                                // condition for update
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
        int nodes = 0;
        while (true) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            nodes++;
            nodeNum[v] = numSCC;
            if (u == v) break;
        }
        weight[numSCC] = nodes;
        numSCC++;
    } }

int best = 0;

void dfsForward(int node, int soFar) {
    int exitNow = -INF;
    for (int backedge : reverseCompressedAdjList[node]) {
        if (reverseDP[backedge] >= 0) exitNow = max(exitNow, reverseDP[backedge]);
    }
    exitNow += soFar + weight[node];
    for (int child : compressedAdjList[node]) {
        dfsForward(child, soFar + weight[node]);
    }
    best = max(best, exitNow);
}

int dfsBackward(int node) {
    if (reverseDP[node] != -1) return reverseDP[node];
    if (node == nodeNum[0]) return reverseDP[node] = 0;
    if (node <= nodeNum[0]) return -INF;
    int num = -INF*2;
    for (int child : compressedAdjList[node]) {
        num = max(num, dfsBackward(child));
    }
    num += weight[node];
    return reverseDP[node] = num;
}

int main() {
    int n, m;
    cin >> n >> m;
    adjList.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adjList[--a].push_back(--b);
    }

    dfs_num.assign(n, UNVISITED); dfs_low.assign(n, 0); visited.assign(n, 0);
    dfsNumberCounter = numSCC = 0;
    for (int i = 0; i < n; i++)
        if (dfs_num[i] == UNVISITED)
            tarjanSCC(i);

    for (int i = 0; i < n; i++) {
        for (int child : adjList[i]) {
            if (nodeNum[i] == nodeNum[child]) continue;
            compressedAdjList[nodeNum[i]].push_back(nodeNum[child]);
            reverseCompressedAdjList[nodeNum[child]].push_back(nodeNum[i]);
        }
    }

    memset(dp, -1, sizeof dp);
    memset(reverseDP, -1, sizeof reverseDP);

    for (int i = 0; i < numSCC; i++) dfsBackward(i);
    dfsForward(nodeNum[0], 0);
    cout << best << endl;
    return 0;
}
