/*
ID: nathan.18
TASK: holstein
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

int main() {
    freopen("holstein.in", "r", stdin);
    freopen("holstein.out", "w", stdout);

    int v, g; cin >> v;
    int required[v]; for (int i = 0; i < v; i++) cin >> required[i];
    cin >> g;
    vi feeds[g];
    for (int i = 0; i < g; i++) for (int j = 0; j < v; j++) {
            int a; cin >> a; feeds[i].push_back(a);
        }
    int best = INF, bestMask = -1;
    int sum[v];
    for (int i = 0; i < (1 << g); i++) {
        if (__builtin_popcount(i) >= best) continue;
        memset(sum, 0, sizeof sum);
        for (int j = 0; j < g; j++) {
            if (i & (1 << j)) {
                for (int k = 0; k < v; k++) {
                    sum[k] += feeds[j][k];
                }
            }
        }
        for (int k = 0; k < v; k++) {
            if (sum[k] < required[k]) goto bad;
        }
        best = __builtin_popcount(i);
        bestMask = i;

        bad:
        continue;
    }
    cout << best;
    for (int i = 0; i < g; i++) {
        if (bestMask & (1 << i)) {
            cout << " " << i+1;
        }
    }
    cout << endl;
    return 0;
}
