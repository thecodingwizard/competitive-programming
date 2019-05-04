/*
Bessie's Weight Problem
=======================

Bessie, like so many of her sisters, has put on a few too many
pounds enjoying the delectable grass from Farmer John's pastures.
FJ has put her on a strict diet of no more than H (5 <= H <= 45,000)
kilograms of hay per day.

Bessie can eat only complete bales of hay; once she starts she can't
stop. She has a complete list of the N (1 <= N <= 500) haybales
available to her for this evening's dinner and, of course, wants
to maximize the total hay she consumes. She can eat each supplied
bale only once, naturally (though duplicate weight valuess might
appear in the input list; each of them can be eaten one time).

Given the list of haybale weights W_i (1 <= W_i <= H), determine the
maximum amount of hay Bessie can consume without exceeding her limit
of H kilograms (remember: once she starts on a haybale, she eats
it all).

PROBLEM NAME: diet

INPUT FORMAT:

* Line 1: Two space-separated integers: H and N

* Lines 2..N+1: Line i+1 describes the weight of haybale i with a
        single integer: W_i

SAMPLE INPUT:

56 4
15
19
20
21

INPUT DETAILS:

Four haybales of weight 15, 19, 20, and 21. Bessie can eat as many as she
wishes without exceeding the limit of 56 altogether.

OUTPUT FORMAT:

* Line 1: A single integer that is the number of kilograms of hay that
        Bessie can consume without going over her limit.

SAMPLE OUTPUT:

56

OUTPUT DETAILS:

Bessie can eat three bales (15, 20, and 21) and run right up to the limit
of 56 kg.
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


int main() {
    int dp[2][45001];
    int weight[101];
    int h, n;
    cin >> h >> n;
    for (int i = 0; i < n; i++) cin >> weight[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= h; j++) {
            int doNotTake = i > 0 ? dp[(i - 1) % 2][j] : 0;
            int take = j - weight[i] >= 0 ? weight[i] + (i > 0 ? dp[(i - 1) % 2][j - weight[i]] : 0) : -INF;
            dp[i % 2][j] = max(take, doNotTake);
        }
    }

    cout << dp[(n - 1) % 2][h];

    return 0;
}
