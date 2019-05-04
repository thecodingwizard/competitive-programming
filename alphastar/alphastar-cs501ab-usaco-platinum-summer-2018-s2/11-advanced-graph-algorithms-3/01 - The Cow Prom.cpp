/*
The Cow Prom
============

The N (2 <= N <= 10,000) cows are so excited: it's prom night! They
are dressed in their finest gowns, complete with corsages and new
shoes. They know that tonight they will each try to perform the
Round Dance.

Only cows can perform the Round Dance which requires a set of ropes
and a circular stock tank. To begin, the cows line up around a
circular stock tank and number themselves in clockwise order
consecutively from 1..N. Each cow faces the tank so she can see the
other dancers.

They then acquire a total of M (2 <= M <= 50,000) ropes all of which
are distributed to the cows who hold them in their hooves.  Each
cow hopes to be given one or more ropes to hold in both her left
and right hooves; some cows might be disappointed.

For the Round Dance to succeed for any given cow (say, Bessie), the
ropes that she holds must be configured just right. To know if
Bessie's dance is successful, one must examine the set of cows
holding the other ends of her ropes (if she has any), along with
the cows holding the other ends of any ropes they hold, etc.  When
Bessie dances clockwise around the tank, she must instantly pull
all the other cows in her group around clockwise, too. Likewise,
if she dances the other way, she must instantly pull the entire
group counterclockwise (anti-clockwise in British English).

Of course, if the ropes are not properly distributed then a set of
cows might not form a proper dance group and thus can not succeed
at the Round Dance. One way this happens is when only one rope
connects two cows. One cow could pull the other in one direction,
but could not pull the other direction (since pushing ropes is
well-known to be fruitless). Note that the cows must Dance in
lock-step: a dangling cow (perhaps with just one rope) that is
eventually pulled along disqualifies a group from properly performing
the Round Dance since she is not immediately pulled into lockstep
with the rest.

Given the ropes and their distribution to cows, how many groups of
cows can properly perform the Round Dance? Note that a set of ropes
and cows might wrap many times around the stock tank.

PROBLEM NAME: prom

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Each line contains two space-separated integers A and
        B that describe a rope from cow A to cow B in the clockwise
        direction.

SAMPLE INPUT:

5 4
2 4
3 5
1 2
4 1

INPUT DETAILS:

ASCII art for Round Dancing is challenging. Nevertheless, here is a
representation of the cows around the stock tank:                         */

//       _1___
//      /**** \
//   5 /****** 2
//  / /**TANK**|
//  \ \********/
//   \ \******/  3
//    \ 4____/  /
//     \_______/

/*
OUTPUT FORMAT:

* Line 1: A single line with a single integer that is the number of
groups successfully dancing the Round Dance.

SAMPLE OUTPUT:

1

OUTPUT DETAILS:

Cows 1, 2, and 4 are properly connected and form a complete Round
        Dance group. Cows 3 and 5 don't have the second rope they'd need
        to be able to pull both ways, thus they can not properly perform the
        Round Dance.
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
//        printf("SCC %d:", ++numSCC);            // this part is done after recursion
        int nodes = 0;
        while (true) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
//            printf(" %d", v);
            nodes++;
            if (u == v) break;
        }
//        printf("\n");
        if (nodes > 1) numSCC++;
    } }

int main() {
    int n, m;
    cin >> n >> m;
    adjList.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adjList[--a].push_back(--b);
//        adjList[b].push_back(a);
    }

    dfs_num.assign(n, UNVISITED); dfs_low.assign(n, 0); visited.assign(n, 0);
    dfsNumberCounter = numSCC = 0;
    for (int i = 0; i < n; i++)
        if (dfs_num[i] == UNVISITED)
            tarjanSCC(i);

    cout << numSCC << endl;

    return 0;
}
