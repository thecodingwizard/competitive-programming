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

int main() {
    freopen("wifi.in", "r", stdin);
    freopen("wifi.out", "w", stdout);

    int n, a, b; cin >> n >> a >> b;
    int cows[n]; F0R(i, n) cin >> cows[i];
    sort(cows, cows+n);

    double dp[n+1]; F0R(i, n+1) dp[i] = LL_INF;
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double cost = double(cows[j] - cows[i])/2.0*b+a;
            dp[j+1] = min(dp[j+1], dp[i] + cost);
        }
    }

    cout << setprecision(9) << dp[n] << endl;

    return 0;
}
