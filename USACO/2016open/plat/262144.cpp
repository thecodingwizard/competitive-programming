/*
ID: nathan.18
TASK: spin
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
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

int dp[100][300000];

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);

    int n; cin >> n;
    int A[n]; F0R(i, n) cin >> A[i];
    SET2D(dp, -1, 100, 300000);

    int ans = 0;
    F0R(i, 100) {
        F0R(j, n) {
            if (A[j] == i) {
                dp[i][j] = j + 1;
                ans = max(ans, i);
            } else if (i > 0 && dp[i-1][j] != -1 && dp[i-1][dp[i-1][j]] != -1) {
                dp[i][j] = dp[i-1][dp[i-1][j]];
                ans = max(ans, i);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
