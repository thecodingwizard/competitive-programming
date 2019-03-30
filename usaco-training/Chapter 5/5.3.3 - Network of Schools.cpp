/*
ID: nathan.18
TASK: schlnet
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

int n;
vi children[100];
int dfsLow[100], dfsNum[100], dfsCtr = 0;
bool visited[100];
int root[100];
vi S;
int sccCtr = 0;
int sccNum[100];
set<int> sccParent[100], sccChildren[100];

void dfs(int u, int r) {
    if (visited[u]) return;
    visited[u] = true;
    root[u] = r;
    for (int v : children[u]) {
        dfs(v, r);
        root[v] = r;
    }
}

void tarjanSCC(int u) {
    dfsLow[u] = dfsNum[u] = dfsCtr++;
    S.pb(u);
    visited[u] = true;
    for (int v : children[u]) {
        if (dfsNum[v] == INF) {
            tarjanSCC(v);
        }
        if (visited[v]) {
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
        }
    }

    if (dfsLow[u] == dfsNum[u]) {
        while (true) {
            int v = S.back(); S.pop_back(); visited[v] = false;
            sccNum[v] = sccCtr;
            if (u == v) break;
        }
        sccCtr++;
    }
}

int main() {
    setupIO("schlnet");

    cin >> n;
    F0R(i, n) {
        int child;
        while (cin >> child && child) {
            children[i].pb(child - 1);
        }
    }

    SET(root, -1, 100);
    F0R(i, n) {
        if (root[i] == -1) {
            SET(visited, false, 100);
            dfs(i, i);
        }
    }
    int ansOne = 0;
    F0R(i, n) {
        if (root[i] == i) ansOne++;
    }
    cout << ansOne << endl;

    SET(dfsLow, INF, 100);
    SET(dfsNum, INF, 100);
    SET(visited, false, 100);
    dfsCtr = sccCtr = 0;
    F0R(i, n) {
        if (dfsNum[i] == INF) {
            tarjanSCC(i);
        }
    }
    F0R(i, n) {
        for (int v : children[i]) {
            if (sccNum[v] == sccNum[i]) continue;
            sccChildren[sccNum[i]].insert(sccNum[v]);
            sccParent[sccNum[v]].insert(sccNum[i]);
        }
    }
    int noChildren = 0, noParent = 0;
    F0R(i, sccCtr) {
        if (sccChildren[i].size() == 0) noChildren++;
        if (sccParent[i].size() == 0) noParent++;
    }
    if (sccCtr == 1) {
        cout << 0 << endl;
    } else {
        cout << max(noChildren, noParent) << endl;
    }

    return 0;
}

