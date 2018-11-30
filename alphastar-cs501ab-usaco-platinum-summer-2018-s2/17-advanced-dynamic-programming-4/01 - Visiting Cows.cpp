/*
Visiting Cows
=============

After many weeks of hard work, Bessie is finally getting a vacation!
Being the most social cow in the herd, she wishes to visit her N
(1 <= N <= 50,000) cow friends conveniently numbered 1..N. The cows
have set up quite an unusual road network with exactly N-1 roads
connecting pairs of cows C1 and C2 (1 <= C1 <= N; 1 <= C2 <= N; C1
!= C2) in such a way that there exists a unique path of roads between
any two cows.

FJ wants Bessie to come back to the farm soon; thus, he has instructed
Bessie that if two cows are directly connected by a road, she may
not visit them both. Of course, Bessie would like her vacation to
be as long as possible, so she would like to determine the maximum
number of cows she can visit.

PROBLEM NAME: vacation

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N: Each line describes a single road with two
        space-separated integers: C1 and C2

SAMPLE INPUT:

7
6 2
3 4
2 3
1 2
7 6
5 6

INPUT DETAILS:

Bessie knows 7 cows. Cows 6 and 2 are directly connected by a road,
as are cows 3 and 4, cows 2 and 3, etc. The illustration below depicts the
roads that connect the cows:

                       1--2--3--4
                          |
                       5--6--7

OUTPUT FORMAT:

* Line 1: A single integer representing the maximum number of cows
        that Bessie can visit.

SAMPLE OUTPUT:

4

OUTPUT DETAILS:

Bessie can visit four cows. The best combinations include two cows
on the top row and two on the bottom. She can't visit cow 6 since
that would preclude visiting cows 5 and 7; thus she visits 5 and
7. She can also visit two cows on the top row: {1,3}, {1,4}, or
{2,4}.
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
#include <unordered_map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n;
vi adjList[50001];
bool visited[50001];
int dontTake[50001], take[50001];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    int dontTakeVal = 0, takeVal = 1;
    for (int child : adjList[node]) {
        if (visited[child]) continue;
        dfs(child);
        dontTakeVal += max(dontTake[child], take[child]);
        takeVal += dontTake[child];
    }
    dontTake[node] = dontTakeVal; take[node] = takeVal;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    for (int i = 0; i < n; i++) dontTake[i] = 0, take[i] = 0, visited[i] = false;
    dfs(0);
    cout << max(dontTake[0], take[0]) << endl;
    return 0;
}
