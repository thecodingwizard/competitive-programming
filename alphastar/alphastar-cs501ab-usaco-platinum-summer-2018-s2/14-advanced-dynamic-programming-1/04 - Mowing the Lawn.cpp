/*
Mowing the Lawn
===============

After winning the annual town competition for best lawn a year ago,
Farmer John has grown lazy; he has not mowed the lawn since then
and thus his lawn has become unruly. However, the competition is
once again coming soon, and FJ would like to get his lawn into
tiptop shape so that he can claim the title.

Unfortunately, FJ has realized that his lawn is so unkempt that he
will need to get some of his N (1 <= N <= 100,000) cows, who are
lined up in a row and conveniently numbered 1..N, to help him. Some
cows are more efficient than others at mowing the lawn; cow i has
efficiency E_i (0 <= E_i <= 1,000,000,000).

FJ has noticed that cows near each other in line often know each
other well; he has also discovered that if he chooses more than K
(1 <= K <= N) consecutive (adjacent) cows to help him, they will
ignore the lawn and start a party instead. Thus, FJ needs you to
assist him: determine the largest total cow efficiency FJ can obtain
without choosing more than K consecutive cows.

PROBLEM NAME: mowlawn

INPUT FORMAT:

* Line 1: Two space-separated integers: N and K

* Lines 2..N+1: Line i+1 contains the single integer: E_i

SAMPLE INPUT:

5 2
1
2
3
4
5

INPUT DETAILS:

FJ has 5 cows whose efficiencies are 1, 2, 3, 4, and 5, in that
order. He wants to choose some of the cows such that their total
efficiency is maximized, but he cannot choose more than 2 consecutive
cows.

OUTPUT FORMAT:

* Line 1: A single integer that is the best total efficiency FJ can
        obtain.

SAMPLE OUTPUT:

12

OUTPUT DETAILS:

FJ chooses all cows but the third. The total efficiency of the cows is thus
1 + 2 + 4 + 5 = 12.
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

struct MaxQueue {
    //         value, index
    deque<pair<long long,   int  >> dq;
    int L = 0, R = -1;

    void insert(long long x) {
        while (!dq.empty() && dq.back().A <= x) {
            dq.pop_back();
        }
        dq.emplace_back(x, ++R);
    }

    int size() { return R - L + 1; }

    void del() {
        if (dq.front().B == L++) dq.pop_front();
    }

    long long query() { return dq.front().A; }
};

int main() {
    int n, k; cin >> n >> k;
    int efficiency[n];
    for (int i = 0; i < n; i++) cin >> efficiency[i];
    long long dp[n];
    long long ps[n];
    ps[0] = efficiency[0];
    for (int i = 1; i < n; i++) ps[i] = ps[i - 1] + efficiency[i];
    memset(dp, 0, sizeof dp);
    MaxQueue mq; mq.insert(0); mq.insert(-ps[0]);
    for (int i = 0; i < n; i++) {
        if (i >= k) mq.del();
        dp[i] = mq.query() + ps[i];
        mq.insert(dp[i] - ps[i + 1]);
    }
    cout << dp[n - 1] << endl;
    return 0;
}
