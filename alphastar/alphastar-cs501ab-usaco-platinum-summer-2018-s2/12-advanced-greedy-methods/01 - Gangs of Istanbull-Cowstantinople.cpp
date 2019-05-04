/*
Gangs of Istanbull/Cowstantinople
=================================

Life is tough on the farm, and when life is tough you have to get
tough. The cows have formed gangs (conveniently numbered 1 to M).
The gangs coexisted in peace for a while, but now things are really
getting out of control!

The cows are competing over control of a great grazing field. This
conflict happens over a series of minutes. Each minute a single
cow walks into the field. If the field is empty the new cow's gang
is considered to take control of the field. If the field is already
controlled by the new cow's gang then the cow just starts grazing.
Otherwise, a single cow from the controlling gang that is grazing
confronts the new cow.

These confrontations between two cows start with some arguing and
inevitably end up with the pair coming to realize how much more
more alike than different they are. The cows, seeing the error
in their way, leave the gang and the field and get a cold glass
of soy milk at FJ's tavern. If after this confrontation the field
is empty than no gang controls the field.

Bessie realizes how these confrontations will occur. She knows how
many cows are in each gang. Bessie really wants her gang to control
the field after the conflict is over and all cows are either on the
field or at FJ's tavern. Help Bessie determine if it is possible
for her gang, labeled 1, to control the field in the end.

If it is possible, Bessie wants to know the maximum number of cows
from her gang that could be on the field at the end. Output this
number and the lexicographically earliest ordering of cows that
results in this number of cows from Bessie's gang at the end. An
ordering X is said to be lexicographically earlier than Y if there
is some k such that X[k] < Y[k] and X[i]=Y[i] for i < k.

PROBLEM NAME: gangs

INPUT FORMAT:

* Line 1: N (1 <= N <= 100) and M (1 <= M <= N) separated by a space.
        The total number of cows in all the gangs will be N. The
        total number of gangs is M.

* Lines 2..1+M: The (1+i)th line indicates how many members are in
        gang i. Each gang has at least 1 member.

SAMPLE INPUT:

5 3
2
1
2

INPUT DETAILS:

There are 5 cows and 3 gangs. Bessie's gang (gang 1) has 2 members,
gang 2 has 1 member, and gang 3 has 2 members.

OUTPUT FORMAT:

* Line 1: Output YES on a single line if Bessie's gang can control
        the field after the conflict. Otherwise output NO on a
        single line.

* Line 2: If Bessie's gang can control the field after the conflict
        output the maximum number of cows that could be on the field
        on a single line.

* Lines 3..2+N: On the (i+2)th line output the index of the gang of
        the cow that appears in the ith minute in the
        lexicographically earliest ordering that leaves the maximum
        number of cows on the field after the conflict.

SAMPLE OUTPUT:

YES
1
1
3
2
3
1

OUTPUT DETAILS:

Only one cow from Bessie's gang can end up on the field.
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

vi cowCount;
int n, m;

int curCowsOnField = 0, curGang = -1;
int send(int startGang) {
    priority_queue<ii, vii> pq;
    for (int i = 2; i <= m; i++) {
        if (i == startGang && cowCount[i] == 1) continue;
        if (cowCount[i] == 0) continue;
        pq.push(mp((i == startGang ? cowCount[i] - 1 : cowCount[i]), i));
    }
    int cowsOnField = 1, gang = startGang;
    if (curGang == startGang) {
        cowsOnField += curCowsOnField;
    } else {
        if (curCowsOnField == cowsOnField) {
            cowsOnField = 0;
        } else if (curCowsOnField > cowsOnField) {
            cowsOnField = curCowsOnField - cowsOnField;
            gang = curGang;
        } else {
            cowsOnField = cowsOnField - curCowsOnField;
        }
    }
    while (!pq.empty()) {
        ii cow = pq.top(); pq.pop();
        if (cow.B == gang) {
            cowsOnField += cow.A;
            continue;
        }
        if (cowsOnField == 0) {
            cowsOnField = cow.A;
            gang = cow.B;
        } else {
            cowsOnField--;
            if (cow.A > 1) pq.push(mp(cow.A - 1, cow.B));
        }
    }
    if (startGang == 1) return cowCount[1] - cowsOnField - 1;
    return cowCount[1] - cowsOnField;
}

int main() {
    cin >> n >> m;
    cowCount.resize(m+10);
    for (int i = 1; i <= m; i++) {
        cin >> cowCount[i];
    }
    vi order;
    int answer = -INF;
    while (order.size() < n) {
        int best = -INF, bestGang;
        for (int i = 1; i <= m; i++) {
            if (cowCount[i] == 0) continue;
            int left = send(i);
            if (best < left) {
                best = left;
                bestGang = i;
            }
        }
        int cowsOnField = 1, gang = bestGang;
        if (curGang == bestGang) {
            cowsOnField += curCowsOnField;
        } else {
            if (curCowsOnField == cowsOnField) {
                cowsOnField = 0;
            } else if (curCowsOnField > cowsOnField) {
                cowsOnField = curCowsOnField - cowsOnField;
                gang = curGang;
            } else {
                cowsOnField = cowsOnField - curCowsOnField;
                gang = bestGang;
            }
        }
        curCowsOnField = cowsOnField;
        curGang = gang;
        cowCount[bestGang]--;
        order.push_back(bestGang);
        if (answer == -INF) answer = best;
    }
    if (answer <= 0) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl << answer << endl;
    for (int cow : order) cout << cow << endl;
    return 0;
}
