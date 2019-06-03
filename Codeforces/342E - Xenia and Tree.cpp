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
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define MOD2 1000000007
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, m;
set<int> children[100000];
int sz[100000], parent[100000], depth[100000], minDist[100000], depthParent[18][100000];

void buildDepth(int node, int p, int d) {
    depth[node] = d;
    depthParent[0][node] = p;
    FOR(i, 1, 18) depthParent[i][node] = depthParent[i - 1][depthParent[i - 1][node]];
    for (int child : children[node]) {
        if (child == p) continue;
        buildDepth(child, node, d + 1);
    }
}

int dfs(int node, int p) {
    sz[node] = 1;

    for (int child : children[node]) {
        if (child == p) continue;
        sz[node] += dfs(child, node);
    }

    return sz[node];
}

int dfs2(int node, int p, int n) {
    for (int child : children[node]) {
        if (child == p) continue;
        if (sz[child] > n/2) return dfs2(child, node, n);
    }
    return node;
}

int build(int node) {
    dfs(node, -1);
    int centroid = dfs2(node, -1, sz[node]);
    for (int child : children[centroid]) {
        children[child].erase(centroid);
        parent[build(child)] = centroid;
    }
    return centroid;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    F0R(i, 18) if ((c >> i) & 1) a = depthParent[i][a];
    if (a == b) return a;

    F0Rd(i, 18) {
        if (depthParent[i][a] != depthParent[i][b]) {
            a = depthParent[i][a];
            b = depthParent[i][b];
        }
    }
    return depthParent[0][a];
}

int dist(int a, int b) {
    return depth[a] + depth[b] - 2*depth[lca(a, b)];
}

void setRed(int node) {
    int origNode = node;
    minDist[node] = 0;
    while (parent[node] != -1) {
        node = parent[node];
        minDist[node] = min(minDist[node], dist(node, origNode));
    }
}

int getMinDist(int node) {
    int best = INF;
    int origNode = node;
    while (node != -1) {
        best = min(best, minDist[node] + dist(node, origNode));
        node = parent[node];
    }
    return best;
}

int main() {
    cin >> n >> m;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        --a; --b;
        children[a].insert(b);
        children[b].insert(a);
    }

    buildDepth(0, 0, 0);

    SET(parent, -1, n);
    build(0);

    SET(minDist, INF, n);
    setRed(0);
    F0R(i, m) {
        int a, b; cin >> a >> b;
        if (a == 1) setRed(b-1);
        else cout << getMinDist(b-1) << endl;
    }

    return 0;
}