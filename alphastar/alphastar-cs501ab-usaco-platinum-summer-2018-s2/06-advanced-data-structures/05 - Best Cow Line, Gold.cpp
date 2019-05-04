/*
Best Cow Line, Gold
===================

FJ is about to take his N (1 <= N <= 30,000) cows to the annual
"Farmer of the Year" competition. In this contest every farmer
arranges his cows in a line and herds them past the judges.

The contest organizers adopted a new registration scheme this year:
simply register the initial letter of every cow in the order they
will appear (e.g., If FJ takes Bessie, Sylvia, and Dora in that
order, he just registers BSD). After the registration phase ends,
every group is judged in increasing lexicographic order (i.e.,
alphabetical order) according to the string of the initials of the
cows' names.

FJ is very busy this year and has to hurry back to his farm, so he
wants to be judged as early as possible. He decides to rearrange
his cows, who have already lined up, before registering them.

FJ marks a location for a new line of the competing cows. He then
proceeds to marshal the cows from the old line to the new one by
repeatedly sending either the first or last cow in the (remainder
of the) original line to the end of the new line. When he's finished,
FJ takes his cows for registration in this new order.

Given the initial order of his cows, determine the least lexicographic
string of initials he can make this way.

PROBLEM NAME: bclgold

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains a single initial ('A'..'Z') of the
        cow in the ith position in the original line

SAMPLE INPUT:

6
A
C
D
B
C
B

INPUT DETAILS:

FJ has 6 cows in this order: ACDBCB

OUTPUT FORMAT:

The least lexicographic string he can make. Every line (except perhaps
the last one) contains the initials of 80 cows ('A'..'Z') in the new
line.

SAMPLE OUTPUT:

ABCBCD

OUTPUT DETAILS:

  Step   Original     New
   #1     ACDBCB
   #2      CDBCB     A
   #3      CDBC      AB
   #4      CDB       ABC
   #5      CD        ABCB
   #6       D        ABCBC
   #7                ABCBCD
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
    int n;
    cin >> n;
    char cows[n];
    char optimal[n];
    for (int i = 0; i < n; i++) cin >> cows[i];
    int front = 0, back = n - 1, idx = 0;
    while (front <= back) {
        if (cows[front] == cows[back]) {
            bool found = false;
            for (int i = 0; i <= (back - front)/2; i++) {
                if (cows[front + i] != cows[back - i]) {
                    if (cows[front + i] < cows[back - i]) optimal[idx++] = cows[front++];
                    else optimal[idx++] = cows[back--];
                    found = true;
                    break;
                }
            }
            if (!found) optimal[idx++] = cows[front++];
        } else {
            if (cows[front] < cows[back]) optimal[idx++] = cows[front++];
            else optimal[idx++] = cows[back--];
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != 0 && i % 80 == 0) cout << endl;
        cout << optimal[i];
    }
    cout << endl;
    return 0;
}
