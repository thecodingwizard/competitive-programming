/*
Taking Turns
============

Farmer John has invented a new way of feeding his cows. He lays out
N (1 <= N <= 700,000) hay bales conveniently numbered 1..N in a
long line in the barn. Hay bale i has weight W_i (1 <= W_i <=
2,000,000,000). A sequence of six weights might look something like:

        17 5 9 10 3 8

A pair of cows named Bessie and Dessie walks down this line after
examining all the haybales to learn their weights. Bessie is the
first chooser. They take turns picking haybales to eat as they walk
(once a haybale is skipped, they cannot return to it). For instance,
if cows Bessie and Dessie go down the line, a possible scenario is:

* Bessie picks the weight 17 haybale
* Dessie skips the weight 5 haybale and picks the weight 9 haybale
* Bessie picks the weight 10 haybale
* Dessie skips the weight 3 haybale and picks the weight 8 haybale

Diagrammatically:

Bessie   |      |
        17 5 9 10 3 8
Dessie       |      |

This scenario only shows a single skipped bale; either cow can skip
as many as she pleases when it's her turn.

Each cow wishes to maximize the total weight of hay she herself
consumes (and each knows that the other cow has this goal).
Furthermore, a cow will choose to eat the first bale of hay that
maximimizes her total weight consumed.

Given a sequence of hay weights, determine the amount of hay that
a pair of cows will eat as they go down the line of hay.

PROBLEM NAME: hayturn

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains a single integer: W_i

SAMPLE INPUT:

6
17
5
9
10
3
8

OUTPUT FORMAT:

* Line 1: Two space-separated integers, the total weight of hay
        consumed by Bessie and Dessie respectively

SAMPLE OUTPUT:

27 17
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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

long long weight[700001];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> weight[i];

    long long dp1 = 0, dp2 = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (weight[i] + dp2 >= dp1) {
            long long tmp = dp1;
            dp1 = weight[i] + dp2;
            dp2 = tmp;
        }
    }

    cout << dp1 << " " << dp2 << endl;

    return 0;
}
