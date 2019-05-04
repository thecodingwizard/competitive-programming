/*
Empty Stalls
============

Farmer John's new barn consists of a huge circle of N stalls (2 <= N <=
3,000,000), numbered 0..N-1, with stall N-1 being adjacent to stall 0.

At the end of each day, FJ's cows arrive back at the barn one by one, each
with a preferred stall they would like to occupy.  However, if a cow's
preferred stall is already occupied by another cow, she scans forward
sequentially from this stall until she finds the first unoccupied stall,
which she then claims.  If she scans past stall N-1, she continues scanning
from stall 0.

Given the preferred stall of each cow, please determine the smallest index
of a stall that remains unoccupied after all the cows have returned to the
barn.  Notice that the answer to this question does not depend on the order
in which the cows return to the barn.

In order to avoid issues with reading huge amounts of input, the input to
this problem is specified in a concise format using K lines (1 <= K <=
10,000) each of the form:

X Y A B

One of these lines specifies the preferred stall for XY total cows: X cows
prefer each of the stalls f(1) .. f(Y), where f(i) = (Ai + B) mod N.  The
values of A and B lie in the range 0...1,000,000,000.

Do not forget the standard memory limit of 64MB for all problems.

PROBLEM NAME: empty

INPUT FORMAT:

* Line 1: Two space-separated integers: N and K.

* Lines 2..1+K: Each line contains integers X Y A B, interpreted as
        above.  The total number of cows specified by all these lines
        will be at most N-1.  Cows can be added to the same stall by
        several of these lines.

SAMPLE INPUT:

10 3
3 2 2 4
2 1 0 1
1 1 1 7

INPUT DETAILS:

There are 10 stalls in the barn, numbered 0..9.  The second line of input
states that 3 cows prefer stall (2*1+4) mod 10 = 6, and 3 cows prefer stall
(2*2+4) mod 10 = 8.  The third line states that 2 cows prefer stall (0*1+1)
mod 10 = 1.  Line four specifies that 1 cow prefers stall (1*1+7) mod 10 =
8 (so a total of 4 cows prefer this stall).

OUTPUT FORMAT:

* Line 1: The minimum index of an unoccupied stall.

SAMPLE OUTPUT:

5

OUTPUT DETAILS:

All stalls will end up occupied except stall 5.
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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    unsigned int n, k;
    cin >> n >> k;
    unsigned int x, y, a, b;
    auto * stalls = new unsigned int[3000001];
    memset(stalls, 0, sizeof stalls);
    for (int i = 0; i < k; i++) {
        cin >> x >> y >> a >> b;
        for (int j = 1; j <= y; j++) {
            unsigned int stall = ((a%n)*j+b)%n;
            stalls[stall] += x;
        }
    }
    unsigned int counter = 0;
    for (int i = 0; i < n; i++) {
        counter += stalls[i];
        if (counter > 0) counter--;
    }
    for (int i = 0; i < n; i++) {
        counter += stalls[i];
        if (counter > 0) counter--;
        else {
            cout << i;
            break;
        }
    }
    return 0;
}
