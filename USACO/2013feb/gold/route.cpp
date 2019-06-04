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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, m, r, lval[40001], rval[40001];
vii paths;

int main() {
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin >> n >> m >> r;
    lval[0] = 0, rval[0] = 0;
    for (int i = 1; i <= n; i++) cin >> lval[i];
    for (int i = 1; i <= m; i++) cin >> rval[i];
    for (int i = 0; i < r; i++) {
        int a, b; cin >> a >> b;
        paths.push_back(mp(a, b));
    }
    sort(paths.begin(), paths.end());
    long long dpLeft[100001];
    long long dpRight[100001];
    memset(dpLeft, 0, sizeof dpLeft);
    memset(dpRight, 0, sizeof dpRight);
    long long best = 0;
    for (int i = 1; i <= n; i++) {
        dpLeft[i] = lval[i];
        best = max(best, dpLeft[i]);
    }
    for (int i = 1; i <= m; i++) {
        dpRight[i] = rval[i];
        best = max(best, dpRight[i]);
    }
    for (int i = r - 1; i >= 0; i--) {
        int start = paths[i].A, end = paths[i].B;

        long long newDPRight = rval[end] + dpLeft[start], newDPLeft = lval[start] + dpRight[end];
        dpRight[end] = max(dpRight[end], newDPRight);
        dpLeft[start] = max(dpLeft[start], newDPLeft);

        best = max(best, dpRight[end]);
        best = max(best, dpLeft[start]);
    }

    cout << best << endl;
    return 0;
}
