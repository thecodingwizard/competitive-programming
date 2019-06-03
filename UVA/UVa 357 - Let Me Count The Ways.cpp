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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

long long n, values[5] = { 1, 5, 10, 25, 50 }, memo[6][30050];

long long dp(int type, long long remaining) {
    if (type == 5) return 0;
    if (remaining < 0) return 0;
    if (remaining == 0) return 1;
    if (memo[type][remaining] != -1) return memo[type][remaining];

    return memo[type][remaining] = dp(type+1, remaining) + dp(type, remaining-values[type]);
}

int main() {
    memset(memo, -1, sizeof(memo));
    while (cin >> n) {
        long long ans = dp(0, n);
        if (ans == 1) {
            cout << "There is only 1 way to produce " << n << " cents change." << endl;
        } else {
            cout << "There are " << ans << " ways to produce " << n << " cents change." << endl;
        }
    }
    return 0;
}
