/*
Addition Chain
==============

An addition chain is a sequence of integers such that the first number is 1,
and every subsequent number is the sum of the previous number and another
number that appears in the list before it. For example, 1 2 3 5 is such a
chain, as 2 is 1+1, 3 is 2+1, and 5 is 2+3. If we were to add another number
to the chain, it had to be one of these: 1+5, 2+5, 3+5 or 5+5. Find the
minimum length chain that ends with a given number.

PROBLEM NAME: chain

INPUT FORMAT:

* Line 1: A single integer: N <= 20,000

SAMPLE INPUT:

5

OUTPUT FORMAT:

* Line 1: The length of shortest addition chain for N

SAMPLE OUTPUT:

4

OUTPUT EXPLANATION:

5 can be reached in 4 steps: 1 2 3 5

*/

/* Note: The following code gets TLE. This problem is not actually DP. */
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

int n;
int best = INF;
vi chain;

int dfs(int steps) {
    int last = chain[chain.size() - 1];
    if (last == n) {
        best = min(best, steps);
        return 0;
    }
    if (last > n) return 0;
    if (steps >= best) return 0;
    if (best != INF) {
        if (last*(1<<(best - steps+1)) < n) return 0;
    }
    for (int i = chain.size() - 1; i >= 0; i--) {
        if (last + chain[i] > n) continue;
        chain.push_back(last + chain[i]);
        dfs(steps+1);
        chain.pop_back();
    }
}

int main() {
    cin >> n;

    chain.push_back(1); chain.push_back(2);

    dfs(2);
    cout << best << endl;

    return 0;
}