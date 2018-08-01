/*
ID: nathan.18
TASK: inflate
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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1100000000
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

int main() {
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);

    int m, n; cin >> m >> n;
    ii categories[n]; F0R(i, n) cin >> categories[i].A >> categories[i].B;
    int dp[m+10];
    memset(dp, 0, sizeof dp);
    F0R(j, n) {
        int pts = categories[j].A, time = categories[j].B;
        FOR(i, time, m+1) dp[i] = max(dp[i], dp[i-time]+pts);
    }
    cout << dp[m] << endl;

    return 0;
}
