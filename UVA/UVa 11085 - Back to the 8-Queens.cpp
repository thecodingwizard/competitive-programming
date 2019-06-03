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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

int row[8];            // ok to use global variables
int solutions[92][8];
int si = 0;

bool place(int r, int c) {
    for (int prev = 0; prev < c; prev++)    // check previously placed queens
        if (row[prev] == r || (abs(row[prev] - r) == abs(prev - c)))
            return false;        // share same row or same diagonal -> infeasible
    return true;
}

void backtrack(int c) {
    if (c == 8) {
        copy(begin(row), end(row), begin(solutions[si++]));
    }
    for (int r = 0; r < 8; r++)                       // try all possible row
        if (place(r, c)) {          // if can place a queen at this col and row
            row[c] = r; backtrack(c + 1);      // put this queen here and recurse
        }
}

int x = 1;
int main() {
    backtrack(0);
    int board[8];
    while (cin >> board[0]) {
        board[0]--;
        for (int i = 1; i < 8; i++) {
            cin >> board[i];
            board[i]--;
        }

        int best = INF;
        for (int i = 0; i < 92; i++) {
            int moves = 0;
            for (int j = 0; j < 8; j++) {
                moves += board[j] != solutions[i][j];
            }
            best = min(moves, best);
        }

        cout << "Case " << x++ << ": " << best << endl;
    }
    return 0;
}