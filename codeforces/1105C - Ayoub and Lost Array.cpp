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
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
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
#define MOD2 1000000007
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
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

int main() {
    int n, l, r; cin >> n >> l >> r;
    ll ways[3];
    SET(ways, 0, 3);

    if (r - l < 3) {
        FOR(i, l, r + 1) {
            ways[(i%3)]++;
        }
    } else {
        FOR(i, (l%3), 3) ways[i]++;
        l += (3 - (l % 3));
        int dist = r - l + 1;
        int toAdd = dist/3;
        ways[0] += toAdd;
        ways[1] += toAdd;
        ways[2] += toAdd;
        F0R(i, dist - toAdd*3) ways[i]++;
        F0R(i, 3) ways[i] %= MOD2;
    }


    ll dp[n+10][3];

    SET2D(dp, 0, n+10, 3);

    dp[0][0] = 1;
    F0R(i, n) {
        F0R(j, 3) {
            if (dp[i][j] == 0) continue;
            F0R(k, 3) {
                dp[i + 1][(j + k)%3] += (dp[i][j] * ways[k] % MOD2);
                dp[i + 1][(j + k)%3] %= MOD2;
            }
        }
    }

    cout << dp[n][0] << endl;

    return 0;
}
