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

int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    int n, m, k; cin >> n >> m >> k;
    int A[n], B[m]; F0R(i, n) cin >> A[i]; F0R(j, m) cin >> B[j];
    sort(A, A+n);
    sort(B, B+m);
    ll dp[n][m][k];
    int mod = 1000000009;
    F0R(i, n) F0R(j, m) F0R(x, k) dp[i][j][x] = 0;
    F0R(x, k) {
        F0R(i, n) {
            F0R(j, m) {
                ll ways = 0;
                if (i > 0) ways += dp[i-1][j][x];
                if (j > 0) ways += dp[i][j-1][x];
                if (i > 0 && j > 0) ways -= dp[i-1][j-1][x];
                ways += mod;
                ways %= mod;
                if (A[i] > B[j]) {
                    if (x > 0) {
                        if (i > 0 && j > 0) ways += dp[i-1][j-1][x-1];
                        ways += mod;
                        ways %= mod;
                    } else {
                        ways++;
                    }
                    dp[i][j][x] = ways;
                } else {
                    dp[i][j][x] = ways;
                }
                dp[i][j][x] %= mod;
            }
        }
    }
    ll ans = dp[n-1][m-1][k-1];
//    F0R(i, n) F0R(j, m) ans = (ans + dp[i][j][k-1])%mod;
    cout << ans << endl;

    return 0;
}
