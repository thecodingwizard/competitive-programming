/*
Riding the Fences
=================

Farmer John owns a large number of fences that must be repaired
annually. He traverses the fences by riding a horse along each
and every one of them (and nowhere else) and fixing the broken
parts.

Farmer John is as lazy as the next farmer and hates to ride the
same fence twice. Your program must read in a description of a
network of fences and tell Farmer John a path to traverse each
fence length exactly once, if possible. Farmer J can, if he
wishes, start and finish at any fence intersection.

Every fence connects two fence intersections, which are numbered
inclusively from 1 through 500 (though some farms have far fewer
than 500 intersections). Any number of fences (>=1) can meet at
a fence intersection. It is always possible to ride from any
fence to any other fence (i.e., all fences are "connected").

Your program must output the path of intersections that, if
interpreted as a base 500 number, would have the smallest
magnitude. There will always be at least one solution for each
set of input data supplied to your program for testing.

PROGRAM NAME: fence

INPUT FORMAT:

* Line 1: The number of fences, F (1 <= F <= 1024)

* Line 2..F+1: A pair of integers (1 <= i,j <= 500) that tell
               which pair of intersections this fence connects.

SAMPLE INPUT:

9
1 2
2 3
3 4
4 2
4 5
2 5
5 6
5 7
4 6

OUTPUT FORMAT:

The output consists of F+1 lines, each containing a single
integer. Print the number of the starting intersection on the
first line, the next intersection's number on the next line,
and so on, until the final intersection on the last line. There
might be many possible answers to any given input set, but only
one is ordered correctly.

SAMPLE OUTPUT:

1
2
3
4
2
5
4
6
5
7
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

int f;
int adjMatrix[501][501];
int edges[501];
vi tour;

void dfs(int node) {
    for (int i = 1; i <= 500; i++) {
        while (adjMatrix[node][i] > 0) {
            adjMatrix[node][i]--;
            adjMatrix[i][node]--;
            dfs(i);
        }
    }
    tour.push_back(node);
}

int main() {
    cin >> f;
    memset(adjMatrix, 0, sizeof adjMatrix);
    for (int i = 0; i < f; i++) {
        int a, b; cin >> a >> b;
        adjMatrix[a][b]++; adjMatrix[b][a]++;
        edges[a]++;
        edges[b]++;
    }
    bool good = false;
    for (int i = 1; i <= 500; i++) {
        if (edges[i] % 2 == 1) {
            dfs(i);
            good = true;
            break;
        }
    }
    if (!good) dfs(1);
    reverse(tour.begin(), tour.end());
    for (int node : tour) cout << node << endl;
    return 0;
}
