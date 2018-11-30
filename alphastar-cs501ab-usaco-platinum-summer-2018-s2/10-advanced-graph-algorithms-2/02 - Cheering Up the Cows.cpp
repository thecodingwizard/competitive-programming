/*
Cheering up the Cows
====================

Farmer John has grown so lazy that he no longer wants to continue
maintaining the cow paths that currently provide a way to visit
each of his N (5 <= N <= 10,000) pastures (conveniently numbered
1..N). Each and every pasture is home to one cow. FJ plans to remove
as many of the P (N-1 <= P <= 100,000) paths as possible while keeping
the pastures connected. You must determine which N-1 paths to keep.

Bidirectional path j connects pastures S_j and E_j (1 <= S_j <= N;
1 <= E_j <= N; S_j != E_j) and requires L_j (0 <= L_j <= 1,000) time
to traverse. No pair of pastures is directly connected by more than
one path.

The cows are sad that their transportation system is being reduced.
You must visit each cow at least once every day to cheer her up.
Every time you visit pasture i (even if you're just traveling
through), you must talk to the cow for time C_i (1 <= C_i <= 1,000).

You will spend each night in the same pasture (which you will choose)
until the cows have recovered from their sadness. You will end up
talking to the cow in the sleeping pasture at least in the morning
when you wake up and in the evening after you have returned to
sleep.

Assuming that Farmer John follows your suggestions of which paths
to keep and you pick the optimal pasture to sleep in, determine the
minimal amount of time it will take you to visit each cow at least
once in a day.

For your first 10 submissions, you will be provided with the results of
running your program on a part of the actual test data.

POINTS: 300

PROBLEM NAME: cheer

INPUT FORMAT:

* Line 1: Two space-separated integers: N and P

* Lines 2..N+1: Line i+1 contains a single integer: C_i

* Lines N+2..N+P+1: Line N+j+1 contains three space-separated
        integers: S_j, E_j, and L_j

SAMPLE INPUT:

5 7
10
10
20
6
30
1 2 5
2 3 5
2 4 12
3 4 17
2 5 15
3 5 6
4 5 12




INPUT DETAILS:

              +-(15)-+
             /        \
            /          \
     1-(5)-2-(5)-3-(6)--5
            \   /(17)  /
         (12)\ /      /(12)
              4------+

OUTPUT FORMAT:

* Line 1: A single integer, the total time it takes to visit all the
        cows (including the two visits to the cow in your
        sleeping-pasture)

SAMPLE OUTPUT:

176

OUTPUT DETAILS:

Keep these paths:

     1-(5)-2-(5)-3      5
            \          /
         (12)\        /(12)
             *4------+

Wake up in pasture 4 and visit pastures in the order 4, 5, 4, 2,
3, 2, 1, 2, 4 yielding a total time of 176 before going back to
sleep.
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

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
    vi p, rank, setSize;                       // remember: vi is vector<int>
    int numSets;
public:
    UnionFind(int N) {
        setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
        p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) { numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else                   { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

struct Edge {
    int first{}, second{}, weight{};
    Edge() = default;

    Edge(int _first, int _second, int _weight) : first(_first), second(_second), weight(_weight) {}
};

int main() {
    int n, p; cin >> n >> p;
    int cows[n], cheapestCow = INF;

    for (int i = 0; i < n; i++) {
        cin >> cows[i];
        cheapestCow = min(cheapestCow, cows[i]);
    }

    vector<Edge> edges;
    for (int i = 0; i < p; i++) {
        Edge e; cin >> e.first >> e.second >> e.weight;
        e.first--; e.second--;
        e.weight += cows[e.first] + cows[e.second] + e.weight;
        edges.push_back(e);
    }
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });

    long long totCost = cheapestCow;
    UnionFind UF(n);
    for (Edge e : edges) {
        if (!UF.isSameSet(e.first, e.second)) {
            UF.unionSet(e.first, e.second);
            totCost += e.weight;
        }
    }

    cout << totCost << endl;

    return 0;
}
