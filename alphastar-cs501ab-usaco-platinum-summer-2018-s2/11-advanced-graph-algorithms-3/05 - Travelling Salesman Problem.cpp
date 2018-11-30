/*
Travelling Salesman Problem
===========================

Given N cities (1 < N < 20) and M two-way roads between cities,
the problem is to find the shortest possible path that visits
every city exactly once.

PROBLEM NAME: tsp

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M.

* Line 2..M+1: three space-separated integers: V1, V2 and D
        Distance D of the road between cities V1 and V2
        (0 < D <= 1000).

SAMPLE INPUT:

5 8
3 5 8
5 4 11
2 5 7
5 1 12
4 2 10
1 2 4
4 3 6
3 2 9

OUTPUT FORMAT:

* Line 1: A line containing a single integer, the total distance
        of the shortest path that travels all cities exactly once.
        If it is impossible output "IMPOSSIBLE".

SAMPLE OUTPUT:

25

OUTPUT DETAILS:

One can travel using the path 1-2-5-3-4. The total distance is
4 + 7 + 8 + 6 = 25.
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

int dist[20][20];
int memo[20][(1 << 19) - 1];
int n, m;

int tsp(int pos, int mask) {
    if (mask == (1 << n) - 1) return 0;
    if (memo[pos][mask] != -1) return memo[pos][mask];
    int ans = INF;
    for (int i = 0; i < n; i++) {
        if (i == pos || (mask & (1 << i)) || dist[pos][i] == INF) continue;
        ans = min(ans, dist[pos][i] + tsp(i, mask | (1 << i)));
    }
    return memo[pos][mask] = ans;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) dist[i][j] = INF;
    memset(memo, -1, sizeof memo);

    for (int i = 0; i < m; i++) {
        int a, b, l; cin >> a >> b >> l;
        dist[--a][--b] = dist[b][a] = l;
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, tsp(i, (1 << i)));
    }
    cout << ans << endl;
    return 0;
}
