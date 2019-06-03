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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

int s, d;

int calc(int mask, int month, int sum, int lastFiveMonths) {
    if (month > 5) {
        if (mask & (1 << 5)) {
            lastFiveMonths -= s;
            mask -= (1 << 5);
        } else {
            lastFiveMonths += d;
        }
        if (lastFiveMonths >= 0) return -INF;
        if (month == 12) {
            return sum;
        }
    } else if (month == 5 && lastFiveMonths >= 0) return -INF;
    mask = mask << 1;
    int a = calc(mask | 1, month + 1, sum + s, lastFiveMonths + s);
    int b = calc(mask, month + 1, sum - d, lastFiveMonths - d);
    return max(a, b);
}

int main() {
    while (cin >> s >> d) {
        int ans = calc(0, 0, 0, 0);
        if (ans >= 0) cout << ans << endl;
        else cout << "Deficit" << endl;
    }
    return 0;
}