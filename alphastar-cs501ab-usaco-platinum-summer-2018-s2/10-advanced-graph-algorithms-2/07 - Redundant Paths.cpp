/*
*** Note: The following code gets WA on one test case. ***

Redundant Paths
===============

In order to get from one of the F (1 <= F <= 5,000) grazing fields
(which are numbered 1..F) to another field, Bessie and the rest of
the herd are forced to cross near the Tree of Rotten Apples.  The
cows are now tired of often being forced to take a particular path
and want to build some new paths so that they will always have a
choice of at least two separate routes between any pair of fields.
They currently have at least one route between each pair of fields
and want to have at least two. Of course, they can only travel on
Official Paths when they move from one field to another.

Given a description of the current set of R (F-1 <= R <= 10,000)
paths that each connect exactly two different fields, determine the
minimum number of new paths (each of which connects exactly two
fields) that must be built so that there are at least two separate
routes between any pair of fields. Routes are considered separate
if they use none of the same paths, even if they visit the same
intermediate field along the way.

There might already be more than one paths between the same pair of
fields, and you may also build a new path that connects the same
fields as some other path.

PROBLEM NAME: rpaths

INPUT FORMAT:

* Line 1: Two space-separated integers: F and R

* Lines 2..R+1: Each line contains two space-separated integers which
        are the fields at the endpoints of some path.

SAMPLE INPUT:

7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7

INPUT DETAILS:

One visualization of the paths is:
   1   2   3
   +---+---+
       |   |
       |   |
 6 +---+---+ 4
      / 5
     /
    /
 7 +

OUTPUT FORMAT:

* Line 1: A single integer that is the number of new paths that must
        be built.

SAMPLE OUTPUT:

2

OUTPUT DETAILS:

Building new paths from 1 to 6 and from 4 to 7 satisfies the conditions.
   1   2   3
   +---+---+
   :   |   |
   :   |   |
 6 +---+---+ 4
      / 5  :
     /     :
    /      :
 7 + - - - -
Check some of the routes:
1 - 2:  1 -> 2 and 1 -> 6 -> 5 -> 2
1 - 4:  1 -> 2 -> 3 -> 4 and 1 -> 6 -> 5 -> 4
3 - 7:  3 -> 4 -> 7 and 3 -> 2 -> 5 -> 7
Every pair of fields is, in fact, connected by two routes.

It's possible that adding some other path will also solve the problem
(like one from 6 to 7). Adding two paths, however, is the minimum.
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
vector<vi> adjList;
vi dfs_num;
vi dfs_low;
vi dfs_parent;
int degree[5000];
int compressedGraphDegree[5000];
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    for (int j = 0; j < (int)adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;

            articulationPointAndBridge(v);

            if (dfs_low[v] > dfs_num[u]) {
                degree[u]++;
                degree[v]++;
//                printf(" Edge (%d, %d) is a bridge\n", u, v);
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u])           // a back edge and not direct cycle
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);       // update dfs_low[u]
    } }

int main() {
    int f, r;
    cin >> f >> r;
    adjList.resize(f);
    memset(degree, 0, sizeof degree);
    memset(compressedGraphDegree, 0, sizeof compressedGraphDegree);
    dfsNumberCounter = 0; dfs_num.assign(f, UNVISITED); dfs_low.assign(f, 0);
    dfs_parent.assign(f, -1);
    int leaves = 0;
    for (int i = 0; i < r; i++) {
        int a, b; cin >> a >> b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    for (int i = 0; i < f; i++)
        if (dfs_num[i] == UNVISITED) {
            dfsRoot = i; rootChildren = 0;
            articulationPointAndBridge(i); }
    for (int i = 0; i < f; i++) {
        compressedGraphDegree[dfs_low[i]] += degree[i];
    }
    for (int i = 0; i < f; i++) {
        if (compressedGraphDegree[i] == 1) leaves++;
    }
    cout << ceil(double(leaves)/2) << endl;
    return 0;
}
