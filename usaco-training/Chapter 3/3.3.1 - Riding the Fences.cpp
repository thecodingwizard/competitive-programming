/*
ID: nathan.18
TASK: fence
LANG: C++11
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
    freopen("fence.in", "r", stdin);
    freopen("fence.out", "w", stdout);

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