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

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int n, k; cin >> n >> k;
    int dp[n+1][k+1][3]; memset(dp, 0, sizeof dp);
    int fj[n];
    F0R(i, n) {
        char x; cin >> x;
        fj[i] = (x == 'P' ? 1 : (x == 'H' ? 2 : 0));
    }

    F0R(i, n) {
        F0R(j, k+1) {
            F0R(l, 3) {
                dp[i+1][j][l] = max(dp[i+1][j][l], dp[i][j][l] + (fj[i] == l));
                if (j > 0) dp[i+1][j-1][fj[i]] = max(dp[i+1][j-1][fj[i]], dp[i][j][l]+1);
            }
        }
    }

    cout << max(dp[n][0][0], max(dp[n][0][1], dp[n][0][2])) << endl;

    return 0;
}
