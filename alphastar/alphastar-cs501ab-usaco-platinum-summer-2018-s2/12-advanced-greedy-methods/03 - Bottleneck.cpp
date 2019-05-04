/*
Bottleneck
==========

Farmer John is gathering the cows. His farm contains a network of
N (1 <= N <= 100,000) fields conveniently numbered 1..N and connected
by N-1 unidirectional paths that eventually lead to field 1. The
fields and paths form a tree.

Each field i > 1 has a single one-way, exiting path to field P_i,
and currently contains C_i cows (1 <= C_i <= 1,000,000,000). In
each time unit, no more than M_i (0 <= M_i <= 1,000,000,000) cows
can travel from field i to field P_i (1 <= P_i <= N) (i.e., only
M_i cows can traverse the path).

Farmer John wants all the cows to congregate in field 1 (which has
no limit on the number of cows it may have). Rules are as follows:

    * Time is considered in discrete units.
    * Any given cow might traverse multiple paths in the same time
      unit. However, no more than M_i total cows can leave field i
      (i.e., traverse its exit path) in the same time unit.
    * Cows never move *away* from field #1.

In other words, every time step, each cow has the choice either to

    a) stay in its current field
    b) move through one or more fields toward field #1, as long
       as the bottleneck constraints for each path are not violated

Farmer John wants to know how many cows can arrive in field 1 by
certain times. In particular, he has a list of K (1 <= K <= 10,000)
times T_i (1 <= T_i <= 1,000,000,000), and he wants to know, for
each T_i in the list, the maximum number of cows that can arrive
at field 1 by T_i if scheduled to optimize this quantity.

Consider an example where the tree is a straight line, and the T_i
list contains only T_1=5, and cows are distibuted as shown:

Locn:      1---2---3---4      <-- Pasture ID numbers
C_i:       0   1   12  12     <-- Current number of cows
M_i:           5   8   3      <-- Limits on path traversal; field
                                  1 has no limit since it has no exit

The solution is as follows; the goal is to move cows to field 1:

Tree:      1---2---3---4
t=0        0   1   12  12     <-- Initial state
t=1        5   4   7   9      <-- field 1 has cows from field 2 and 3
t=2        10  7   2   6
t=3        15  7   0   3
t=4        20  5   0   0
t=5        25  0   0   0

Thus, the answer is 25: all 25 cows can arrive at field 1 by time
t=5.

PROBLEM NAME: bottleneck

INPUT FORMAT:

* Line 1: Two space-separated integers: N and K

* Lines 2..N: Line i (not i+1) describes field i with three
        space-separated integers: P_i, C_i, and M_i

* Lines N+1..N+K: Line N+i contains a single integer: T_i


SAMPLE INPUT:

4 1
1 1 5
2 12 7
3 12 3
5

OUTPUT FORMAT:

* Lines 1..K: Line i contains a single integer that is the maximum
        number of cows that can arrive at field 1 by time T_i.

SAMPLE OUTPUT:

25
*/

/* Note: This O(n*k) solution gives TLE on some test cases. */

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

int n, k;
long long cowsAtPasture[100001];
long long originalCowsAtPasture[100001];
vi traversalPath;
int parent[100001];
int bandwith[100001];
vi reverseAdjList[100001];

void dfsPath(int node) {
    for (int child : reverseAdjList[node]) {
        dfsPath(child);
    }
    traversalPath.push_back(node);
}

int main() {
    cin >> n >> k;
    originalCowsAtPasture[1] = 0;
    for (int i = 2; i <= n; i++) {
        int p, c, m; cin >> p >> c >> m;
        originalCowsAtPasture[i] = c;
        parent[i] = p;
        bandwith[i] = m;
        reverseAdjList[p].push_back(i);
    }
    dfsPath(1);
    for (int i = 0; i < k; i++) {
        for (int j = 1; j <= n; j++) cowsAtPasture[j] = originalCowsAtPasture[j];
        long long t; cin >> t;
        for (int node : traversalPath) {
            long long cows = min(t*bandwith[node], cowsAtPasture[node]);
            cowsAtPasture[parent[node]] += cows;
        }
        cout << cowsAtPasture[1] << endl;
    }
    return 0;
}
