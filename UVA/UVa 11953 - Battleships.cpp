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

int dr[] = {1,0,-1,0};
int dc[] = {0,1,0,-1};
int n;
bool ship[101][101];
bool bombed[101][101];

bool floodfill(int x, int y) {
    if (!ship[x][y]) return false;
    ship[x][y] = false;
    bool isShip = !bombed[x][y];
    for (int i = 0; i < 4; i++) {
        if (floodfill(x + dr[i], y + dc[i])) isShip = true;
    }
    return isShip;
}

int main() {
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        cin >> n;
        memset(ship, false, sizeof ship);
        memset(bombed, false, sizeof bombed);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
                char c; cin >> c;
                if (c == 'x') ship[i][j] = true;
                else if (c == '@') {
                    ship[i][j] = true;
                    bombed[i][j] = true;
                }
            }
        int ct = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
                if (!ship[i][j]) continue;
                if (floodfill(i, j)) ct++;
            }
        cout << "Case " << caseNum << ": " << ct << endl;
    }


    return 0;
}
