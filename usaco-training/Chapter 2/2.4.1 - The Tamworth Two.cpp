/*
ID: nathan.18
TASK: ttwo
LANG: C++
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
#include <fstream>
#include <cassert>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define FORWARD 0
#define RIGHT 1
#define BACKWARD 2
#define LEFT 3
#define BLOCKED 0
#define EMPTY 1

struct State {
    int x, y, direction;
};

int grid[10][10];

void move(State &object) {
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    int x1 = object.x + dx[object.direction], y1 = object.y + dy[object.direction];
    if (x1 < 0 || x1 >= 10 || y1 < 0 || y1 >= 10 || grid[x1][y1] == BLOCKED) {
        object.direction++;
        object.direction %= 4;
    } else {
        object.x = x1; object.y = y1;
    }
}

int main() {
    freopen("ttwo.in", "r", stdin);
    freopen("ttwo.out", "w", stdout);

    State fj, bessie;

    F0R(i, 10) F0R(j, 10) {
            char c; cin >> c;
            grid[i][j] = c == '*' ? BLOCKED : EMPTY;
            if (c == 'F') { fj.x = i; fj.y = j; }
            else if (c == 'C') { bessie.x = i; bessie.y = j; }
        }

    fj.direction = bessie.direction = FORWARD;

    long long steps = 0;
    while (!(fj.x == bessie.x && fj.y == bessie.y) && steps < 160010) {
        move(fj); move(bessie);
        steps++;
    }

    if (steps >= 160005) {
        cout << "0" << endl;
    } else {
        cout << steps << endl;
    }

    return 0;
}
