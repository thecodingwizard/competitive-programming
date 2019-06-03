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
typedef vector<int> vi;

struct Grid {
    int x{}, y{}, pop = 0;
};

int calcDist(int x, int y, int a, int b) {
    return abs(a - x) + abs(b - y);
}

int calcDist(int x, int y, int a, int b, int c, int d, int e) {
    int best = INF;
    best = min(best, calcDist(x, y, a % 5, a / 5));
    best = min(best, calcDist(x, y, b % 5, b / 5));
    best = min(best, calcDist(x, y, c % 5, c / 5));
    best = min(best, calcDist(x, y, d % 5, d / 5));
    best = min(best, calcDist(x, y, e % 5, e / 5));
    return best;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        vector<Grid> city;
        int n;
        cin >> n;
        while (n--) {
            Grid grid;
            cin >> grid.y >> grid.x >> grid.pop;
            city.push_back(grid);
        }

        int A, B, C, D, E, least = INF;
        for (int a = 0; a < 25; a++) {
            for (int b = a + 1; b < 25; b++) {
                for (int c = b + 1; c < 25; c++) {
                    for (int d = c + 1; d < 25; d++) {
                        for (int e = d + 1; e < 25; e++) {
                            int totDist = 0;
                            for (auto &grid : city) {
                                totDist += grid.pop * calcDist(grid.x, grid.y, a, b, c, d, e);
                            }
                            if (totDist < least) {
                                least = totDist;
                                A = a;
                                B = b;
                                C = c;
                                D = d;
                                E = e;
                            }
                        }
                    }
                }
            }
        }

        printf("%d %d %d %d %d\n", A, B, C, D, E);
    }
    return 0;
}