/*
Cow Calisthenics
================

Farmer John continues his never-ending quest to keep the cows fit
by having them exercise on various cow paths that run through the
pastures. These cow paths can be represented as a set of vertices
connected with bidirectional edges so that each pair of vertices
has exactly one simple path between them. In the abstract, their
layout bears a remarkable resemblance to a tree. Surprisingly, each
edge (as it winds its way through the pastures) has the same length.

For any given set of cow paths, the canny cows calculate the longest
possible distance between any pair of vertices on the set of cowpaths
and call it the pathlength. If they think this pathlength is too
large, they simply refuse to exercise at all.

Farmer John has mapped the paths and found V (2 <= V <= 100,000)
vertices, conveniently numbered from 1..V. In order to make shorter
cowpaths, he can block the path between any two vertices, thus
creating more sets of cow paths while reducing the pathlength of
both cowpath sets.

Starting from a single completely connected set of paths (which
have the properties of a tree), FJ can block S (1 <= S <= V-1)
paths, creating S+1 sets of paths. Your goal is to compute the best
paths he can create so that the largest pathlength of all those
sets is minimized.

Farmer John has a list of all V-1 edges in his tree, each described
by the two vertices A_i (1 <= A_i <= V) and B_i (1 <= B_i <= V; A_i
!= B_i) that it connects.

Consider this rather linear cowpath set (a tree with 7 vertices):
                   1---2---3---4---5---6---7

If FJ can block two paths, he might choose them to make a map like
this:
		   1---2 | 3---4 | 5---6---7

where the longest pathlength is 2, which would be the answer in
this case. He can do no better than this.

PROBLEM NAME: exercise

INPUT FORMAT:

* Line 1: Two space separated integers: V and S

* Lines 2..V: Two space separated integers: A_i and B_i

SAMPLE INPUT:

7 2
6 7
3 4
6 5
1 2
3 2
4 5

OUTPUT FORMAT:

* Line 1: A single integer that is the best maximum pathlength FJ can
        achieve with S blocks

SAMPLE OUTPUT:

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

vector<vi> adjList;
bool visited[100001];
vector<int> toVisit;
int parent[100001];
int maxLength[100001];

void dfs(int node) {
    if (visited[node]) {
        return;
    }
    visited[node] = true;
    for (int child : adjList[node]) {
        dfs(child);
        parent[child] = node;
    }
    toVisit.push_back(node);
}

int main() {
    int v, s; cin >> v >> s;
    adjList.resize(v+1);
    for (int i = 0; i < v - 1; i++) {
        int a, b; cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    memset(visited, false, sizeof visited);
    dfs(1);
    parent[1] = 0;
    int ans = 0, lo = 1, hi = v, mid;
    while (lo < hi) {
        mid = (lo + hi)/2;
        int cost = 0;
        memset(maxLength, 0, sizeof maxLength);
        for (int node : toVisit) {
            if (node == 1) continue;
            if (maxLength[node] + 1 + maxLength[parent[node]] > mid) {
                cost++;
                maxLength[parent[node]] = min(maxLength[node] + 1, maxLength[parent[node]]);
            } else {
                maxLength[parent[node]] = max(maxLength[parent[node]], maxLength[node] + 1);
            }
        }
        if (cost <= s) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
