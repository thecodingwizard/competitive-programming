/*
No Change
=========

Farmer John is at the market to purchase supplies for his farm.  He has in
his pocket K coins (1 <= K <= 16), each with value in the range
1..100,000,000.  FJ would like to make a sequence of N purchases
(1 <= N <= 100,000), where the ith purchase costs c(i) units of money
(1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can
periodically stop and pay, with a single coin, for all the purchases made
since his last payment (of course, the single coin he uses must be large
enough to pay for all of these).  Unfortunately, the vendors at the market
are completely out of change, so whenever FJ uses a coin that is larger
than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making
his N purchases in sequence.  Output -1 if it is impossible for FJ to make
all of his purchases.

PROBLEM NAME: nochange

INPUT FORMAT:

* Line 1: Two integers, K and N.

* Lines 2..1+K: Each line contains the amount of money of one of FJ's
        coins.

* Lines 2+K..1+N+K: These N lines contain the costs of FJ's intended
        purchases.

SAMPLE INPUT:

3 6
12
15
10
6
3
3
2
3
7

INPUT DETAILS:

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in
sequence of value 6, 3, 3, 2, 3, and 7.

OUTPUT FORMAT:

* Line 1: The maximum amount of money FJ can end up with, or -1 if FJ
        cannot complete all of his purchases.

SAMPLE OUTPUT:

12

OUTPUT DETAILS:

FJ spends his 10-unit coin on the first two purchases, then the 15-unit
coin on the remaining purchases.  This leaves him with the 12-unit coin.
*/

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

int k, n, coins[16], cost[100001], ps[100001];

int main() {
    cin >> k >> n;
    for (int i = 0; i < k; i++) cin >> coins[i];
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
        ps[i] = (i > 0 ? ps[i - 1] : 0) + cost[i];
    }
    int dp[(1 << 16)];
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1 << k); i++) {
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) continue;
            int toSearch = coins[j];
            if (dp[i] > 0) {
                toSearch += ps[dp[i] - 1];
            }
            auto it = upper_bound(ps, ps + n, toSearch);
            dp[i | (1 << j)] = max(dp[i | (1 << j)], (int) distance(ps, it));
        }
    }
    int ans = -1;
    for (int i = 0; i < (1 << k); i++) {
        if (dp[i] >= n) {
            int sum = 0;
            for (int j = 0; j < k; j++) {
                if (!(i & (1 << j))) sum += coins[j];
            }
            ans = max(ans, sum);
        }
    }
    cout << ans << endl;
    return 0;
}
