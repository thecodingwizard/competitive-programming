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

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

set<ii> visited, inObject;
int perimeter = 0;

void run(int x, int y) {
    if (inObject.count(mp(x, y))) perimeter++;
    else if (visited.count(mp(x, y))) return;
    else {
        visited.insert(mp(x, y));
        bool stop = true;
        for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++) {
                if (inObject.count(mp(x+dx, y+dy))) stop = false;
            }
        if (stop) return;
        run(x+1,y);
        run(x,y+1);
        run(x-1,y);
        run(x,y-1);
    }
}

int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    int n; cin >> n;
    ii leftmost = mp(INF, INF);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        leftmost = min(leftmost, mp(a, b));
        inObject.insert(mp(a, b));
    }
    run(leftmost.A - 1, leftmost.B);
    cout << perimeter << endl;
    return 0;
}
