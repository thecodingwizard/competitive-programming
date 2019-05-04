/*
Running Away From the Barn
==========================

It's milking time at Farmer John's farm, but the cows have all run away!
Farmer John needs to round them all up, and needs your help in the search.

FJ's farm is a series of  N (1 <= N <= 200,000) pastures numbered 1 ... N
connected by N - 1 bidirectional paths. The barn is located at pasture 1,
and it's possible to reach any pasture from the barn.

FJ's cows were in their pastures this morning, but who knows where they ran
to by now. FJ does know that the cows only run away from the barn, and they
are too lazy to run a distance of more than L. For every pasture, FJ wants
to
know how many different pastures cows starting in that pasture could have
ended up in.

Note: 64-bit integers (int64 in Pascal, long long in C/C++ and long in Java)
are needed to store the distance values.

PROBLEM NAME: runaway

INPUT FORMAT:

* Line 1: 2 integers, N and L (1 <= N <= 200,000, 1 <= L <= 10^18)

* Lines 2..N: The ith line contains two integers p_i and l_i. p_i (1
        <= p_i < i) is the  first pasture on the shortest path between
        pasture i and the barn, and l_i  (1 <= l_i <= 10^12) is the
        length of that path.

SAMPLE INPUT:

4 5
1 4
2 3
1 5

OUTPUT FORMAT:

* Lines 1..N: One number per line, the number on line i is the number
        pastures that can be  reached from pasture i by taking roads
        that lead strictly farther away from  the barn (pasture 1)
        whose total length does not exceed L.

SAMPLE OUTPUT:

3
2
1
1

OUTPUT DETAILS:

Cows from pasture 1 can hide at pastures 1, 2, 4
Cows from pasture 2 can hide at pastures 2 and 3
Pasture 3 and 4 are as far from the barn as possible, and the cows can hide
there.
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

vector<vector<pair<int, long long>>> adjList;
int n;
long long l;
int p[18][200001];
long long d[200001];
int toSubtract[200001];
long long ans[200001];
int depth[200001];

// Building the parent array, n log n
void dfs(int x, int pa, long long dist) {                  // node, parent of node, depth of node
    d[x] = dist;
    p[0][x] = pa;
    for (int i = 1; i < 18; i++) {
        p[i][x] = p[i - 1][p[i - 1][x]];
    }
    for (auto child : adjList[x]) {
        dfs(child.A, x, dist + child.B);
    }
}

long long dfsAns(int x) {
    long long counter = 1;
    for (auto child : adjList[x]) {
        counter += dfsAns(child.A);
    }
    counter -= toSubtract[x];
    return ans[x] = counter;
}

long long dist(int b, int a) {
    return d[b] - d[a];
}

int main() {
    cin >> n >> l;
    adjList.resize(n+10);
    for (int i = 1; i <= n - 1; i++) {
        int pi; long long li; cin >> pi >> li;
        adjList[pi].push_back(mp(i + 1, li));
    }
    dfs(1, 1, 0);
    memset(toSubtract, 0, sizeof toSubtract);
    for (int i = 2; i <= n; i++) {
        int a = i;
        long long cur = 0;
        for (int j = 17; j >= 0; j--) {
            if (cur + dist(a, p[j][a]) <= l) {
                cur += dist(a, p[j][a]);
                a = p[j][a];
            }
        }
        toSubtract[(a == 1 ? 0 : p[0][a])]++;
    }
    memset(ans, -1, sizeof ans);
    dfsAns(1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
