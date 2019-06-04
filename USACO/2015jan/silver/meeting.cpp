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

#define INF 1000000000
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

int n, m;
bool dp[101][10001];
bool dp2[101][10001];
vii bessie[101], elsie[101];

int main() {
    freopen("meeting.in", "r", stdin);
    freopen("meeting.out", "w", stdout);

    cin >> n >> m;
    memset(dp, false, sizeof dp);
    memset(dp2, false, sizeof dp2);
    F0R(i, m) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        bessie[a].push_back(mp(b, c));
        elsie[a].push_back(mp(b, d));
    }

    dp[1][0] = dp2[1][0] = true;
    FOR(i, 1, n+1) {
        F0R(j, 10001) {
            if (dp[i][j]) {
                for (ii child : bessie[i]) {
                    dp[child.A][j + child.B] = true;
                }
            }
            if (dp2[i][j]) {
                for (ii child : elsie[i]) {
                    dp2[child.A][j + child.B] = true;
                }
            }
        }
    }
    int ans = 0;
    F0R(i, 10001) {
        if (dp[n][i] && dp2[n][i]) {
            ans = i;
            break;
        }
    }
    if (ans == 0) cout << "IMPOSSIBLE" << endl;
    else cout << ans << endl;

    return 0;
}
