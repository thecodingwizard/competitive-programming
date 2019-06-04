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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, machines[100000];

bool can(double avg) {
    double tot = 0; for (int i = 0; i < n; i++) tot += machines[i] - avg;
    double cur = 0, best = -INF;
    for (int i = 1; i < n - 1; i++) {
        if (cur < 0) cur = 0;
        cur += (machines[i] - avg);
        best = max(best, cur);
    }
    return (tot - best) >= 0;
}

int main() {
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> machines[i];

    double lo = 1.0, hi = 10000.0, mid, ans;
    while ((int)round(lo*10000.0) < (int)round(hi*10000.0)) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            lo = mid;
            ans = lo;
        } else {
            hi = mid;
        }
    }

    printf("%0.3f\n", ans);

    return 0;
}
