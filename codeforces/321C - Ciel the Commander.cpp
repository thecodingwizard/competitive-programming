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

int n;
set<int> children[100000];
int sz[100000];
vi centroidChildren[100000];
char ans[100000];

int dfsSZ(int node, int p) {
    sz[node] = 1;
    for (int child : children[node]) {
        if (p == child) continue;
        sz[node] += dfsSZ(child, node);
    }
    return sz[node];
}

int dfsCentroid(int node, int parent, int totSz) {
    for (int child : children[node]) {
        if (parent == child) continue;
        if (sz[child] > totSz/2) return dfsCentroid(child, node, totSz);
    }
    return node;
}

int build(int node) {
    dfsSZ(node, node);
    int centroid = dfsCentroid(node, node, sz[node]);
    for (int child : children[centroid]) {
        children[child].erase(centroid);
        centroidChildren[centroid].pb(build(child));
    }
    return centroid;
}

void bad() {
    cout << "Impossible!" << endl;
    exit(0);
}

void assign(int node, char c) {
    if (c > 'Z') bad();
    ans[node] = c;
    for (int child : centroidChildren[node]) {
        assign(child, c+1);
    }
}

int main() {
    cin >> n;
    F0R(i, n - 1) {
        int a, b; cin >> a >> b;
        --a; --b;
        children[a].insert(b);
        children[b].insert(a);
    }

    int topCentroid = build(0);
    assign(topCentroid, 'A');

    cout << ans[0];
    FOR(i, 1, n) cout << " " << ans[i];
    cout << endl;

    return 0;
}