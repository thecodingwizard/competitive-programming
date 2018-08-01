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

int n, b;
int cows[20], volumes[100];
int dp[120001];

int main() {
    freopen("mooomoo.in", "r", stdin);
    freopen("mooomoo.out", "w", stdout);

    cin >> n >> b;
    F0R(i, b) cin >> cows[i];
    F0R(i, n) cin >> volumes[i];
    F0R(i, 100001) dp[i] = INF;

    dp[0] = 0;
    F0R(i, 100001) F0R(j, b) dp[i+cows[j]] = min(dp[i+cows[j]], dp[i]+1);

    int ans = 0;
    F0R(i, n) {
        int adjusted = volumes[i] - (i - 1 >= 0 ? max(volumes[i-1]-1, 0) : 0);
        if (dp[adjusted] == INF) {
            cout << "-1" << endl;
            return 0;
        }
        ans += dp[adjusted];
    }
    cout << ans << endl;

    return 0;
}
