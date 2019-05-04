/*
The Milk Queue
==============

Every morning, Farmer John's N (1 <= N <= 25,000) cows all line up
for milking. In an effort to streamline the milking process, FJ has
designed a two-stage milking process where the line of cows progresses
through two barns in sequence, with milking taking part sequentially
in both barns. Farmer John milks cows one by one as they go through
the first barn, and his trusty sidekick Farmer Rob milks the cows
(in the same order) as they are released from the first barn and
enter the second barn.

Unfortunately, Farmer John's insistence that the cows walk through
both barns according to a single ordering leads to some inefficiencies.
For example, if Farmer John takes too long to milk a particular
cow, Farmer Rob might end up sitting idle with nothing to do for
some time. On the other hand, if Farmer John works too fast then
we might end up with a long queue of cows waiting to enter the
second barn.

Please help Farmer John decide on the best possible ordering of
cows to use for the milking, so that the last cow finishes milking
as early as possible. For each cow i we know the time A(i) required
for milking in the first barn and the time B(i) required for milking
in the second barn.  Both A(i) and B(i) are in the range 1...20,000.

PROBLEM NAME: mqueue

INPUT FORMAT:

* Line 1: A single integer, N.

* Lines 2..1+N: Line i+1 contains two space-separated integers A(i)
        and B(i) for cow i.

SAMPLE INPUT:

3
2 2
7 4
3 5

INPUT DETAILS:

There are three cows.  Cow #1 takes 2 units of time in both barns,
cow #2 takes 7 units of time in the first barn and 4 in the second,
and cow #3 takes 3 units of time in the first barn and 5 in the
second.

OUTPUT FORMAT:

* Line 1: The minimum possible time it takes to milk all the cows, if
        we order them optimally.

SAMPLE OUTPUT:

16

OUTPUT DETAILS:

Ordering the cows in the order 3, 1, 2, will allow for milking to complete
within only 16 units of time.
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


struct Cow {
    int A, B;
    int order;
};

vector<Cow> cows;

bool howToSort(Cow a, Cow b) {
    return a.order < b.order;
}

int main() {
    int n; cin >> n;
    cows.resize(n);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        cows[i].A = a; cows[i].B = b;
        if (a < b) cows[i].order = a;
        else cows[i].order = INF - b;
    }
    sort(cows.begin(), cows.end(), howToSort);
    int fjMilk = 0, frMilk = 0;
    int ans = 0;
    for (Cow cow : cows) frMilk += cow.B;
    for (Cow cow : cows) {
        fjMilk += cow.A;
        ans = max(ans, fjMilk + frMilk);
        frMilk -= cow.B;
    }
    cout << ans << endl;
    return 0;
}
