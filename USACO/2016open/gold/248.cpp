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

int dp[248][248];

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);

    int n; cin >> n;
    int A[n]; F0R(i, n) cin >> A[i];

    SET2D(dp, -1, 248, 248);

    int ans = 0;
    F0R(size, n) {
        F0R(start, n-size) {
            int end = start + size;
            if (end == start) {
                dp[start][end] = A[start];
            } else {
                F0R(top, size) {
                    int split = start + top;
                    if (dp[start][split] == dp[split+1][end]) {
                        dp[start][end] = max(dp[start][end], dp[start][split] + 1);
                        ans = max(ans, dp[start][end]);
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
