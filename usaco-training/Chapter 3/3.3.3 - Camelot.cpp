/*
ID: nathan.18
TASK: camelot
LANG: C++11
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
    freopen("camelot.in", "r", stdin);
    freopen("camelot.out", "w", stdout);
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