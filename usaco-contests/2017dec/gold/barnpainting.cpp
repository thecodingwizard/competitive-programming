/*
ID: nathan.18
TASK: kimbits
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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, k;
vi adjList[100001];
int color[100001];
ll dp[100001][4];

ll solve(int node, int bad, int parent) {
    if (dp[node][bad] != -1) return dp[node][bad];
    if (color[node] == bad) return 0;
    ll finalAns = 0;
    FOR(target, 1, 4) {
        if (target == bad) continue;
        if (color[node] != -1 && color[node] != target) continue;
        ll ans = 1;
        for (int child : adjList[node]) {
            if (child == parent) continue;
            ans *= solve(child, target, node);
            if (ans % (int)1e+9+7 != 0) ans %= (int)1e+9+7;
        }
        finalAns += ans;
        finalAns %= (int)1e+9+7;
    }
    return dp[node][bad] = finalAns;
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    cin >> n >> k;
    F0R(i, n+1) color[i] = -1;
    F0R(i, n-1) {
        int x, y; cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
    F0R(i, k) {
        int x, y; cin >> x >> y;
        color[x] = y;
    }

    memset(dp, -1, sizeof dp);
    ll ans = solve(1, 0, -1);
    cout << ans%int(1e+9+7) << endl;

    return 0;
}
