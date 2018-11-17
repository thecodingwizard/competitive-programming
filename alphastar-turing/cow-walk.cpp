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
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int n;
int dfs_low[300010], dfs_num[300010], dfsNumberCounter;
bool visited[300010];
int sccStack[300010], stackIdx = 0;
#define DFS_WHITE -1
int numSCC = 0;
int scc[300010];
int sccSz[300010];
int A[300010];

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      // dfs_low[u] <= dfs_num[u]
    sccStack[stackIdx++] = u;          // stores u in a vector based on order of visitation
    if (stackIdx > 200000) {
        cout << "Stack size > 200000" << endl;
        exit(0);
    }
    visited[u] = 1;
    int next = A[u];
    if (dfs_num[next] == DFS_WHITE)
        tarjanSCC(next);
    if (visited[next])                                // condition for update
        dfs_low[u] = min(dfs_low[u], dfs_low[next]);

    if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
        numSCC++;
        int sz = 0;
        while (1) {
            int v = sccStack[--stackIdx];
            visited[v] = 0;
            scc[v] = numSCC;
            sz++;
            if (u == v) break;
        }
        sccSz[numSCC] = sz;
    }
}

pll dp[300010];
pll run(int node) {
    if (dp[node].pA != -1) return dp[node];
    int target = A[node];
    int targetSCC = scc[target];
    ll sz = sccSz[targetSCC];
    if (scc[target] == scc[node]) {
        // same SCC
        return mp(sz, sz * (sz - 1) / 2);
    }
    pll next = run(target);
    return dp[node] = mp(next.pA + 1, next.pB + next.pA);
}

int main() {
    cin >> n;
    F0R(i, n) {
        cin >> A[i];
        A[i]--;
//        if (i < 299000) {
//            A[i] = i+1;
//        } else {
//            A[i] = 3;
//        }
    }

    SET(dfs_num, DFS_WHITE, n);
    SET(dfs_low, 0, n);
    SET(visited, false, n);

    F0R(i, n) {
        if (dfs_num[i] == DFS_WHITE) {
            tarjanSCC(i);
        }
        dp[i].pA = -1;
    }

    ll num = 0, tot = 0;
    F0R(i, n) {
        pll res = run(i);
        num += res.pA;
        tot += res.pB;
    }
    num -= n;

    cout << num << " " << tot << endl;

    return 0;
}