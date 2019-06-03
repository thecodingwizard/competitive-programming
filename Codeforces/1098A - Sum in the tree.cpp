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

ll n, parent[100000], A[100000], val[100000];
vi children[100000];
bool visited[100000];

void bad() {
    cout << "-1" << endl;
    exit(0);
}

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    if (A[node] == -1) {
        // do something about children
        ll minChild = LL_INF;
        for (int child : children[node]) {
            if (A[child] == -1) continue;
            minChild = min(minChild, A[child]);
        }
        if (minChild == LL_INF) minChild = A[parent[node]];
        val[node] = minChild - A[parent[node]];
        if (val[node] < 0) bad();
        A[node] = A[parent[node]] + val[node];
    } else {
        // look to parent
        if (node == 0) val[node] = max(A[node], 0LL);
        else {
            val[node] = A[node] - A[parent[node]];
            if (val[node] < 0) bad();
        }
    }
}

ll dfs2(int node) {
    ll ans = val[node];
    for (int child : children[node]) ans += dfs2(child);
    return ans;
}

void dfs3(int node) {
    dfs(node);
    for (int child : children[node]) dfs3(child);
}

int main() {
    cin >> n;
    parent[0] = -1;
    FOR(i, 1, n) {
        cin >> parent[i];
        parent[i]--;
        children[parent[i]].pb(i);
    }
    F0R(i, n) {
        cin >> A[i];
    }
    SET(visited, false, 100000);

    dfs3(0);

    cout << dfs2(0) << endl;

    return 0;
}