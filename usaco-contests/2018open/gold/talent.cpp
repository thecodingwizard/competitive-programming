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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, w;
ii cows[251];
ll dp[1001];

bool can(int ratio) {
    SET(dp, -LL_INF, 1001);
    dp[0] = 0;
    F0R(i, n) {
        ll val = (ll)cows[i].B*1000 - (ll)ratio*cows[i].A;
        F0Rd(j, w+1) {
            if (dp[j] != -LL_INF) {
                int toUpdate = min(w, j + cows[i].A);
                if (dp[toUpdate] < dp[j] + val) {
                    dp[toUpdate] = dp[j] + val;
                }
            }
        }
    }
    return dp[w] >= 0;
}

int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);

    cin >> n >> w;
    F0R(i, n) cin >> cows[i].A >> cows[i].B;

    int lo = 0, hi = 250000001, mid, ans;
    while (lo + 1 < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            lo = mid;
            ans = mid;
        } else {
            hi = mid;
        }
    }
    cout << ans << endl;

    return 0;
}
