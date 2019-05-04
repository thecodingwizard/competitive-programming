/*
Cheapest Palindrome
===================

To keeping track of all the cows, Farmer John has installed on each
cow an electronic ID tag that the system will read as the cows pass
by a scanner. Each ID tag's contents are currently a single string
with length M (1 <= M <= 2,000) characters drawn from an alphabet
of N (1 <= N <= 26) different symbols (namely, the lower-case roman
alphabet).

Cows, being the mischievous creatures they are, sometimes try to
spoof the system by walking backwards. While a cow whose ID is
"abcba" would read the same no matter which direction the she walks,
a cow with the ID "abcb" can potentially register as two different
IDs ("abcb" and "bcba").

FJ would like to change the cows's ID tags so they read the same
no matter which direction the cow walks by. For example, "abcb" can
be changed by adding "a" at the end to form "abcba" so that the ID
is palindromic (reads the same forwards and backwards). Some other
ways to change the ID to be palindromic are include adding the three
letters "bcb" to the begining to yield the ID "bcbabcb" or removing
the letter "a" to yield the ID "bcb". One can add or remove characters
at any location in the string yielding a string longer or shorter
than the original string.

Unfortunately as the ID tags are electronic, each character insertion
or deletion has a cost (0 <= cost <= 10,000) which varies depending
on exactly which character value to be added or deleted. Find the
minimum cost to change the ID tag so it satisfies FJ's requirements.
An empty ID tag is considered to satisfy the requirements of reading
the same forward and backward. Only letters with associated costs can
be added to a string.

PROBLEM NAME: cheappal

INPUT FORMAT:

* Line 1: Two space-separated integers: N and M

* Line 2: This line contains exactly M characters which constitute the
       initial ID string

* Lines 3..N+2: Each line contains three space-separated entities: a
       character of the input alphabet and two integers which are
       respectively the cost of adding and deleting that character.

SAMPLE INPUT:

3 4
abcb
a 1000 1100
b 350 700
c 200 800

INPUT DETAILS:

The nametag is "abcb" with these per-operation costs:

 Insert Delete
a  1000   1100
b   350    700
c   200    800

OUTPUT FORMAT:

* Line 1: A single line with a single integer that is the minimum cost
       to change the given name tag.

SAMPLE OUTPUT:

900

OUTPUT DETAILS:

If we insert an "a" on the end to get "abcba", the cost would be
1000. If we delete the "a" on the beginning to get "bcb", the cost
would be 1100. If we insert "bcb" at the begining of the string, the
cost would be 350+200+350=900, which is the minimum.
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

int n, m;
string input;
int addCost[1000], delCost[1000];
int memo[2000][2000];

bool isPalindrome(int start, int end) {
    int x = start, y = end;
    while (x < y) {
        if (input[x] != input[y]) return false;
        x++; y--;
    }
}

int dp(int start, int end) {
    if (start > end) return 0;
    if (memo[start][end] != -1) return memo[start][end];
    if (isPalindrome(start, end)) return memo[start][end] = 0;
    char last = input[end-1], first = input[start];
    if (last == first) return dp(start + 1, end - 1);
    return memo[start][end] = min(dp(start, end - 1) + min(addCost[last], delCost[last]), dp(start + 1, end) + min(addCost[first], delCost[first]));
}

int main() {
    cin >> n >> m;
    cin >> input;
    for (int i = 0; i < n; i++) {
        char c; int x, y; cin >> c >> x >> y; addCost[c] = x; delCost[c] = y;
    }
    memset(memo, -1, sizeof memo);

    cout << dp(0, m) << endl;

    return 0;
}
