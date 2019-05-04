/*
Meeting Place
=============

Bessie and Jonell are great friends. Since Farmer John scrambles
where the cows graze every day, they are sometimes quite far from
each other and can't talk.

The pastures and paths on FJ's farm form a 'tree' structure.  Each
pasture has exactly one distinct path to any other pasture, and
each pasture (except pasture #1, the 'root') also has a single
parent node.

Bessie and Jonell have decided that they will always meet at the
closest pasture that that is both an ancestor of Jonell's pasture
and of Bessie's pasture.

FJ created a map of his N (1 <= N <= 1,000) pastures (conveniently
numbered 1..N) that tells the parent P_i (1 <= P_i <= N) of each
pasture except pasture 1, which has no parent.

FJ has released his daily grazing schedule for the next M (1 <= M
<= 1,000) days, so Bessie and Jonell are deciding where they should
meet each day for gossip. On day k, Bessie is in pasture B_k (1 <=
B_k <= N) and Jonell is in pasture J_k (1 <= J_k <= N).

Given a map and schedule, help Bessie and Jonell find their meeting
places.

Consider, for example, the following farm layout:

                            Pasture      Parent Pasture
             [1]           ---------    ----------------
            / | \              1              ---
           /  |  \             2               1
         [2] [3] [6]           3               1
         /        | \          4               2
        /         |  \         5               8
      [4]        [8]  [9]      6               1
                /   \          7               8
               /     \         8               6
             [5]     [7]       9               6

Here are the meeting places that Bessie and Jonell would choose
given a six day schedule of their initial grazing locations:

              Bessie      Jonell       Meeting Place
             --------    --------     ---------------
                 2           7               1
                 4           2               2
                 1           1               1
                 4           1               1
                 7           5               8
                 9           5               6

PROBLEM NAME: meetplace

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M

* Lines 2..N: Line i contains a single integer that describes the
        parent of pasture i:  P_i

* Lines N+1..N+M: Line k+N describes Bessie and Jonell's respective
        pastures with two space-separated integers: B_k and J_k

SAMPLE INPUT:

9 6
1
1
2
8
1
8
6
6
2 7
4 2
3 3
4 1
7 5
9 5

OUTPUT FORMAT:

* Lines 1..M: Line j contains the meeting place Bessie and Jonell
        would use for line j+N of the input

SAMPLE OUTPUT:

1
2
3
1
8
6
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

int depth[100001], p[20][100001];
vector<vi> adjList;

void dfs(int x, int pa, int d) {
    depth[x] = d;
    p[0][x] = pa;
    for (int i = 1; i <= 17; i++) {
        p[i][x] = p[i - 1][p[i - 1][x]];
    }
    for (int child : adjList[x]) {
        dfs(child, x, d + 1);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    for (int i = 0; i <= 17; i++) {
        if ((c >> i) & 1) a = p[i][a];
    }
    if (a == b) return a;

    for (int i = 17; i >= 0; i--) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }

    return p[0][a];
}

int main() {
    int n, m; cin >> n >> m;
    adjList.resize(n+1);
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        adjList[p].push_back(i);
    }
    dfs(1, 1, 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << endl;
    }
    return 0;
}
