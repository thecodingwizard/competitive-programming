/*
Buying Hay
==========

Farmer John is running out of supplies and needs to purchase H (1
<= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N.
Supplier i sells packages that contain P_i (1 <= P_i <= 5,000)
pounds of hay at a cost of C_i (1 <= C_i <= 5,000) dollars. Each
supplier has an unlimited number of packages available, and the
packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least
H pounds of hay.

PROBLEM NAME: buyhay

INPUT FORMAT:

* Line 1: Two space-separated integers: N and H

* Lines 2..N+1: Line i+1 contains two space-separated integers: P_i
        and C_i

SAMPLE INPUT:

2 15
3 2
5 3

OUTPUT FORMAT:

* Line 1: A single integer representing the minimum cost FJ needs to
        pay to obtain at least H pounds of hay.

SAMPLE OUTPUT:

9

OUTPUT DETAILS:

FJ can buy three packages from the second supplier for a total cost of 9.
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

int n, h;
int memo[50001];
int amt[101], cost[101];

int dp(int hayLeft) {
    if (hayLeft <= 0) return 0;
    if (memo[hayLeft] != -1) return memo[hayLeft];

    int ans = INF;
    for (int i = 0; i < n; i++) ans = min(ans, dp(hayLeft - amt[i]) + cost[i]);
    return memo[hayLeft] = ans;
}

int main() {
    cin >> n >> h;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) cin >> amt[i] >> cost[i];
    cout << dp(h) << endl;

    return 0;
}
