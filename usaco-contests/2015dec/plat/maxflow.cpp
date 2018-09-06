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
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int n, k;
vi adjList[50001];
int depth[50001], p[17][50001];
int delta[50001];
int best = 0;

int dfs(int node, int parent) {
    int score = delta[node];
    for (int child : adjList[node]) {
        if (child != parent) {
            score += dfs(child, node);
        }
    }
    best = max(score, best);
    return score;
}

void build(int x, int pa, int d) {
    depth[x] = d;
    p[0][x] = pa;
    FOR(i, 1, 17) {
        p[i][x] = p[i-1][p[i-1][x]];
    }
    for (int child : adjList[x]) {
        if (child != pa) build(child, x, d+1);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    F0R(i, 17) {
        if ((c >> i) & 1) a = p[i][a];
    }
    if (a == b) return a;

    F0Rd(i, 17) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }
    return p[0][a];
}

int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    cin >> n >> k;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    build(1, 1, 1);

    SET(delta, 0, 50001);

    F0R(i, k) {
        int s, t; cin >> s >> t;
        int lca1 = lca(s, t);
        delta[lca1]--;
        delta[p[0][lca1]]--;
        delta[s]++;
        delta[t]++;
    }

    dfs(1, 1);

    cout << best << endl;

    return 0;
}
