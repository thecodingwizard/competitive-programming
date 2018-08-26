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

double dp[33][33];

void solve(int n, int l, double i) {
    if (n == 0) return;
    double numCombinations = dp[n-1][l];
    if (i > numCombinations) {
        cout << "1";
        solve(n-1, l-1, i - numCombinations);
    } else {
        cout << "0";
        solve(n-1, l, i);
    }
}

int main() {
    freopen("kimbits.in", "r", stdin);
    freopen("kimbits.out", "w", stdout);

    int n, l; double i; cin >> n >> l >> i;

    F0R(j, 33) dp[0][j] = 1;
    FOR(i, 1, 33) F0R(j, 33) dp[i][j] = (j == 0 ? 1 : dp[i-1][j-1] + dp[i-1][j]);

    solve(n, l, i);

    cout << endl;

    return 0;
}
