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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int h, g;
ii H[1000], G[1000];
int dp[1001][1001][2];

int dist(ii a, ii b) { return (a.A-b.A)*(a.A-b.A)+(a.B-b.B)*(a.B-b.B); }

int solve(int i, int j, int k) {
    if (j == g && i == h && k != 0) return INF;
    if (i == h && j == g) return 0;
    if (dp[i][j][k] != -1) return dp[i][j][k];
    ii cur = k == 0 ? H[i-1] : G[j-1];
    return dp[i][j][k] = min(
            i != h ? (dist(cur, H[i]) + solve(i+1, j, 0)) : INF,
            j != g ? (dist(cur, G[j]) + solve(i, j+1, 1)) : INF
    );
}

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    cin >> h >> g;
    F0R(i, h) cin >> H[i].A >> H[i].B;
    F0R(i, g) cin >> G[i].A >> G[i].B;

    memset(dp, -1, sizeof dp);

    cout << solve(1, 0, 0) << endl;

    return 0;
}
