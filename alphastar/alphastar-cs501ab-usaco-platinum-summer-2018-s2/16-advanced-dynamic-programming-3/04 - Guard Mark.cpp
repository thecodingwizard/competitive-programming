/*
Guard Mark
==========

Farmer John and his herd are playing frisbee.  Bessie throws the
frisbee down the field, but it's going straight to Mark the field hand
on the other team!  Mark has height H (1 <= H <= 1,000,000,000), but
there are N cows on Bessie's team gathered around Mark (2 <= N <= 20).
They can only catch the frisbee if they can stack up to be at least as
high as Mark.  Each of the N cows has a height, weight, and strength.
A cow's strength indicates the maximum amount of total weight of the
cows that can be stacked above her.

Given these constraints, Bessie wants to know if it is possible for
her team to build a tall enough stack to catch the frisbee, and if so,
what is the maximum safety factor of such a stack.  The safety factor
of a stack is the amount of weight that can be added to the top of the
stack without exceeding any cow's strength.

INPUT:

The first line of input contains N and H.

The next N lines of input each describe a cow, giving its height,
weight, and strength.  All are positive integers at most 1 billion.

SAMPLE INPUT:

4 10
9 4 1
3 3 5
5 5 10
4 4 5

OUTPUT:

If Bessie's team can build a stack tall enough to catch the frisbee,
please output the maximum achievable safety factor for such a stack.
Otherwise output "Mark is too tall" (without the quotes).

SAMPLE OUTPUT:

2
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
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Cow {
    long long height, weight, strength;
};

long long dp[(1 << 20)], weight[(1 << 20)], height[(1 << 20)];
int main() {
    int n, h;
    cin >> n >> h;
    Cow cows[n];
    for (int i = 0; i < n; i++) cin >> cows[i].height >> cows[i].weight >> cows[i].strength;
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = -INF;
        int w = 0, h = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) w += cows[j].weight;
            if (i & (1 << j)) h += cows[j].height;
        }
        weight[i] = w;
        height[i] = h;
    }
    long long best = -1;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;
            int idx = i | (1 << j);
            if (dp[i] == -INF) dp[i] = INF;
            dp[idx] = max(dp[idx], max(min(dp[i] - cows[j].weight, cows[j].strength), min(cows[j].strength - weight[i], dp[i])));
            if (height[idx] >= h) best = max(best, dp[idx]);
        }
    }
    if (best == -1) cout << "Mark is too tall" << endl;
    else cout << best << endl;
    return 0;
}
