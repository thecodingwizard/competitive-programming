#include "grader.h"

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
#include <ctime>
#include <list>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

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

vi children[100000];
int sz[100000];
ii loc[100000];

int depth[100001], p[18][100001];

void buildLCA(int x, int pa, int d) {
    depth[x] = d;
    p[0][x] = pa;
    FOR(i, 1, 18) {
        p[i][x] = p[i-1][p[i-1][x]];
    }
    for (int child : children[x]) {
        if (child != pa) buildLCA(child, x, d+1);
    }
}

int findLCA(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    F0R(i, 18) {
        if ((c >> i) & 1) a = p[i][a];
    }
    if (a == b) return a;

    F0Rd(i, 18) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }
    return p[0][a];
}

int findLCA2(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int c = depth[a] - depth[b];
    F0R(i, 18) {
        if ((c >> i) & 1) a = p[i][a];
    }
    if (a == b) {
        assert(false);
        return a;
    }

    F0Rd(i, 18) {
        if (p[i][a] != p[i][b]) {
            a = p[i][a];
            b = p[i][b];
        }
    }
    return b;
}

void addRoad(int a, int b) {
    children[a].pb(b);
    children[b].pb(a);
}

int dfsSz(int u, int p) {
    sz[u] = 1;
    for (int v : children[u]) {
        if (v == p) continue;
        sz[u] += dfsSz(v, u);
    }
    return sz[u];
}

void build(int node, int parent, int startX, int endX, int startY, int endY) {
    loc[node] = { startX, startY };
    setFarmLocation(node, startX, startY);
    vector<ii> todo;
    for (int u : children[node]) {
        if (u == parent) continue;
        todo.pb(mp(sz[u], u));
    }
    SORT(todo);
    int processed = 0;
    for (ii x : todo) {
        int u = x.pB;
        build(u, node, endX - processed - sz[u] + 1, endX - processed, startY + processed + 1, startY + processed + sz[u]);
        processed += sz[u];
    }
}

void buildFarms() {
    dfsSz(0, 0);

    int n = getN();
    build(0, 0, 1, n, 1, n);
    buildLCA(0, 0, 0);
}

void addBox2(int x, int y, int a, int b) {
    if (x > a) {
        addBox(a, b, x, y);
    } else {
        addBox(x, y, a, b);
    }
}

void notifyFJ(int a, int b) {
    if (depth[a] < depth[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int lca = findLCA(a, b);
    if (lca == a || lca == b) {
        addBox2(loc[a].pA, loc[a].pB, loc[b].pA, loc[b].pB);
    } else {
        int magic = findLCA2(a, b);

        addBox2(loc[lca].pA, loc[lca].pB, loc[a].pA, loc[a].pB);
        addBox2(loc[magic].pA, loc[magic].pB, loc[b].pA, loc[b].pB);
    }
}

void testNotify(int a, int b) {
    cout << "Notifying " << a << ", " << b << endl;
    notifyFJ(a, b);
}
int main() {
    addRoad(0, 1);
    addRoad(1, 3);
    addRoad(1, 4);
    addRoad(0, 2);
    buildFarms();

//    testNotify(1, 4);
//    testNotify(1, 3);
//    testNotify(0, 2);
//    testNotify(2, 0);
    testNotify(2, 3);

    return 0;
}