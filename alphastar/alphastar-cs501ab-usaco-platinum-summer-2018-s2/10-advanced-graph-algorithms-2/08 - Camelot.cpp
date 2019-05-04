/*
Camelot
=======

Centuries ago, King Arthur and the Knights of the Round Table used
to meet every year on New Year's Day to celebrate their fellowship.
In remembrance of these events, we consider a board game for one
player, on which one chesspiece king and several knight pieces are
placed on squares, no two knights on the same square.

The King can move to any adjacent square (shown with '*' below) as
long as it does not fall off the board:

* * *
* K *
* * *

A Knight (represented with 'N' below) can jump L shaped, as long as
it does not fall off the board:

- * - * -
* - - - *
- - N - -
* - - - *
- * - * -

During the play, the player can place more than one piece in the
same square. The board squares are assumed big enough so that a
piece is never an obstacle for any other piece to move freely.

The player's goal is to move the pieces so as to gather them all in
the same square - in the minimal number of moves. To achieve this,
he must move the pieces as prescribed above. Additionally, whenever
the king and one or more knights are placed in the same square, the
player may choose to move the king and one of the knights together
from that point on, as a single knight, up to the final gathering
point. Moving the knight together with the king counts as a single
move.

Write a program to compute the minimum number of moves the player
must perform to produce the gathering. The pieces can gather on any
square, of course.

PROGRAM NAME: camelot

INPUT FORMAT

* Line 1: Two space-separated integers: R,C, the number of rows and
columns on the board. There will be no more than 26 columns and no
more than 30 rows.

* Line 2..end: The input file contains a sequence of
space-separated letter/digit pairs, 1 or more per line. The first
pair represents the board position of the king; subsequent pairs
represent positions of knights. There might be 0 knights or the
knights might fill the board. Rows are numbered starting at 1;
columns are specified as upper case characters starting with 'A'.

SAMPLE INPUT:

8 8
D 4
A 3 A 8
H 1 H 8

The king is positioned at D4. There are four knights, positioned at
A3, A8, H1, and H8.

OUTPUT FORMAT:

A single line with the number of moves to aggregate the pieces.

SAMPLE OUTPUT:

10

SAMPLE OUTPUT ELABORATION:

They gather at B5.
Knight 1: A3 - B5 (1 move)
Knight 2: A8 - C7 - B5 (2 moves)
Knight 3: H1 - G3 - F5 - D4 (picking up king) - B5 (4 moves)
Knight 4: H8 - F7 - D6 - B5 (3 moves)
1 + 2 + 4 + 3 = 10 moves.
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
#include <unordered_map>
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

ii king; vii knights;
int steps[30][26][30][26];

int main() {
    int r, c; cin >> r >> c;
    {
        char row; int col;
        cin >> row >> col; king.B = row - 'A'; king.A = col - 1;
        while (cin >> row >> col) {
            knights.emplace_back(--col, row - 'A');
        }
    }
    int dx[8] = {-2, -1, 1, 2,  2,  1, -1, -2};
    int dy[8] = { 1,  2, 2, 1, -1, -2, -2, -1};
    queue<ii> q;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) for (int k = 0; k < r; k++) for (int l = 0; l < c; l++) steps[i][j][k][l] = INF;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
            steps[i][j][i][j] = 0;
            q.push(mp(i, j));
            while (!q.empty()) {
                ii next = q.front(); q.pop();
                for (int x = 0; x < 8; x++) {
                    int a = next.A + dx[x], b = next.B + dy[x];
                    if (a < 0 || a >= r || b < 0 || b >= c || steps[i][j][a][b] <= steps[i][j][next.A][next.B] + 1) continue;
                    steps[i][j][a][b] = steps[i][j][next.A][next.B] + 1;
                    q.push(mp(a, b));
                }
            }
        }
    long long bestCost = INF;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
            long long costForThisSquare = 0;
            for (ii knight : knights) {
                costForThisSquare += steps[knight.A][knight.B][i][j];
            }
            for (auto knight : knights) {
                int bestStepsRequired = INF/2;
                for (int k = -2; k <= 2; k++) for (int l = -2; l <= 2; l++) {
                        if (king.A + k < 0 || king.A + k >= r || king.B + l < 0 || king.B + l >= c) continue;
                        // king can take at most two steps
                        int stepsRequired = steps[knight.A][knight.B][king.A + k][king.B + l] + max(abs(k), abs(l)) + steps[king.A + k][king.B + l][i][j];
                        bestStepsRequired = min(bestStepsRequired, stepsRequired);
                    }
                bestCost = min(bestCost, costForThisSquare + bestStepsRequired - steps[knight.A][knight.B][i][j]);
            }
            bestCost = min(bestCost, costForThisSquare + max(abs(king.A - i), abs(king.B - j)));
        }
    cout << (bestCost == INF ? 0 : bestCost) << endl;
    return 0;
}
