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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

vi S, visited;                                    // additional global variables
vi dfs_low, dfs_num;
#define DFS_WHITE (-1) // normal DFS, do not change this with other values (other than 0), because we usually use memset with conjunction with DFS_WHITE
#define DFS_BLACK 1
vector<vi> AdjList;
vii EdgeList;
int numSCC;
int dfsNumberCounter;
int newComponent[1500];
int inDegree[1500], outDegree[1500];

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
    S.push_back(u);           // stores u in a vector based on order of visitation
    visited[u] = 1;
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        int v = AdjList[u][j];
        if (dfs_num[v] == DFS_WHITE)
            tarjanSCC(v);
        if (visited[v])                                // condition for update
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
        while (true) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            newComponent[v] = numSCC;
            if (u == v) break;
        }
        numSCC++;
    }
}

int main() {
    int n, m; cin >> n >> m;
    AdjList.assign(n, vi());
    F0R(i, m) {
        int a, b; cin >> a >> b;
        --a; --b;
        AdjList[a].pb(b);
        EdgeList.pb(mp(a, b));
    }
    dfs_num.assign(n, DFS_WHITE); dfs_low.assign(n, 0); visited.assign(n, 0);
    dfsNumberCounter = numSCC = 0;
    for (int i = 0; i < n; i++)
        if (dfs_num[i] == DFS_WHITE)
            tarjanSCC(i);
    if (numSCC == 1) {
        cout << "0" << endl;
        return 0;
    }
    SET(inDegree, 0, n);
    SET(outDegree, 0, n);
    for (ii edge : EdgeList) {
        int a = newComponent[edge.pA], b = newComponent[edge.pB];
        if (a == b) continue;
        inDegree[b]++;
        outDegree[a]++;
    }
    int inDegreeZero = 0, outDegreeZero = 0;
    F0R(i, numSCC) {
        if (inDegree[i] == 0) inDegreeZero++;
        if (outDegree[i] == 0) outDegreeZero++;
    }
    cout << max(inDegreeZero, outDegreeZero) << endl;

    return 0;
}